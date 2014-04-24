#!/bin/bash

rm -f *.data
rm -f time_data

for dir_name in *
do
    if [ -d "$dir_name" ]; then
        for file_name in $dir_name/*.smt.log
        do
            awk '/real:/ {print $3}'  $file_name >> "$dir_name".data
        done
    fi
done

for data_file in *.data
do
    awk 'BEGIN {sum = 0} {sum = sum + $1} END {print "'$data_file'",sum}'\
 $data_file >> time_data
done
