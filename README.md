# Multithreaded-sorting implementation
## 1. Team Members and Responsibility
- Kuan, Chin-Wei (官京緯): Overall architecture & threading logic
- Chen, Ban-Ban (陳半半): Sorting function algorithm & merging logic

## 2. Project Overview
This project implements a multithreaded sorting application. It divides a list into two halves, sorts them concurrently using two separate threads, and merges the results using a third thread.

## 3. Implementation Details
- **Sorting Algorithm**: Used (TBD) for sub-list sorting.
- **Thread Synchronization**: Used `pthread_join` to ensure sorting is complete before merging.
- **Global Data**: Utilized global arrays for shared data access between threads.

## 3. Compilation and Configuration Instructions
### Environment
* **Tested on**: (TBD)
* **Requirements**: `gcc` or `clang` compiler.

### Compile the program
Enter the project folder and use the following command to compile:
```bash
gcc sort.c -o sort -pthread
```
### Run the Program
Execute the binary to display the sorted list:
```Bash
./sort
```

## 5. Test Results
### (TBD)

## 6. File Structure
* `sort.c`: Core source code.
* `README.md`: Project documentation.
* `snapshot`: Directory containing execution screenshots.
---
Author: Kuan, Chin-Wei (官京緯), Chen, Ban-Ban (陳半半)

Date: March 30, 2026