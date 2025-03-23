#include <iostream>
#include <SFML/Network.hpp>

sf::TcpListener listener;

int run_server()
{
    sf::TcpListener listener;
    std::cout << "Listening on port 53000..." << std::endl;


    // Retrieve and print the server's IP address
    sf::IpAddress const server_ip = sf::IpAddress::getLocalAddress().value();
    std::cout << "Server is running on: " << server_ip.toString() << std::endl;
    // bind the listener to a port
    if (listener.listen(53000, server_ip) != sf::Socket::Status::Done)
    {
        // TODO improve error handling
        return 0;
    }

    // accept a new connection
    sf::TcpSocket socket;
    if (listener.accept(socket) != sf::Socket::Status::Done)
    {
        // TODO improve error handling
        return 0;
    }

    std::cout << "Connected: " << socket.getRemoteAddress().value() << std::endl;
    static constexpr std::string_view server_message = "Hello from server!";

    if (socket.send(server_message.data(), server_message.size()) != sf::Socket::Status::Done)
        return 0; // TODO improve error handling

    std::cout << "Message sent to the client: " << std::quoted(server_message.data()) << std::endl;

    std::array<char, 1024> buffer{};
    std::size_t received = 0;
    if (socket.receive(buffer.data(), buffer.size(), received) != sf::Socket::Status::Done)
        return 0; // TODO improve error handling

    std::cout << "Message received from the client: " << std::quoted(buffer.data()) << std::endl;

    return 0;
}