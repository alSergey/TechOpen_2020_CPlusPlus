//
// Created by tsv on 18.04.19.
//

#ifndef GAME_USER_H
#define GAME_USER_H

#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/Packet.hpp>

#include <memory>

using UserSocket = std::unique_ptr<sf::TcpSocket>;

class User {
public:
    User(const std::string& username, UserSocket socket);

    const std::string& get_username() const;

    void send_packet(sf::Packet& packet);

    sf::Socket::Status receive_packet(sf::Packet& packet);

private:
    std::string m_username;
    UserSocket m_socket;
};

using UserPtr = std::shared_ptr<User>;

#endif //GAME_USER_H
