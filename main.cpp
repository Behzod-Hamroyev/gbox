#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "Student.h"
#include "Faculty.h"
#include "Administration.h"
#include "Registration.h"

using namespace std;

void startServer() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[1024] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        cerr << "Socket creation failed." << endl;
        return;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        cerr << "Bind failed." << endl;
        return;
    }

    if (listen(server_fd, 3) < 0) {
        cerr << "Listen failed." << endl;
        return;
    }

    cout << "Server listening on port 8080..." << endl;

    socklen_t addrlen = sizeof(address);
    new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    if (new_socket < 0) {
        cerr << "Accept failed." << endl;
        return;
    }

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        read(new_socket, buffer, sizeof(buffer));
        cout << "Client: " << buffer << endl;

        string response;
        cout << "You: ";
        getline(cin, response);
        send(new_socket, response.c_str(), response.size(), 0);
    }

    close(new_socket);
    close(server_fd);
}

void startClient() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cerr << "Socket creation error" << endl;
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        cerr << "Connection failed" << endl;
        return;
    }

    while (true) {
        string message;
        cout << "You: ";
        getline(cin, message);
        send(sock, message.c_str(), message.size(), 0);

        memset(buffer, 0, sizeof(buffer));
        read(sock, buffer, sizeof(buffer));
        cout << "Server: " << buffer << endl;
    }

    close(sock);
}

int main() {
    srand(time(0));
    vector<unique_ptr<UniversityMember>> users;

    while (true) {
        string option;
        cout << "\nChoose action: register / server / client / exit: ";
        cin >> option;

        if (option == "register") {
            registerUser(users);
        } else if (option == "server") {
            startServer();
        } else if (option == "client") {
            startClient();
        } else if (option == "exit") {
            break;
        } else {
            cout << "Invalid option." << endl;
        }
    }

    return 0;
}
