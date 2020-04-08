#!/bin/bash
# This is a comment!

k = "\n"
for sp in 10 100 1000 10000 100000 1000000 10000000 100000000
do
    for j in 1 2 3 4 5 6 7 8
    do
        for n in 100 1000 2000 3000 4000 5000 6000 7000
        do
            ./main.o $n #>> data.csv
        done
        echo $k #>> data.csv
    done
    echo $k
    echo $k
    echo $k
done
