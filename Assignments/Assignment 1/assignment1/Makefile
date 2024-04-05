all: run1 run2

numbers1:	numbers1.c
	mpicc -g -Wall -o numbers1 numbers1.c
	mpiexec -n 5 ./numbers1

numbers2:	numbers2.c
	mpicc -g -Wall -o numbers2 numbers2.c
	mpiexec -n 5 ./numbers2