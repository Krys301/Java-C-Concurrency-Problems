# Java Concurrency Problems — Dining Philosophers

This repository contains multiple implementations of the classic **Dining Philosophers** concurrency problem in **Java**, focusing on synchronization correctness and deadlock prevention strategies.

## 🧠 Objective
Model philosophers (threads) competing for shared resources (forks/chopsticks) and implement solutions that avoid deadlock while maintaining correct multithreaded execution.

## ✅ Implementations Included
- **Baseline (deadlock-prone)**  
  Demonstrates the classic deadlock scenario when all philosophers acquire forks in the same order.  
  [![View Dining Philosophers](https://img.shields.io/badge/View%20Code-Dining%20Philosophers-blue?style=for-the-badge)]([https://github.com/Krys301/Java-C-Concurrency-Problems-/blob/main/DiningPhilosophers1_Waiter.java](https://github.com/Krys301/Java-C-Concurrency-Problems/blob/main/src/DiningPhilosophers_Baseline.java))


- **Waiter / Butler solution (Semaphore N−1)**  
  Uses a semaphore to limit the number of philosophers attempting to eat simultaneously, preventing circular wait.  
  → [`DiningPhilosophers_Waiter.java`](DiningPhilosophers_Waiter.java)

- **Odd/Even fork ordering solution**  
  Breaks circular wait by enforcing different fork pickup order depending on philosopher index.  
  → [`DiningPhilosophers_Order.java`](DiningPhilosophers_Order.java)

- **Mutex + shared state solution**  
  Uses a mutex to protect a shared representation of chopstick availability.  
  → [`DiningPhilosophers_Mutex.java`](DiningPhilosophers_Mutex.java)

## 🛠️ Tech Stack
- Java
- Threads
- Semaphores / synchronization primitives

## ▶️ How to Run
Compile and run a chosen version:

```bash
javac DiningPhilosophers_Waiter.java
java DiningPhilosophers
