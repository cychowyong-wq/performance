# Performance Measurement
The goal of this project is to step by step example to measure the efficiency of a code and optimize it.
This project use matrix multiplication as example, assume same interface for implementation to perform calculation of matrix A (m x n) multiply matrix B (n x b) to get a result matrix Dest (m x b). Different approach to the same problem might shows different result, and profiling in this project will help to see the difference between each implementation.  

## Quick Start
- This project assume the user to be able to run simple perf and make c code by its own.
- RUN `make verify-<implement>` for example, `make verify-naive` to verify implementation
- RUN `make profile-<implement>` for example, `make profile-naive` to profile and benchmark implementation

### Optimization Process
1. Create a function with naive approach. 
    - Define and standardize the function name and parameter for different approach.
2. Benchmark its execution time, and profile its cpu cycle, instructions, cache miss, and branch miss.
    - Perf record is used for measurement.
    - RUN `make profile` or `make profile-<implement>`
3. Implement other algorithm that might improve.
4. Verify the correctness of new method with naive approach(golden reference).
    - RUN `make verify` or `make verify-<implement>`
6. Repeat (2. to last.) until acceptable performance.  

## Documentation
### Modular Design
- the idea is to make each implementation like a plugin, all share a common interface defined in `/implementation/implementation.h`, each implementation will also locate under same directory
- A tradeoff is made when choosing implementation method, instead of using function pointer to point to different implementation, which is faster to implement, a more complicated Makefile is used which standardize verify and profiling method in each case. 

### Perf
- Perf is an important tool to profiling an executable, it shows cache, branch, cpu, hw events, and a whole lot of other metrics.  
- the most simple way to use perf is `perf stat` or `perf record` which in most of the case is enough to collect the performance of an executable.
- Normally, it is not so useful to know the exact value of a metrics like cache miss, since it includes the part of code you dont want to measure like initialization, the noise from cpu/process schdule, hardware specs and etc. The exact value of metrics only shows a possible trend, but comparative value is valuable to compare two executable.
- In this project, perf is controlled to only enable after benchmarking. Ideally, separation of benchmarking, verification and profiling is a cleaner way to measure each metrics. Profiling can run perf stat and the executable alone. This project use perf_ctl.fifo and perf_ack.fifo to control when to start and stop profiling, so that profiling and benchmark can be combined together in single executable and avoid pollution.


### Example output
| Algorithm    | Execution Time (us) | Insn per cycle | branch miss (k) | cache miss (k) |
| -------- | ------- | ------- | ------- | ------- |
| Naive  | 131,544 | 2.17 | 6,895 | 1,867 |
| submatrix | 85,463 | 4.39 | 494 | 1,069 |
