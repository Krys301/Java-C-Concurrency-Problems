// Introduces a "waiter" semaphore (room) that limits the number of philosophers
// allowed to attempt to eat at once (4 out of 5). This prevents circular waiting
// and guarantees progress, eliminating deadlock.

#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

#include "Semaphore.hpp"

namespace {
void randomSleep(int maxMillis) {
    thread_local std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> dist(0, maxMillis - 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(dist(rng)));
}
}  // namespace

// The Philosopher class implements a run() method defining the behaviour of a Philosopher thread
class Philosopher {
public:
    Philosopher(int myName, Semaphore* chopSticks, Semaphore* room)
        : myName(myName), chopSticks(chopSticks) {
        // NOTE: this preserves a bug present in the original Java source, whose
        // constructor never assigns this.room = room. There `room` was left null
        // and room.acquire() threw a NullPointerException at runtime; here `room`
        // is left as the default nullptr and room->acquire() will crash the same way.
    }

    // This is what each philosopher thread executes
    void run() {
        while (true) {
            std::cout << "Philosopher " << myName << " thinking.\n";
            randomSleep(20000);

            room->acquire();
            std::cout << "Philosopher " << myName << " entered the room\n";
            chopSticks[myName].acquire();            // Acquire right
            chopSticks[(myName + 1) % 5].acquire();   // Acquire left

            std::cout << "Philosopher " << myName << " eating.\n";
            randomSleep(10000);  // Simulate eating activity for a random time
            chopSticks[myName].release();            // Release right
            chopSticks[(myName + 1) % 5].release();   // Release left

            room->release();
            std::cout << "Philosopher " << myName << " left the room\n";
        }
    }

private:
    int myName;
    Semaphore* chopSticks;
    Semaphore* room = nullptr;
};

int main() {
    Semaphore room(4);
    // Create five Binary Semaphore Objects, initial value=1
    Semaphore chopSticks[5] = {Semaphore(1), Semaphore(1), Semaphore(1), Semaphore(1), Semaphore(1)};

    // Create and initiate five Philosopher Thread Objects
    std::vector<Philosopher> workerThread;
    workerThread.reserve(5);
    for (int i = 0; i < 5; i++) {
        workerThread.emplace_back(i, chopSticks, &room);
    }

    std::vector<std::thread> threads;
    threads.reserve(5);
    for (int i = 0; i < 5; i++) {
        threads.emplace_back(&Philosopher::run, &workerThread[i]);
    }
    for (auto& t : threads) {
        t.join();
    }
    return 0;
}
