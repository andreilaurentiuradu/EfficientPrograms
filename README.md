## How to use
<b>Please note that these commands are supposed to be run on the complang server.</b>

The repository is divided into four folders: <b>benchmarks, binaries, datasets, and implementations.</b>
<li> Benchmarks: Stores the benchmarked programs for specific dates and programs, so that we can look at it again later.
<li> Binaries: Stores the executables temporarily. These should be in your gitignore since we dont wanna push binaries.
<li> Datasets: These are testcases. We got some standard testcases from the lecturer, but they are pretty rudimentary. 
<li> Implementations: This is where we store the cpp files.

### 1. Adding tests
--- 
To add your own tests, add it in its own directory under datasets/. You can use the `data_generator.sh` to do this for you. If you want to do that, you can specify the amount of unique strings, and the amount of lines in each file respectively, like so:
`./data_generator.sh`
`Enter number of different strings, and file sizes for file 1, 2, 3, and 4 respectively, separated by space:`
`100 500 500 500 500`
`echo "Creating files..."`
Beware that these tests get huge very quickly, and may bottleneck the testing process for you. Make sure to not upload large tests to github, as it will slow down development a lot. (But definitely keep in the benchmarks). You can share large tests through other means (like google drive for example). 

### 2. Correctness testing
---
In order to test the correctness of an implementation, place the file in the `implementations/` folder. Then run `./test_correctness`. It will ask for the filename in implementations, specify it <b> without the .cpp</b> at the end. E.g. to test `hashmap_join.cpp` you type `hashmap_join`. It will compile and run all the tests for you. Try it. 

### 3. Benchmarking
---
To test the performance of a specific implementation, make sure it is placed in the `implementations/` folder. Then you can run `./bm_quick` to purely show you the results of benchmarking. It saves the data, then it summarizes it with a python script, and removes the benchmark again, s.t. the `benchmarks/` folder does not get cluttered. Once you think you have a meaningful benchmark to add, run `./bm_save`, which will permanently store it under `benchmarks/`.