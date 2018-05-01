#!/bin/bash


number_th=(2 5 10)
number_ac=(100000 1000000 3000000)
scheds=("SCHED_OTHER" "SCHED_FIFO" "SCHED_RR")
syncs=("\/\/" "")

for sched in ${scheds[@]}; do
    sed -i "s/#define OS_SCHEDULER .*/#define OS_SCHEDULER $sched/" main.c
    for th in ${number_th[@]}; do
        for ac in ${number_ac[@]}; do
            for sync in ${syncs[@]}; do
                sed -rie "s/(\/\/|)__sync_synchronize\(\);/$sync __sync_synchronize\(\);/g" *
                make
                echo SCHEDULER: $sched
                echo THREADS: $th
                echo ACCESS: $ac
                echo SYNC: $sync
                ./main $th $ac
            done
        done
    done
done
