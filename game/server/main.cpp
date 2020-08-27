//
// Created by tsv on 18.04.19.
//

#include <iostream>
#include "Server.h"

int main(int ac, const char* av[]) {
    if (ac < 2) {
        std::cerr << "Usage: " << av[0] << " <port>" << std::endl;
        return -1;
    }

    auto port = static_cast<unsigned short>(std::stoul(std::string(av[1])));

    Server server(port);
    return server.run();
}