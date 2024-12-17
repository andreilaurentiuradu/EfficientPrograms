## <b>16-12-2024</b>
----
### Presentation 1

* Optimized mainly I/O and Join operations
* Prioritized CPU-Cycles (Said memory and time are not relevant)
* Used C++

#### General optimizations
- Avoiding to copy move values
- Avoid resizing of dynamic data structurs
- Use contiguous memory 

#### Other improvements, unordered
- Unordered multimap
    - Because one key can have multiple values
    - Performance of hash function is important
    - Avoid rehashing

- Divide & Conquer did not show improvements
- Sort merge also did not show promising results
- Naive approach (~132 Billion Cycles)
- Used asyncio for loading files 
    - less time but more cycles
- Used different hash function (SIMD)
    - Was not faster
- Try to estimate the file size
    - preemptively allocate memory
    - adjust load factor of hashmap
- Print directly to stdout
- use mmap to load entire file into memory at once
- used custom data structure to compare strings efficiently

=====
### Presentation 2

- Keep arrays on the stack instead of heap (not sure if u can do this in cpp)
- Efficient hashfunction
- Only output string once
    - <b> ask them how did they did this, because you need to store intermediate results right?
- pre-allocate hashmaps
- entry api is slow (rust specific)
- store strings on the stack instead of heap (rust specific)
- store vetors on the stack ..
- <b> Use one hashmap for the first three files </b>
- optimized for the specific file 
- buffered output
- final: 30b cycles (impressive)
- <b> highlighted what worked well and what didnt </b>
- <b> they did all benchmarks once, leading to high variance in the benchmarks -> maybe we could do multiple to decrease variance </b>
====
#### Presentation 3

- They tried python but didnt work
    - GIL restricted parallellism ( i think they didnt use processes )
- 

====
#### Presentation 4
- They did python too?
- oh but did collission attack
- they essentially implemented a bitcoin miner but didnt parallelize on the gpu


====
## Takeaways
- Nobody benchmarked on multiple instances
- Nobody compared C++ code to Assembly code
- All the code was hard to read / follow
- Individiual speedup ideas listed above