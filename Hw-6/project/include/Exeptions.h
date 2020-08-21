#pragma once

#include <exception>
#include <string>

class GameException: public std::exception {
 public:
    explicit GameException(const std::string& msg)
            : m_msg(msg) {}

    const char* what() const noexcept override {
        return m_msg.c_str();
    }

 private:
    std::string m_msg;
};


class InvalidFileOperation: GameException {
 public:
    InvalidFileOperation()
    : GameException("Can't work with file") {
    }
};
