#pragma once
#include <SFML/Network.hpp>

class Server
{
private:
    static constexpr int port = 53000;
    static constexpr int max_clients = 4;
    static constexpr int buff_size = 1024;
    sf::IpAddress ip;
    sf::TcpListener listener;
    // TODO socket, buffs, received, for each client
    sf::TcpSocket socket;
    std::array<char, buff_size> buff_in{};
    std::array<char, buff_size> buff_out{};
    std::size_t received{};

public:
    Server();
    ~Server() = default;

    void start();
    void shutdown();
};