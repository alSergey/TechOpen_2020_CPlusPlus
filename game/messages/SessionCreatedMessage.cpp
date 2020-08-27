//
// Created by tsv on 18.04.19.
//
#include "SessionCreatedMessage.h"

sf::Packet& operator<<(sf::Packet& packet, const SessionCreatedMessage& message) {
    return packet << message.session_id;
}

sf::Packet& operator>>(sf::Packet& packet, SessionCreatedMessage& message) {
    return packet >> message.session_id;
}
