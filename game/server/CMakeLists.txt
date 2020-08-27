add_executable(server main.cpp Server.cpp Session.cpp ../common/User.cpp ../messages/UserInitMessage.cpp
        ../messages/SessionCreatedMessage.cpp GameObject.cpp Player.cpp ../messages/UserToServerMessage.cpp)

target_link_libraries(server ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
