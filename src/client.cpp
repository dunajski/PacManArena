#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "client.h"

Client::Client()
{
    std::cout << "Client is starting..." << std::endl;
}

void Client::init_connection_and_run()
{
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
    this->send_to_server(client_message.data());
    std::cout << "Message sent to the server: " << std::quoted(client_message.data()) << std::endl;

    // I want to use non-blocking socket to run checking every 10 ms, I know that I could use threads
    // ,but I want to use something simpler
    this->selector.add(socket);
    socket.setBlocking(false);

    // now start rendering and handle data between connected client and server
    this->run_game();
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
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "SFML TEST 1");
    window.setFramerateLimit(144);

    while (window.isOpen() && is_connected)
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

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

        window.clear();
        window.display();
    }
}
