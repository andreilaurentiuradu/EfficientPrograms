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