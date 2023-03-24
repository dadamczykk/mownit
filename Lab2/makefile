all:
	gcc -Wall -I/usr/local/include -c ex3.c
	gcc ex3.o -lgsl -lgslcblas -lm -o ex3

prepare:
	LD_LIBRARY_PATH=/usr/local/lib
	export LD_LIBRARY_PATH

run:
	make all
	rm -f ex3.o
	./ex3 > report.txt
