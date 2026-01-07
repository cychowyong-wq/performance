## Performance Measurement
The goal of this project is to step by step example to measure the efficiency of a code and optimize it.

### Modular Design
- the idea is to make each implementation like a plugin, all share a common interface defined in `/implementation/implementation.h`, each implmentation will also locate under same directory
- A tradeoff is made when choosing implmentation method, instead of using function pointer to point to different implmentation, which is faster to implement, a more complicated Makefile is used which standardize verify and profiling method in each case. 

### Optimization Process
1. Create a function with native approach. 
    - Define and standardize the function name and parameter for different approach.
2. Benchmark its execution time, cpu cycle, cache miss, and branch miss.
    - Perf record is used for measurement.
    - RUN `make profile` or `make profile-<implement>`
3. Implement other algorithm that might improve.
4. Verify the correctness of new method with naive approach(golden reference).
    - RUN `make verify` or `make verify-<implement>`
4. Repeat (2. to 4.) until acceptable performance.  


## TODO
1. add native approach for matrix multiplication [done]
2. modify Makefile to run verification
3. modify Makefile to auto run pref for each implementation
4. add better approach for matrix multiplication

