  <p><b><h1>Dining Philosophers (C++ Concurrency)</h1></b><br>
  Multiple implementations of the classic Dining Philosophers synchronization problem using C++ threads (std::thread) and semaphores. 
  Focused on understanding deadlock, resource contention, and practical deadlock-prevention strategies.</p>

  <p>Build with CMake: <code>cmake -B build && cmake --build build</code> (requires a C++17 compiler with thread support). This produces four executables: <code>dining_philosophers_baseline</code>, <code>dining_philosophers_waiter</code>, <code>dining_philosophers_order</code>, <code>dining_philosophers_mutex</code>.</p>

  <hr>

  <p><b>✅ Solution 1: Baseline (Deadlock-Prone)</b><br>
  Each philosopher attempts to pick up the left fork then the right fork. This naive implementation can cause circular wait, leading to a deadlock where all philosophers hold one fork and wait forever.</p>

  <p><b>What I learned:</b> How deadlock forms in real systems and why simply using locks without a strategy can break multithreaded programs.</p>

  <a href="src/DiningPhilosophers_Baseline.cpp">
    <img src="https://img.shields.io/badge/🔗_View_Baseline_Code-black?style=for-the-badge" alt="Baseline Code"/>
  </a>

  <hr>

  <p><b>✅ Solution 2: Waiter / Butler (Semaphore N−1)</b><br>
  Introduces a “waiter” semaphore that limits the number of philosophers allowed to attempt to eat at once (e.g., 4 out of 5). 
  This prevents circular waiting and guarantees progress, eliminating deadlock.</p>

  <p><b>What I learned:</b> How semaphores can enforce safe global constraints, and why limiting concurrent resource acquisition prevents deadlock.</p>

  <a href="src/DiningPhilosophers_Waiter.cpp">
    <img src="https://img.shields.io/badge/🔗_View_Waiter_Solution-green?style=for-the-badge" alt="Waiter Solution"/>
  </a>

  <hr>

  <p><b>✅ Solution 3: Odd/Even Fork Ordering</b><br>
  Breaks the deadlock cycle by changing the order forks are picked up. 
  For example, odd-numbered philosophers pick up the right fork first, while even-numbered philosophers pick up the left fork first. 
  This prevents circular wait by removing the possibility of a complete lock cycle.</p>

  <p><b>What I learned:</b> Deadlock prevention through ordering policies and how small protocol changes can guarantee system safety.</p>

  <a href="src/DiningPhilosophers_Order.cpp">
    <img src="https://img.shields.io/badge/🔗_View_Odd%2FEven_Solution-orange?style=for-the-badge" alt="Odd Even Solution"/>
  </a>

  <hr>

  <p><b>✅ Solution 4: Mutex + Shared State</b><br>
  Uses a shared data structure to track chopstick availability and protects it using a mutex semaphore. 
  This ensures updates to shared state remain consistent and thread-safe during concurrent execution.</p>

  <p><b>What I learned:</b> How to guard shared memory correctly, and the importance of atomic updates in multithreaded programs.</p>

  <a href="src/DiningPhilosophers_Mutex.cpp">
    <img src="https://img.shields.io/badge/🔗_View_Mutex_Solution-red?style=for-the-badge" alt="Mutex Solution"/>
  </a>

</div>
