#define _WIN32_WINNT 0x0601  // Enable InetPtonA for Windows 7+

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

using namespace std;

int main() {
    WSADATA wsaData;
    SOCKET sock = INVALID_SOCKET;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    // 1. Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed: " << WSAGetLastError() << endl;
        return 1;
    }

    // 2. Create socket
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        cerr << "Socket creation error: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }

    // 3. Define server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (InetPtonA(AF_INET, "127.0.0.1", &serv_addr.sin_addr) != 1) {
        cerr << "Invalid address / Address not supported\n";
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // 4. Connect to the server
    if (connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        cerr << "Connection Failed: " << WSAGetLastError() << endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    cout << "Connected to server successfully!\n";

    // 5. Send message
    const char* message = "Hello from Client!";
    send(sock, message, strlen(message), 0);
    cout << "Message sent to server\n";

    // 6. Receive server response
    int valread = recv(sock, buffer, BUFFER_SIZE, 0);
    if (valread > 0) {
        buffer[valread] = '\0';
        cout << "Server: " << buffer << endl;
    } else {
        cerr << "Failed to receive message or connection closed.\n";
    }

    // 7. Cleanup
    closesocket(sock);
    WSACleanup();

    return 0;
}
