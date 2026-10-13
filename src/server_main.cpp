#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdio>
#include <iostream>

int main() {
    const int port = 5000;

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::perror("socket");
        return 1;
    }

    //restart the server right away without "Address already in use"
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));


    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons(port);

    if (bind(server_fd, reinterpret_cast<sockaddr*>(&address), sizeof(address)) == -1) {
        std::perror("bind");
        close(server_fd);
        return 1;
    }


    if (listen(server_fd, 1) == -1) {
        std::perror("listen");
        close(server_fd);
        return 1;
    }
    std::cout << "Listening on port " << port << "..." << std::endl;


    int client_fd = accept(server_fd, nullptr, nullptr);
    if (client_fd == -1) {
        std::perror("accept");
        close(server_fd);
        return 1;
    }
    std::cout << "Client connected" << std::endl;


    char buffer[1024];
    while (true) {
        ssize_t bytes = recv(client_fd, buffer, sizeof(buffer), 0);

        if (bytes > 0) {
            std::cout << "[recv got " << bytes << " bytes]" << std::endl;
            std::cout.write(buffer, bytes);
        } else if (bytes == 0) {
            std::cout << "Client disconnected" << std::endl;
            break;
        } else {
            std::perror("recv");
            break;
        }
    }


    close(client_fd);
    close(server_fd);
    return 0;
}