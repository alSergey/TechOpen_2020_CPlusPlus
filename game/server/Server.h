//
// Created by tsv on 18.04.19.
//

#ifndef GAME_SERVER_H
#define GAME_SERVER_H


#include "Session.h"

#include <SFML/Network/TcpListener.hpp>

#include <memory>
#include <string>
#include <vector>

using Sessions = std::vector<SessionPtr>;

class Server {
public:
    explicit Server(unsigned short port);

    ~Server();

    int run();

private:
    unsigned short m_port;
    Sessions m_sessions;
    sf::TcpListener m_listener;

    void accept_new_user();
};


#endif //GAME_SERVER_H
