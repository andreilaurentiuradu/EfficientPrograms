#! /bin/bash

echo "Enter number of different strings, and file sizes for file 1, 2, 3, and 4 respectively, separated by space:"
read n_strings a b c d

echo "Copying files if not exists"
src_dir="/localtmp/efficient24/"
dest_dir="."

echo "Copying .csv files from $src_dir to $dest_dir if they don't already exist..."
for file in "$src_dir"*.csv; do
    if [ -e "$file" ]; then
        basefile=$(basename "$file")
        if [ ! -e "$dest_dir/$basefile" ]; then
            cp "$file" "$dest_dir/"
            echo "Copied $basefile to $dest_dir"
        else
            echo "$basefile already exists in $dest_dir, skipping."
        fi
    else
        echo "No .csv files found in $src_dir."
        break
    fi
done

echo "Creating files..."
dirname="datasets/data_${n_strings}_${a}_${b}_${c}_${d}"
mkdir $dirname
gforth -e "include generator.fs $n_strings $a $b $c $d main5 bye"
/usr/ftp/pub/anton/lvas/effizienz-aufgabe24/myjoin f1.csv f2.csv f3.csv f4.csv|sort > output.csv
mv f1.csv $dirname
mv f2.csv $dirname
mv f3.csv $dirname
mv f4.csv $dirname
mv output.csv $dirname
