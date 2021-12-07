#pragma once

#include <chrono>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <iostream>

class InterruptableSleep {
public:
    void wait_ms(int milliseconds) {
        std::unique_lock lk(_wait_mux);
        auto now = std::chrono::system_clock::now();
        using namespace std::chrono_literals;
        if (_wait_cv.wait_until(lk, now + milliseconds * 1ms, [this]() { return _stopped == true; })) {
            std::cout << "stopping wait because _stopped is true" << std::endl;
        }
    }

    void stop() {
        _stopped = true;
        _wait_cv.notify_all();
    }

    void reset() {
        _stopped = false;
    }

private:
    std::condition_variable _wait_cv;
    std::mutex _wait_mux;
    std::atomic<bool> _stopped{false};
};
