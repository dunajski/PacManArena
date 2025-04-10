#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "client.h"
#include "drawer.h"
#include "pacman.h"

#include "game.h"

Client::Client()
{
    std::cout << "Client is starting..." << std::endl;
}

Client::~Client()
{
    selector.remove(socket);
    socket.disconnect();
}

#define RUN_ONLY_CLIENT 1

void Client::init_connection_and_run()
{
    #if RUN_ONLY_CLIENT
    if (const sf::Socket::Status status = socket.connect(server_ip, port); status != sf::Socket::Status::Done)
    {
        std::cout << "Connection failed" << std::endl;
        return;
    }
    std::cout << "Connected" << std::endl;

    if (std::size_t received = 0; socket.receive(buff_in.data(), buff_in.size(), received) != sf::Socket::Status::Done)
        return;
    is_connected = true;
    std::cout << "Message received from the server: " << std::quoted(buff_in.data()) << std::endl;

    static constexpr std::string_view client_message = "Hello from client!";
    send_to_server(client_message.data());
    std::cout << "Message sent to the server: " << std::quoted(client_message.data()) << std::endl;

    // I want to use non-blocking socket to run checking every 10 ms, I know that I could use threads
    // ,but I want to use something simpler
    selector.add(socket);
    socket.setBlocking(false);
    #else
    is_connected = true;
    #endif

    // now start rendering and handle data between connected client and server
    run_game();
}

void Client::send_to_server(const std::string& data)
{
    auto send_status = socket.send(data.data(), data.size());

    if (send_status != sf::Socket::Status::Done)
    {
        std::cout << "Failed to send message to server" << std::endl;
    }
}

void Client::run_game()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Pac-Man Arena", sf::State::Fullscreen);
    window.setFramerateLimit(144);

    // it is weird... stolen from web
    // https://www.sfml-dev.org/tutorials/3.0/graphics/view/#defining-what-the-view-views
    sf::View views[4];

    views[0].setViewport(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.5f, 0.5f)));
    views[1].setViewport(sf::FloatRect(sf::Vector2f(0.5f, 0.f), sf::Vector2f(0.5f, 0.5f)));
    views[2].setViewport(sf::FloatRect(sf::Vector2f(0.f, 0.5f), sf::Vector2f(0.5f, 0.5f)));
    views[3].setViewport(sf::FloatRect(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.5f, 0.5f)));

    constexpr float view_width = 960.f;
    constexpr float view_height = 540.f;

    for (auto& view : views) {
        view.setSize(sf::Vector2f(view_width, view_height));
        view.setCenter(sf::Vector2f(view_width / 2.f, view_height / 2.f));
    }
    std::unique_ptr<Game> games[4];
    std::unique_ptr<Drawer> drawers[4];

    for (int i = 0; i < 4; ++i) {
        games[i] = std::make_unique<Game>();
        games[i]->initialize_map();
        games[i]->start_game();
        drawers[i] = std::make_unique<Drawer>(window, view_width, view_height);
    }

    sf::Clock clock;

    while (window.isOpen() && is_connected)
    {
        auto dt = clock.restart().asSeconds();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (key_pressed->scancode == sf::Keyboard::Scan::Escape)
                    window.close();

                for (auto& game : games) {
                    auto pac = game->get_pacman();
                    if (key_pressed->scancode == sf::Keyboard::Scan::Right)
                        pac->set_direction(MoveDirection::RIGHT);
                    else if (key_pressed->scancode == sf::Keyboard::Scan::Left)
                        pac->set_direction(MoveDirection::LEFT);
                    else if (key_pressed->scancode == sf::Keyboard::Scan::Up)
                        pac->set_direction(MoveDirection::UP);
                    else if (key_pressed->scancode == sf::Keyboard::Scan::Down)
                        pac->set_direction(MoveDirection::DOWN);
                }
            }
        }
        #if RUN_ONLY_CLIENT
        // check every 10 ms that there is something data to handle
        if (selector.wait(sf::milliseconds(10)))
        {
            if (selector.isReady(socket))
            {
                std::size_t received;
                if (const sf::Socket::Status status = socket.receive(buff_in.data(), buff_in.size(), received);
                    status == sf::Socket::Status::Done)
                {
                    std::cout << "Received " << received << " bytes from server" << std::endl;
                    std::cout << "Message: " << std::quoted(buff_in.data()) << std::endl;

                }
                else if (status == sf::Socket::Status::Disconnected)
                {
                    is_connected = false;
                    std::cout << "Server disconnected" << std::endl;
                }
            }
        }
        #endif

        for (auto& game : games)
            game->update(dt);

        window.clear();
        for (int i = 0; i < 4; ++i) {
            window.setView(views[i]);
            drawers[i]->draw_map(games[i]->get_map_layout());
            drawers[i]->draw_game_entities(games[i]->get_all_entities());
            drawers[i]->draw_score(games[i]->get_score());
        }
        window.display();
    }
}
