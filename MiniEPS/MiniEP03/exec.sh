#!/bin/bash

sz=(10 100 1000 10000 1000000)

th=(10 20 30 40 100)

for i in ${sz[@]}; do
    for j in ${th[@]}; do
        echo ----------------------------------------------------------------
        echo N_SIZE: $i
        echo N_THREADS: $j
        ./contention.sh $i $j
    done
done

