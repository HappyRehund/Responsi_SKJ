#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080 

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char *message = "Hello, Client!";

    // Langkah 1: Buat socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Error creating socket");
        return 1;
    }

    // Langkah 2: Bind socket ke port yang didefinisikan
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);  // Gunakan variabel PORT

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding socket");
        close(server_fd);
        return 1;
    }

    // Langkah 3: Listen untuk koneksi masuk
    if (listen(server_fd, 5) < 0) { // Maksimal 5 koneksi dalam antrean
        perror("Error listening on socket");
        close(server_fd);
        return 1;
    }
    printf("Listening on port %d...\n", PORT);  // Tampilkan PORT dinamis

    // Langkah 4: Terima koneksi dari client
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if (client_fd < 0) {
        perror("Error accepting connection");
        close(server_fd);
        return 1;
    }

    printf("Client connected!\n");

    // Langkah 5: Kirim pesan ke client
    if (write(client_fd, message, strlen(message)) < 0) {
        perror("Error sending message to client");
    }

    // Langkah 6: Tutup koneksi
    close(client_fd);
    close(server_fd);

    return 0;
}
