#include "calculator.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <arpa/inet.h>
#endif

using namespace std;

class CalculatorServer {
private:
    int server_fd;
    int port;
    CommandProcessor processor;
    
    void initializeSocket() {
#ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw runtime_error("WSAStartup failed");
        }
#endif
    }
    
    void cleanupSocket() {
#ifdef _WIN32
        WSACleanup();
#endif
    }
    
public:
    CalculatorServer(int port = 8080) : port(port), server_fd(-1) {
        initializeSocket();
    }
    
    ~CalculatorServer() {
        stop();
        cleanupSocket();
    }
    
    bool start() {
        // Create socket
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd < 0) {
            cerr << "Socket creation failed" << endl;
            return false;
        }
        
        // Set socket options
        int opt = 1;
#ifdef _WIN32
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0) {
#else
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
#endif
            cerr << "Setsockopt failed" << endl;
            return false;
        }
        
        // Bind socket
        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);
        
        if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
            cerr << "Bind failed" << endl;
            return false;
        }
        
        // Listen for connections
        if (listen(server_fd, 3) < 0) {
            cerr << "Listen failed" << endl;
            return false;
        }
        
        cout << "Calculator server started on port " << port << endl;
        cout << "Waiting for Python GUI to connect..." << endl;
        
        return true;
    }
    
    void run() {
        sockaddr_in address;
        int addrlen = sizeof(address);
        
        while (true) {
            // Accept connection
            int client_socket;
#ifdef _WIN32
            client_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
#else
            client_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
#endif
            
            if (client_socket < 0) {
                cerr << "Accept failed" << endl;
                continue;
            }
            
            cout << "Python GUI connected" << endl;
            
            // Handle client
            handleClient(client_socket);
            
            // Close client socket
#ifdef _WIN32
            closesocket(client_socket);
#else
            close(client_socket);
#endif
            
            cout << "Python GUI disconnected" << endl;
        }
    }
    
    void handleClient(int client_socket) {
        char buffer[1024] = {0};
        
        while (true) {
            // Read command from client
            memset(buffer, 0, sizeof(buffer));
            int bytes_read = recv(client_socket, buffer, sizeof(buffer), 0);
            
            if (bytes_read <= 0) {
                break; // Client disconnected
            }
            
            string command(buffer);
            cout << "Received command: " << command << endl;
            
            // Process command
            string response = processor.processCommand(command);
            
            // Send response back to client
            send(client_socket, response.c_str(), response.length(), 0);
            
            // Check if client wants to exit
            if (response.find("EXIT") == 0) {
                break;
            }
        }
    }
    
    void stop() {
        if (server_fd >= 0) {
#ifdef _WIN32
            closesocket(server_fd);
#else
            close(server_fd);
#endif
            server_fd = -1;
        }
    }
};

int main() {
    CalculatorServer server(8080);
    
    if (!server.start()) {
        cerr << "Failed to start server" << endl;
        return 1;
    }
    
    server.run();
    
    return 0;
}
