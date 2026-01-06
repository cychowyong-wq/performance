## Performance Measurement
---
The goal of this project is to step by step example to measure the efficiency of a code and optimize it.


### Optimization Process
1. Create a function with native approach. 
    - Define and standardize the function name and parameter for different approach.
2. Benchmark its execution time, cpu cycle, cache miss, and branch miss.
    - Perf record is used for measurement.
    - RUN `make profile`
3. Implement other algorithm that might improve.
4. Verify the correctness of new method with naive approach(golden reference).
    - RUN `make verify`
4. Repeat (2. to 4.) until acceptable performance.  


---
## TODO
1. add native approach for matrix multiplication
2. modify Makefile to run verification
3. modify Makefile to auto run pref for each implementation
4. add better approach for matrix multiplication

