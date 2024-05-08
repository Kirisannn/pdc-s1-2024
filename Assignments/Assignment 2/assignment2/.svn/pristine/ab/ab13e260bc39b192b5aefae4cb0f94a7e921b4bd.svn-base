#!/bin/bash

matrix_orders=(16 32 64 128 256 512 1024 2048 4096 8192)

echo "==========================================" > mvmult_output.txt
for i in "${matrix_orders[@]}"
do
    # Output line to say N = i and P = 4
    echo -e "N = $i, P = 1" >> mvmult_output.txt
    echo -e "$i\n$i" | mpirun -n 1 ./mvmult | tail -n 1 >> mvmult_output.txt
    echo -e "$i\n$i" | mpirun -n 1 ./mvmult | tail -n 1 >> mvmult_output.txt
    echo -e "$i\n$i" | mpirun -n 1 ./mvmult | tail -n 1 >> mvmult_output.txt
    echo "" >> mvmult_output.txt
done
echo "==========================================" >> mvmult_output.txt

echo "==========================================" >> mvmult_output.txt
for i in "${matrix_orders[@]}"
do
    # Output line to say N = i and P = 4
    echo -e "N = $i, P = 2" >> mvmult_output.txt
    echo -e "$i\n$i" | mpirun -n 2 ./mvmult | tail -n 1 >> mvmult_output.txt
    echo -e "$i\n$i" | mpirun -n 2 ./mvmult | tail -n 1 >> mvmult_output.txt
    echo -e "$i\n$i" | mpirun -n 2 ./mvmult | tail -n 1 >> mvmult_output.txt
    echo "" >> mvmult_output.txt
done
echo "==========================================" >> mvmult_output.txt

# Loop through the matrix orders for mpirun with 4 processes
echo "==========================================" >> mvmult_output.txt
for i in "${matrix_orders[@]}"
do
    # Output line to say N = i and P = 4
    echo -e "N = $i, P = 4" >> mvmult_output.txt
    echo -e "$i\n$i" | mpirun -n 4 ./mvmult | tail -n 1 >> mvmult_output.txt
    echo -e "$i\n$i" | mpirun -n 4 ./mvmult | tail -n 1 >> mvmult_output.txt
    echo -e "$i\n$i" | mpirun -n 4 ./mvmult | tail -n 1 >> mvmult_output.txt
    echo "" >> mvmult_output.txt
done
echo "==========================================" >> mvmult_output.txt