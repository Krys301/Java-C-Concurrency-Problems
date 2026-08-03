// Uses a shared data structure to track chopstick availability and protects it
// using a mutex semaphore. This ensures updates to shared state remain consistent
// and thread-safe during concurrent execution.

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
    Philosopher(int myName, int* chopSticks, Semaphore* mutex)
        : myName(myName), chopSticks(chopSticks), mutex(mutex) {}

    // This is what each philosopher thread executes
    void run() {
        bool haveChopsticks;

        while (true) {
            std::cout << "Philosopher " << myName << " thinking.\n";
            randomSleep(20000);
            std::cout << "Philosopher " << myName << " hungry.\n";

            haveChopsticks = false;

            while (!haveChopsticks) {
                mutex->acquire();

                if (chopSticks[myName] == 1 && chopSticks[(myName + 1) % 5] == 1) {
                    chopSticks[myName] = 0;             // Acquire right
                    chopSticks[(myName + 1) % 5] = 0;    // Acquire left
                    haveChopsticks = true;
                    std::cout << "Philosopher " << myName << " acquired chopsticks\n";
                }
                mutex->release();

                randomSleep(10000);  // Simulate eating activity for a random time

                mutex->acquire();
                chopSticks[myName] = 1;             // Release right
                chopSticks[(myName + 1) % 5] = 1;    // Release left
                std::cout << "Philosopher " << myName << " released both chopsticks\n";
                mutex->release();
            }
        }
    }

private:
    int myName;
    int* chopSticks;
    Semaphore* mutex;
};

int main() {
    int chopSticks[5] = {1, 1, 1, 1, 1};
    Semaphore mutex(1);

    // Create and initiate five Philosopher Thread Objects
    std::vector<Philosopher> workerThread;
    workerThread.reserve(5);
    for (int i = 0; i < 5; i++) {
        workerThread.emplace_back(i, chopSticks, &mutex);
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
