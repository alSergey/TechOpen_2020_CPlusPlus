//
// Created by tsv on 18.04.19.
//

#include "Session.h"

uint Session::next_id = 10;

Session::Session()
        : m_id(next_id++)
        , m_users()
        , m_messages() {
}

void Session::update(float dt) {
    for (auto& item: m_users) {
        auto& player = item.second;

        player->update(dt);

        UpdatePlayerMessage update_player_message = {
                .id=player->get_id(), .position=player->get_position()
        };

        ServerToUserMessage server_message = {.type=ServerToUserMessage::UpdatePlayer};
        server_message.value = update_player_message;

        m_messages.messages.push_back(server_message);
    }

    notify_all();
}

bool Session::is_end() {
    return m_users.empty();
}

uint Session::get_id() const {
    return m_id;
}

void Session::add_user(UserPtr user) {
    auto player = std::make_shared<Player>();
    m_users[user] = player;

    NewPlayerMessage new_player_message = {
            .id=player->get_id(), .username=user->get_username(), .position=player->get_position()
    };

    ServerToUserMessage server_message = {.type=ServerToUserMessage::NewPlayer};
    server_message.value = new_player_message;

    m_messages.messages.push_back(server_message);
}

void Session::notify_all() {
    // TODO: send ServerToUserVectorMessage message to all users
    // TODO: check user connection: if sending fails -> remove that user from m_users + add send DeletePlayerMessage to all
}

