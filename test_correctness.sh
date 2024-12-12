#!/bin/bash
echo "(!) Please provide the sourcefile name"
read sourcefile
echo "(!) Compiling"
g++ implementations/${sourcefile}.cpp -o binaries/$sourcefile

for dir in datasets/*; do
    echo -n "Testing $dir"
    
    # Capture output of the command in 'out'
    out=$(./binaries/$sourcefile $dir/f1.csv $dir/f2.csv $dir/f3.csv $dir/f4.csv | sort | diff - $dir/output.csv)

    # Check if output is empty or if diff found differences
    if [ -z "$out" ]; then
        echo -e "\e[32m Passes\e[0m"
    else
        echo -e "\e[31m Fails\e[0m"
    fi
done

