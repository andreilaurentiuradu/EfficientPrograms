#!/bin/bash
echo "Please enter source file"
read source_file
g++ implementations/${source_file}.cpp -o binaries/$source_file
timestamp=$(date "+%Y-%m-%d%H:%M:%S")
out_dir=benchmarks/${source_file}_${timestamp}
mkdir "$out_dir"
for dir in datasets/*; do
	test_name=${dir#'datasets/'}
	echo "Benchmarking $test_name"
	perf stat -j -e branches,branch-misses,bus-cycles,cache-misses,cache-references,cpu-cycles,instructions,ref-cycles,alignment-faults,bpf-output,cgroup-switches,cs,cpu-clock,cpu-migrations,emulation-faults,major-faults,minor-faults,page-faults,task-clock,duration_time,user_time,system_time ./binaries/$source_file > /dev/null 2> $out_dir/${test_name}.json
done
python3 benchmark_summary.py $source_file
rm $out_dir -r