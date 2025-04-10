#pragma once
#include <SFML/Network.hpp>

/**
 * @brief Handles the client-side logic and network connection.
 */
class Client
{
public:
    Client();
    ~Client();
    void init_connection_and_run();
    void exit_app();
    void show_window();
    void send_to_server(const std::string& data);
    void run_game();

private:
    const  sf::IpAddress server_ip = {192, 168, 0, 123};
    static constexpr auto port = 53000;
    static constexpr auto buff_size = 1024;
    sf::TcpSocket socket;
    sf::SocketSelector selector;
    std::array<char, buff_size> buff_in{};
    std::array<char, buff_size> buff_out{};
    bool is_connected{false};
};