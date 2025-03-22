#include <iostream>
#include <SFML/Network.hpp>

sf::TcpListener listener;

int run_server()
{
    sf::TcpListener listener;
    std::cout << "Listening on port 53000..." << std::endl;

    // bind the listener to a port
    if (listener.listen(53000) != sf::Socket::Status::Done)
    {
        // error...
    }

    // accept a new connection
    sf::TcpSocket client;
    if (listener.accept(client) != sf::Socket::Status::Done)
    {
        // error...
    }

    // use "client" to communicate with the connected client,
    // and continue to accept new connections with the listener

    return 0;
}