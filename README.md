# Dining Philosophers Problem (Java Concurrency)

This project demonstrates multiple solutions to the classic **Dining Philosophers** synchronization problem using **Java threads and semaphores**.  
The focus is on **deadlock prevention**, correctness under contention, and comparing alternative concurrency strategies.

---

## 🎯 Objective

The goal of this project is to simulate philosophers competing for limited shared resources (chopsticks/forks) while ensuring:

- No deadlock (system never freezes)
- Safe resource sharing (mutual exclusion)
- Correct multithreaded execution under concurrency
- Clear, testable behaviour through logging

---

## 🧠 Core Concepts Covered

- Multi-threaded programming in Java (`Thread`)
- Synchronization using `Semaphore`
- Deadlock conditions:
  - Mutual Exclusion
  - Hold and Wait
  - No Preemption
  - Circular Wait
- Deadlock prevention strategies

---

## 🛠️ Software & Synchronization

Each philosopher is implemented as a thread which cycles through:

1. Thinking
2. Hungry
3. Acquire chopsticks
4. Eating
5. Release chopsticks

### Solution Variants Included

✅ **1) Baseline (Deadlock-Prone)**
- Each philosopher acquires chopsticks in the same order.
- Demonstrates the classic deadlock risk.

File: `DiningPhilosophers_Baseline.java`

✅ **2) Waiter / Butler Semaphore Solution (Deadlock Prevention)**
- Uses a semaphore `room = new Semaphore(4)` to limit how many philosophers may attempt to eat at the same time.
- Prevents circular wait → guarantees progress.

File: `DiningPhilosophers_Waiter.java`

✅ **3) Odd/Even Chopstick Ordering Solution**
- Even philosophers pick up forks in one order, odd philosophers in reverse.
- Breaks circular wait by enforcing inconsistent order.

File: `DiningPhilosophers_Order.java`

✅ **4) Mutex + Shared State Solution**
- Shared integer array tracks chopstick availability.
- A mutex semaphore ensures state updates happen safely.

File: `DiningPhilosophers_Mutex.java`

---

## ✅ Results

- Successfully implemented multiple synchronization strategies
- Demonstrated understanding of deadlock formation and prevention
- Verified behaviour through repeated concurrent execution with logging
- Reinforced practical concurrency foundations in Java

---

## 🚀 Future Improvements

- Add starvation prevention and fairness guarantees
- Add configurable number of philosophers (N)
- Add structured testing:
  - runtime stress tests
  - detection of deadlock conditions
- Improve logging and performance metrics

---

## ▶️ How to Run

Compile & run a chosen version:

```bash
javac src/DiningPhilosophers_Waiter.java
java DiningPhilosophers
