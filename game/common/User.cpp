//
// Created by tsv on 18.04.19.
//

#include "User.h"

User::User(const std::string& username, UserSocket socket)
        : m_username(username)
        , m_socket(std::move(socket)) {
    m_socket->setBlocking(false);
}

const std::string& User::get_username() const {
    return m_username;
}

void User::send_packet(sf::Packet& packet) {
    while (m_socket->send(packet) == sf::Socket::Partial) {
    }
}

sf::Socket::Status User::receive_packet(sf::Packet& packet) {
    return m_socket->receive(packet);
}
