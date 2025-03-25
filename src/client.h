#pragma once
#include <SFML/Network.hpp>

class Client
{
public:
    Client();
    ~Client() = default;
    void connect_to_server();
    void exit_app();
    void show_window();

private:
    const  sf::IpAddress server_ip = {192, 168, 0, 123};
    static constexpr auto port = 53000;
    static constexpr auto buff_size = 1024;
    // TODO copy in server module/class, shall be shared
    sf::TcpSocket socket;
    std::array<char, buff_size> buff_in{};
    std::array<char, buff_size> buff_out{};
    std::size_t received{};
};