# Nole Taxi

## TL;DR
This project implements the Nole Taxi system using two core data structures: a Min-Heap and a Red-Black Tree (RBT), coordinated through a driver program (NoleTaxi.cpp). The driver initializes both structures, parses input commands, executes taxi operations (such as insert, cancel, update, and print), and writes results to an output file. Helper functions handle individual operations, while stringUtils.h provides parsing utilities to extract arguments from input lines and dispatch the appropriate commands. The system is designed to efficiently manage ride information using synchronized nodes between the heap and the RBT.

The Min-Heap is used to efficiently retrieve the next ride based on minimum ride cost (with trip duration as a tie-breaker), supporting operations such as insert, delete, update, and heapify in O(log n) time. The Red-Black Tree stores rides ordered by rideNumber, enabling fast search, insertion, deletion, and range queries, all with logarithmic time complexity. Each RBT node maintains a pointer to its corresponding heap node, ensuring consistency across structures. Together, these data structures allow Nole Taxi operations to meet strict time and space complexity requirements while supporting advanced features like range queries and dynamic ride updates.

## Project Overview
Nole-Taxi is a software solution designed to efficiently manage and schedule taxi ride requests within a campus environment. The system maintains a strictly prioritized queue of rides while allowing for real-time updates and cancellations. 

The primary challenge of this project was to ensure that every operation—whether inserting a new ride, canceling an existing one, or retrieving the highest priority trip—executes in **O(log N)** time.

## Data Structures & Architecture
To achieve optimal performance, the system is built on two primary data structures:

### 1. Red-Black Tree (RBT)
Used for **$O(\log n)$ lookup**. The RBT stores all active rides indexed by their unique `rideID`. This allows the system to quickly find a ride for cancellation or information retrieval without scanning the entire database.

### 2. Min-Priority Heap
Used for **$O(1)$ access to the best ride**. The heap organizes rides based on their priority (calculated from ride cost and duration). This ensures the most "eligible" ride is always at the root for immediate assignment.


### Installation & Execution
* A C++ compiler (GCC/Clang) supporting C++11 or higher.
   ```bash
   git clone https://github.com/sohailuddinsyed/Nole-Taxi.git
   cd Nole-Taxi
   make
   ./noletaxi input_file.txt

