#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <jsoncpp/json/json.h>

int main() {
    // Create a JSON object
    Json::Value mess;
    mess["id"] = 33;
    mess["test"] = 1;
    mess["box"] = 0;
    mess["SN"] = "sn012345678901234567890";

    // Convert the JSON object to a string
    std::string json_str = Json::FastWriter().write(mess);

    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Set up the server address and port
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr("SERVER_IP_ADDRESS");
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        std::cerr << "Error connecting to server" << std::endl;
        return 1;
    }

    // Send the JSON data over the socket
    if (send(sock, json_str.c_str(), json_str.size(), 0) < 0) {
        std::cerr << "Error sending data" << std::endl;
        return 1;
    }

    // Close the socket
    close(sock);

    return 0;
}
 
