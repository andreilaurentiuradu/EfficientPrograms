#!/bin/bash
source_file=$1
# -pthread
g++ implementations/${source_file}.cpp -std=c++17 -o binaries/$source_file
timestamp=$(date "+%Y-%m-%d%H_%M_%S")
out_dir=benchmarks/${source_file}_${timestamp}
mkdir "$out_dir"
for dir in datasets/*; do
	test_name=${dir#'datasets/'}
	echo "Benchmarking $test_name"
	perf stat -j -e branches,branch-misses,bus-cycles,cache-misses,cache-references,cpu-cycles,instructions,ref-cycles,alignment-faults,bpf-output,cgroup-switches,cs,cpu-clock,cpu-migrations,emulation-faults,major-faults,minor-faults,page-faults,task-clock,duration_time,user_time,system_time ./binaries/$source_file $dir/f1.csv $dir/f2.csv $dir/f3.csv $dir/f4.csv > /dev/null 2> $out_dir/${test_name}.json
done
