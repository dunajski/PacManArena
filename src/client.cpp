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

#define RUN_ONLY_CLIENT 0

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
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Pac-Man Arena");
    window.setFramerateLimit(144);

    auto game_instance = std::make_unique<Game>();
    game_instance->initialize_map();
    game_instance->start_game();

    Drawer drawer(window);

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
                auto pac = game_instance->get_pacman();
                if (key_pressed->scancode == sf::Keyboard::Scan::Right)
                {
                    pac->set_direction(MoveDirection::RIGHT);
                }
                else if (key_pressed->scancode == sf::Keyboard::Scan::Left)
                {
                    pac->set_direction(MoveDirection::LEFT);
                }
                else if (key_pressed->scancode == sf::Keyboard::Scan::Up)
                {
                    pac->set_direction(MoveDirection::UP);
                }
                else if (key_pressed->scancode == sf::Keyboard::Scan::Down)
                {
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

        game_instance->update(dt);

        window.clear();
        drawer.draw_map(game_instance->get_map_layout());
        drawer.draw_game_entities(game_instance->get_all_entities());
        drawer.draw_score(game_instance->get_score());
        window.display();
    }
}
