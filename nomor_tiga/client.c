#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080 

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};

    // Langkah 1 : Membuat socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0){
        perror("Error creating socket");
        return 1;
    }

    //Langkah 2 : Tentukan alamat server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //Langkah 3 : Terhubung ke server
    if(connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error connection to server");
        close(client_fd);
        return 1;
    }

    printf("Connected to server...\n");

    //Langkah 4 : Terima Pesan dari server
    if(read(client_fd, buffer, sizeof(buffer)) < 0){
        perror("Error reading from server");
    } else {
        printf("Message from server: %s\n", buffer);
    }

    //Langkah 5 : Tutup koneksi
    close(client_fd);

    return 0;
}