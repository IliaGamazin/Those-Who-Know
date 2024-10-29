#include "../inc/server.h"
 
int main(void) {
    int server_fd;
    int server_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    char *test_msg = "Connected to MangoServer!";
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Failed to create socket!");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", 8080);

    if ((server_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    send(server_socket, test_msg, strlen(test_msg), 0);
    printf("Message sent to client\n");

    close(server_socket);
    close(server_fd);

    return 0;
}
