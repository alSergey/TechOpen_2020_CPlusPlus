//
// Created by tsv on 18.04.19.
//
#include "UserToServerMessage.h"


sf::Packet& operator<<(sf::Packet& packet, const Direction& direction) {
    return packet << direction.up << direction.left << direction.right << direction.down;
}

sf::Packet& operator>>(sf::Packet& packet, Direction& direction) {
    return packet >> direction.up >> direction.left >> direction.right >> direction.down;
}

sf::Packet& operator<<(sf::Packet& packet, const UserToServerMessage& message) {
    packet << message.type;

    switch (message.type) {
        case UserToServerMessage::Move:
            return packet << message.direction;
    }
}

sf::Packet& operator>>(sf::Packet& packet, UserToServerMessage& message) {
    int type = 0;
    packet >> type;
    message.type = static_cast<UserToServerMessage::MessageType>(type);

    switch (message.type) {
        case UserToServerMessage::Move:
            return packet >> message.direction;
    }
}
