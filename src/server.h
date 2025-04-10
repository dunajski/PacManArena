#pragma once
#include <SFML/Network.hpp>

/**
 * @brief Manages server-side networking logic for handling multiple clients.
 */
class Server
{
public:
    Server();
    ~Server() = default;

    void start();
    void shutdown();

private:
    static constexpr auto port = 53000;
    static constexpr auto max_clients = 4;
    static constexpr auto buff_size = 1024;

    sf::IpAddress ip;
    sf::TcpListener listener;
    sf::SocketSelector selector;
    std::vector<std::unique_ptr<sf::TcpSocket>> clients;
    std::array<char, buff_size> buff_in{};
    std::array<char, buff_size> buff_out{};
    bool running{false};
};