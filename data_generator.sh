#! /bin/bash

echo "Enter number of different strings, and file sizes for file 1, 2, 3, and 4 respectively, separated by space:"
read n_strings a b c d

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
