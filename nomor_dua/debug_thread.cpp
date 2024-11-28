#include <iostream>
#include <thread>
#include <unistd.h>

void threadFunction() {
    sleep(1);
    printf("Hello\n");
}

int main() {
    //membuat thread
    std::thread t(threadFunction);

    //kembali dari main tanpa menunggu thread selesai
    return 0;
}