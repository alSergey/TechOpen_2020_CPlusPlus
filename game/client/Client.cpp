//
// Created by tsv on 18.04.19.
//

#include "Client.h"

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <cstring>

Client::Client(const std::string& host, unsigned short port, const std::string& username)
        : m_window(sf::VideoMode(800, 600), "game")
        , m_objects() {
    auto socket = std::make_unique<sf::TcpSocket>();
    if (socket->connect(sf::IpAddress(host), port) != sf::Socket::Done) {
        throw std::runtime_error(std::strerror(errno));
    }

    m_user = std::make_shared<User>(username, std::move(socket));
}

void Client::create_session() {
    sf::Packet packet;

    {
        UserInitMessage message = {UserInitMessage::Create, m_user->get_username(), 0};
        packet << message;

        m_user->send_packet(packet);
    }

    {
        packet.clear();

        while (m_user->receive_packet(packet) != sf::Socket::Done) {
        }

        SessionCreatedMessage message{};
        packet >> message;

        std::cout << "New session created. Session ID: " << message.session_id << std::endl;
    }

}

void Client::join_to(uint session_id) {
    sf::Packet packet;

    {
        UserInitMessage message = {UserInitMessage::Join, m_user->get_username(), session_id};
        packet << message;

        m_user->send_packet(packet);

        std::cout << "Joined to session " << session_id << std::endl;
    }
}

int Client::run() {
    while (m_window.isOpen()) {
        process_events();

        receive_from_server();
        render();
        send_to_server();
    }

    return 0;
}

void Client::process_events() {
    sf::Event event{};
    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed: {
                m_window.close();
                break;
            }

            default: {
                break;
            }
        }
    }

    m_direction.up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    m_direction.left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    m_direction.right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    m_direction.down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
}

void Client::receive_from_server() {
    ServerToUserVectorMessage message;

    /* TODO: implement me
     * receive ServerToUserVectorMessage, parse it, and apply messages to objects
     *
     * NB: if you receive UpdatePlayerMessage, but haven't that Player - just add it
     */

    apply_messages(message);
}

void Client::render() {
    m_window.clear();

    for (auto& obj: m_objects) {
        obj->draw(m_window);
    }

    m_window.display();
}

void Client::send_to_server() {
    UserToServerMessage message = {.type=UserToServerMessage::Move};
    message.direction = m_direction;

    sf::Packet packet;
    packet << message;

    m_user->send_packet(packet);
}

void Client::apply_messages(const ServerToUserVectorMessage& messages) {
    // TODO: implement me
}
