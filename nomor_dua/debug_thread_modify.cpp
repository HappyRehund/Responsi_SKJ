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

    //tunggu thread selesai sebelum program selesai
    t.join();
    return 0;
}