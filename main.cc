#include "wait.hh"
#include <thread>

InterruptableSleep is;

void sleep_thread() {
    std::cout << "sleep 10 second" << std::endl;
    is.wait_ms(10000);
    std::cout << "sleep_threa exit" << std::endl;
}

int main() {
    std::thread th(sleep_thread);
    std::cout << "sleep for 3 sec in main thread" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    is.stop();
    th.join();
    return 0;
}
