// This is the file DiningPhilosophers_Baseline.cpp
// Study the class Semaphore (Semaphore.hpp) and the class Philosopher given below.
// A Semaphore object maintains a private integer which can only be accessed by the
// operations acquire and release. These are guarded by a mutex so they execute
// indivisibly when invoked by different threads. The Philosopher class defines a
// run() method that is executed on its own thread.
//
// Each philosopher attempts to pick up the right chopstick then the left chopstick.
// This naive implementation can cause circular wait, leading to a deadlock where
// all philosophers hold one chopstick and wait forever.

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
    Philosopher(int myName, Semaphore* chopSticks)
        : myName(myName), chopSticks(chopSticks) {}

    // This is what each philosopher thread executes
    void run() {
        while (true) {
            std::cout << "Philosopher " << myName << " thinking.\n";
            randomSleep(20000);
            std::cout << "Philosopher " << myName << " hungry.\n";
            chopSticks[myName].acquire();            // Acquire right
            chopSticks[(myName + 1) % 5].acquire();   // Acquire left
            std::cout << "Philosopher " << myName << " eating.\n";
            randomSleep(10000);  // Simulate eating activity for a random time
            chopSticks[myName].release();            // Release right
            chopSticks[(myName + 1) % 5].release();   // Release left
        }
    }

private:
    int myName;
    Semaphore* chopSticks;
};

int main() {
    // Create five Binary Semaphore Objects, initial value=1
    Semaphore chopSticks[5] = {Semaphore(1), Semaphore(1), Semaphore(1), Semaphore(1), Semaphore(1)};

    // Create and initiate five Philosopher Thread Objects
    std::vector<Philosopher> workerThread;
    workerThread.reserve(5);
    for (int i = 0; i < 5; i++) {
        workerThread.emplace_back(i, chopSticks);
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
