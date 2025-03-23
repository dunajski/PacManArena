#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

int run_client()
{
    sf::TcpSocket socket;

    if (const sf::Socket::Status status = socket.connect({192, 168, 0, 123}, 53000); status != sf::Socket::Status::Done)
    {
        // TODO improve error handling
        std::cout << "Connection failed" << std::endl;
        return 0;
    }

    std::cout << "Connected" << std::endl;
    std::array<char, 1024> buffer{};
    if (std::size_t received = 0; socket.receive(buffer.data(), buffer.size(), received) != sf::Socket::Status::Done)
        return 0; // TODO improve error handling
    std::cout << "Message received from the server: " << std::quoted(buffer.data()) << std::endl;

    static constexpr std::string_view client_message = "Hello from client!";
    if (socket.send(client_message.data(), client_message.size()) != sf::Socket::Status::Done)
        return 0; // TODO improve error handling

    std::cout << "Message sent to the server: " << std::quoted(client_message.data()) << std::endl;

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

    return 0;
}