#!/bin/bash

for i in 1 2 4
do
    line="======================================================="
    if [ $i -eq 1 ]
    then
        echo $line > test_output.txt
    else
        echo $line >> test_output.txt
    fi
    echo "$i core" >> test_output.txt
    echo "=======================================================" >> test_output.txt
    basic_total=0

    for j in 1 2 3 4 5 6 7 8 9 10
    do
        time_basic=$(./column1 $i 400 1000 0.01 1000 g | tail -n 1)
        echo -en "Basic-$j: $time_basic\n" >> test_output.txt
        # total_time_basic=$(echo "$total_time_basic + $time_basic" | bc)
    done

    # average_basic=$(echo "scale=6; $total_time_basic / 10" | bc)
    echo "" >> test_output.txt
    echo "Average of Basic $i core: " >> test_output.txt

    echo -e "=======================================================\n" >> test_output.txt


    echo "=======================================================" >> test_output.txt
    red_default_total=0

    for j in 1 2 3 4 5 6 7 8 9 10
    do
        red_def=$(./column2 $i 400 1000 0.01 1000 g | tail -n 1)
        echo -en "Reduced Default-$j: $red_def\n" >> test_output.txt
    done

    echo "" >> test_output.txt
    echo "Average of Reduced Default $i core: " >> test_output.txt
    echo -e "=======================================================\n" >> test_output.txt

    echo "=======================================================" >> test_output.txt
    red_forces_total=0

    for j in 1 2 3 4 5 6 7 8 9 10
    do
        red_force=$(./column3 $i 400 1000 0.01 1000 g | tail -n 1)
        echo -en "Reduced Forces-$j: $red_force\n" >> test_output.txt
    done

    echo "" >> test_output.txt
    echo "Average of Reduced Forces $i core: " >> test_output.txt
    echo -e "=======================================================\n" >> test_output.txt

    echo "=======================================================" >> test_output.txt
    red_all_total=0
    
    for j in 1 2 3 4 5 6 7 8 9 10
    do
        red_all=$(./column4 $i 400 1000 0.01 1000 g | tail -n 1)
        echo -en "Reduced All-$j: $red_all\n" >> test_output.txt
    done

    echo "" >> test_output.txt
    echo "Average of Reduced All $i core: " >> test_output.txt
    echo -e "=======================================================\n\n" >> test_output.txt
done