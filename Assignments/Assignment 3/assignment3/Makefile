all:	column1 column2 column3 column4

column1:	column1.c
	gcc -g -Wall -fopenmp -o column1 column1.c -lm

column2:	column2.c
	gcc -g -Wall -fopenmp -o column2 column2.c -lm

column3:	column3.c
	gcc -g -Wall -fopenmp -o column3 column3.c -lm

column4:	column4.c
	gcc -g -Wall -fopenmp -o column4 column4.c -lm
	./test_script.sh