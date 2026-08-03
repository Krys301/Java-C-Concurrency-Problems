#pragma once

#include <condition_variable>
#include <mutex>

// A counting semaphore equivalent to the Java Semaphore class used
// throughout this repo: acquire() blocks while the internal value is 0,
// release() increments the value and wakes one waiting thread.
class Semaphore {
public:
    explicit Semaphore(int value) : value(value) {}

    void acquire() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return value > 0; });
        --value;
    }

    void release() {
        std::unique_lock<std::mutex> lock(mtx);
        ++value;
        lock.unlock();
        cv.notify_one();
    }

private:
    std::mutex mtx;
    std::condition_variable cv;
    int value;
};
