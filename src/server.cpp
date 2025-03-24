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

/// @brief Starts the server to listen for incoming connections and handle communication.
/// @details This method begins by binding the server to the specified IP and port.
///          Then, it waits for an incoming connection from a client. Once a connection 
///          is established, the server sends a greeting message to the client and awaits 
///          a response. If any error occurs during the process (e.g., failing to listen, 
///          accept, send, or receive), the procedure is terminated and relevant error 
///          messages are logged to the console.
void Server::start()
{
    std::cout << "...listening on: " << ip.toString() << ":" << port  << std::endl;

    if (listener.listen(port, ip) != sf::Socket::Status::Done)
    {
        std::cout << "Failed to listen to. Try launch server again." << std::endl;
        return;
    }

    if (listener.accept(socket) != sf::Socket::Status::Done)
    {
        std::cout << "Failed to accept connection" << std::endl;
        return;
    }

    std::cout << "Connected: " << socket.getRemoteAddress().value() << std::endl;
    static constexpr std::string_view server_message = "Hello from server!";

    if (socket.send(server_message.data(), server_message.size()) != sf::Socket::Status::Done)
        return;

    std::cout << "Message sent to the client: " << std::quoted(server_message.data()) << std::endl;

    if (socket.receive(buff_in.data(), buff_in.size(), received) != sf::Socket::Status::Done)
        return;

    std::cout << "Message received from the client: " << std::quoted(buff_in.data()) << std::endl;
}

void Server::shutdown()
{
    listener.close();
}