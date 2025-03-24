    #include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "client.h"

Client::Client()
{
    std::cout << "Client is starting..." << std::endl;
}

void Client::connect_to_server()
{
    if (const sf::Socket::Status status = socket.connect(server_ip, port); status != sf::Socket::Status::Done)
    {
        std::cout << "Connection failed" << std::endl;
        return;
    }

    std::cout << "Connected" << std::endl;
    std::array<char, 1024> buffer{};
    if (std::size_t received = 0; socket.receive(buffer.data(), buffer.size(), received) != sf::Socket::Status::Done)
        return;
    std::cout << "Message received from the server: " << std::quoted(buffer.data()) << std::endl;

    static constexpr std::string_view client_message = "Hello from client!";
    if (socket.send(client_message.data(), client_message.size()) != sf::Socket::Status::Done)
        return; // TODO improve error handling

    std::cout << "Message sent to the server: " << std::quoted(client_message.data()) << std::endl;
}

void Client::show_window()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "SFML TEST 1");
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}


