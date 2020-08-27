//
// Created by tsv on 18.04.19.
//
#include "UserInitMessage.h"

sf::Packet& operator<<(sf::Packet& packet, const UserInitMessage& message) {
    return packet << message.action << message.username << message.session_id;
}

sf::Packet& operator>>(sf::Packet& packet, UserInitMessage& message) {
    int action = 0;
    packet >> action;
    message.action = static_cast<UserInitMessage::Action>(action);

    return packet >> message.username >> message.session_id;
}
