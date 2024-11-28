#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *filename = "hello.txt";
    int fd;
    struct stat file_stat;
    char *mapped_file;
    size_t file_size;

    // Langkah 1: Buka file untuk baca dan tulis
    fd = open(filename, O_RDWR); // O_RDWR untuk read dan write
    if (fd < 0) {
        perror("Error membuka file");
        return 1;
    }

    // Langkah 2: Dapatkan ukuran file
    if (fstat(fd, &file_stat) == -1) {
        perror("Error mendapatkan ukuran file");
        close(fd);
        return 1;
    }
    file_size = file_stat.st_size; // Dapatkan ukuran file

    // Langkah 3: Memory-map file
    mapped_file = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_file == MAP_FAILED) {
        perror("Error mapping file");
        close(fd);
        return 1;
    }

    // Langkah 4: Modifikasi isi file
    mapped_file[0] = 'J'; // Mengubah karakter pertama menjadi 'J'

    // Langkah 5: Sinkronisasi perubahan dan pembersihan
    if (msync(mapped_file, file_size, MS_SYNC) == -1) {
        perror("Error mensinkronisasi perubahan");
    }
    if (munmap(mapped_file, file_size) == -1) {
        perror("Error unmapping file");
    }
    close(fd);

    return 0;
}
