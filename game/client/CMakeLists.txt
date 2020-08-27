add_executable(client main.cpp Client.cpp ../common/User.cpp Player.cpp Object.cpp ../messages/SessionCreatedMessage.cpp
        ../messages/UserInitMessage.cpp ../messages/UserToServerMessage.cpp ../messages/ServerToUserMessage.cpp)

target_link_libraries(client ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
