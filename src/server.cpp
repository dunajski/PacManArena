#include <iostream>
#include <SFML/Network.hpp>
#include "server.h"

/// @brief Constructor for the Server class.
/// @details This constructor initializes the server by obtaining the local IP address
///          of the machine using sf::IpAddress::getLocalAddress(). This ensures that the
///          server is set up to operate on the local network.
Server::Server() : ip(sf::IpAddress::getLocalAddress().value())
{
    std::cout << "Server is starting..." << std::endl;
}

/// @brief Starts the server and listens for incoming client connections.
/// @details This function initializes the server's listening socket, adds the socket 
///          to a sf::SocketSelector to monitor multiple connections, and enters a loop
///          to handle client connections and messages. 
///          - Listens for client connection requests.
///          - Accepts connections from new clients and sends a welcome message.
///          - Receives data from clients and processes their messages.
///          - Handles client disconnection.
///
/// @note This function operates in a loop, so it will block until the server is shut down.
///       The function uses a non-blocking mechanism (via sf::SocketSelector) to avoid 
///       resource wastage during idle periods.
///
void Server::start()
{
    std::cout << "...listening on: " << ip.toString() << ":" << port  << std::endl;

    if (listener.listen(port, ip) != sf::Socket::Status::Done)
    {
        std::cout << "Failed to listen to. Try launch server again." << std::endl;
        return;
    }

    selector.add(listener);

    running = true;

    // TODO there is no quit here
    while (running)
    {
        // selector.wait - waits until one or more sockets are ready
        if (selector.wait(sf::seconds(0.1)))
        {
            // check listener socket if there is a new client to connect
            if (selector.isReady(listener))
            {
                auto client = std::make_unique<sf::TcpSocket>();
                if (listener.accept(*client) == sf::Socket::Status::Done)
                {
                    std::cout << "Connected: " << client->getRemoteAddress().value() << std::endl;

                    selector.add(*client);
                    clients.push_back(std::move(client));

                    static constexpr std::string_view server_message = "Hello from server!";
                    if (clients.back()->send(server_message.data(), server_message.size()) != sf::Socket::Status::Done)
                    {
                        std::cout << "Failed to send welcome message to client" << std::endl;
                    }
                    else
                    {
                        std::cout << "Welcome message sent to client" << std::endl;
                    }
                }
            }

            // check for messages from clients
            for (auto c = clients.begin(); c != clients.end();)
            {
                sf::TcpSocket& client = **c;

                if (selector.isReady(client))
                {
                    // client has sent some data
                    std::size_t received;
                    sf::Socket::Status status = client.receive(buff_in.data(), buff_in.size(), received);

                    if (status == sf::Socket::Status::Done)
                    {
                        std::cout << "Message from client " << client.getRemoteAddress().value()
                                  << ": " << std::quoted(buff_in.data()) << std::endl;

                    }
                    else if (status == sf::Socket::Status::Disconnected)
                    {
                        std::cout << "Client disconnected: " << client.getRemoteAddress().value() << std::endl;
                        selector.remove(client);
                        c = clients.erase(c);
                        continue;
                    }
                }

                ++c;
            }

        }
    }
}

void Server::shutdown()
{
    running = false;

    // Close all client connections
    for (auto& client : clients)
    {
        selector.remove(*client);
        client->disconnect();
    }
    clients.clear();

    // Close the listener
    selector.remove(listener);
    listener.close();

    std::cout << "Server shutdown complete" << std::endl;
}