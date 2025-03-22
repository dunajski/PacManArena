#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

int run_client()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "SFML TEST 1");
    window.setFramerateLimit(144);

    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect({192, 168, 0, 5}, 53000);
    if (status != sf::Socket::Status::Done)
    {

    }
    else
    {
        std::cout << "Connected" << std::endl;
    }

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