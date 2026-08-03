cmake_minimum_required(VERSION 3.10)
project(DiningPhilosophers CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

foreach(variant Baseline Waiter Order Mutex)
    add_executable(dining_philosophers_${variant} src/DiningPhilosophers_${variant}.cpp)
    target_link_libraries(dining_philosophers_${variant} PRIVATE Threads::Threads)
endforeach()
