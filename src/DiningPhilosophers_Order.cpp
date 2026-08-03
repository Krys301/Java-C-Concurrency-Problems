// Breaks the deadlock cycle by changing the order chopsticks are picked up.
// Odd-numbered philosophers pick up the right chopstick first, while even-numbered
// philosophers pick up the left chopstick first. This prevents circular wait by
// removing the possibility of a complete lock cycle.

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
    //
    // NOTE: this preserves the exact brace structure of the original Java source,
    // where the `else` binds only to the print statement that follows it (no braces),
    // so the two acquire() calls after the if/else run unconditionally for every
    // philosopher -- including even philosophers, who already acquired both
    // chopsticks in the if-block above and will now deadlock re-acquiring their
    // own already-held chopstick.
    void run() {
        while (true) {
            std::cout << "Philosopher " << myName << " thinking.\n";
            randomSleep(20000);

            if (myName % 2 == 0) {
                std::cout << "Philosopher " << myName << " is even, acquire left followed by\n";
                chopSticks[myName].acquire();            // Acquire right
                chopSticks[(myName + 1) % 5].acquire();   // Acquire left
            } else
                std::cout << "Philosopher " << myName << " is odd, acquire right followed by left\n";
            chopSticks[(myName + 1) % 5].acquire();  // Acquire left
            chopSticks[myName].acquire();            // Acquire right
            {
                randomSleep(10000);  // Simulate eating activity for a random time

                chopSticks[myName].release();            // Release right
                chopSticks[(myName + 1) % 5].release();   // Release left
            }
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
