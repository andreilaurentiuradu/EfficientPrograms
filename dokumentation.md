## File to dokument optimizations

The order of the optimizations can (and maybe should) if possible be changed. Larger improvements in the beginning are prefered.

| Implementation            | Cycles             | Comment                          |
|---------------------------|--------------------|---------------------------------|
| **Ths reference**         | 155,414,886,890    |                                  |
| **1.0_slow baseline**     | Too slow to finish |                                  |
| **1.1_hashmap_join**      | 468,443,852,089    | Use hashmap and join two files in one step |
| **1.2_hashmap_all_together** | 285,872,357,740 | Join all files at once           |
| **2.1_remove_loop_split**| 204,703,265,567 | As we only have two columns per file we do not need a loop to iterate trough a line |
| **2.2_remove_vector_split** | 177,673,673,812 | Move the split line into the read line and remove the passed vector |
| **2.3_memory_optimization** | 178,415,673,961 | No real improvement(maby dont mention it) |
| **2.4_preallocate_memory_5_mio_hashmap** | 167,637,745,777 | Prelocate the hash tables with 5 Mio unique keys |
| **2.4_preallocate_memory_7_mio_hashmap** | 157,655,530,579 | Prelocate the hash tables with 7 Mio unique keys |
| **2.4_preallocate_memory_10_mio_hashmap** | 152,262,989,084 | Prelocate the hash tables with 10 Mio unique keys |
| **2.4_preallocate_memory_30_mio_hashmap** | 139,615,569,026 | Prelocate the hash tables with 30 Mio unique keys |
| **2.4_preallocate_memory_100_mio_hashmap** | 157,639,470,511 | Prelocate the hash tables with 100 Mio unique keys |
| **2.5_buffer_output** | 142,024,248,870 | Dont cout for all iterations. Save them in a buffer. (Prelocate 30Mio) |

Our Optimizing is not always ellegant. We optimize not for all data but for exactly the data_reference.

**The bottleneck at this version is the creation of the hashmap.**(When we remove the for loop from the file we can run the benchmark and get the cycles the program needs for the loading and the creation of the hashmap)

We can also include optimizations that did not improve our program. (e.g. loop unrolling from the lecture is probably already done by the compiler)

2.4.1 165268697875
2.4.2 140894615144 starter
2.4.3 151018219603
3.0 Add buffer size for iostream 
    using 2.4.2 as skel : 138298968968

3.1 
136601103826
138515627345
135365369065
in benchmark we have: 140032593378
- verify number of arguments
- add try catch error handler
- output buffer with preallocation
- intermediary buffer for reading (line)

3.2
135685574101
133536138358
135789105029
- optimizing for loops with loop unrolling

3.3
139877263271
- common subexpression elimination (small differences)

3.4
157612803132
- tried to parallize reading the data (worse results than before)

3.5 
144079554918
- no improvement of removing substr calls and append calls

3.6
184236371124
- increased cpu cycle for large dataset, for small decreased

3.7
161477113968
- robin hood map increased cpu cycle a bit but lowers instruction cycles

3.8
- not providing right output yet, needs to be further debugged but could decrease cpu cycles bc of hash lookups and comparisons

3.9
- not providing right output yet, needs to be further debugged but could decrease cpu cycles bc of hash lookups and comparisons