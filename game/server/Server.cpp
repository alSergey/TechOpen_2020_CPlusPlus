//
// Created by tsv on 18.04.19.
//

#include "Server.h"
#include "common/User.h"
#include "messages/UserInitMessage.h"

#include <SFML/System/Clock.hpp>

#include <cstring>
#include <algorithm>
#include <iostream>
#include <messages/SessionCreatedMessage.h>

Server::Server(unsigned short port)
        : m_port(port)
        , m_sessions()
        , m_listener() {
    if (m_listener.listen(m_port) != sf::Socket::Done) {
        throw std::runtime_error(std::strerror(errno));
    }
    m_listener.setBlocking(false);
}

Server::~Server() {
    m_listener.close();
}

int Server::run() {
    auto clock = sf::Clock();

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {
        accept_new_user();

        auto dt = clock.restart().asSeconds();
        for (auto session = m_sessions.begin(); session != m_sessions.end(); ++session) {
            if ((*session)->is_end()) {
                session = m_sessions.erase(session);
            } else {
                (*session)->update(dt);
            }
        }
    }
#pragma clang diagnostic pop

    return 0;
}

void Server::accept_new_user() {
    UserSocket socket = std::make_unique<sf::TcpSocket>();

    if (m_listener.accept(*socket) == sf::Socket::Done) {
        sf::Packet packet;
        socket->receive(packet);
        // FIXME: if user stuck - server stuck too

        UserInitMessage message;
        packet >> message;

        std::cout << "New user: " << message.username << " " << static_cast<int>(message.action) << " "
                  << message.session_id << std::endl;

        UserPtr user = std::make_shared<User>(message.username, std::move(socket));

        switch (message.action) {
            case UserInitMessage::Create: {
                SessionPtr session = std::make_shared<Session>();
                session->add_user(user);

                m_sessions.push_back(session);

                SessionCreatedMessage response{session->get_id()};

                packet.clear();
                packet << response;

                user->send_packet(packet);

                break;
            }
            case UserInitMessage::Join: {
                auto session = std::find_if(
                        m_sessions.begin(), m_sessions.end(),
                        [&message = std::as_const(message)](const SessionPtr& session) -> bool {
                            return session->get_id() == message.session_id;
                        }
                );
                
                if (session == m_sessions.end()) {
                    // TODO: send error message
                    break;
                }

                (*session)->add_user(user);

                break;
            }
        }
    }
}

