//
// Created by tsv on 18.04.19.
//

#ifndef GAME_USERINIT_H
#define GAME_USERINIT_H


#include <SFML/Network/Packet.hpp>

#include <string>


struct UserInitMessage {
    enum Action {
        Create = 0,
        Join,
    };

    Action action;
    std::string username;
    uint session_id;
};

sf::Packet& operator<<(sf::Packet& packet, const UserInitMessage& message);

sf::Packet& operator>>(sf::Packet& packet, UserInitMessage& message);

#endif //GAME_USERINIT_H
