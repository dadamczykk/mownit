all:
	gcc -Wall -I/usr/local/include -c multiplication.c
	gcc multiplication.o -lgsl -lgslcblas -lm -o multiplication

prepare:
	LD_LIBRARY_PATH=/usr/local/lib
	export LD_LIBRARY_PATH

run:
	make all
	rm -f multiplication.o
	./multiplication > times_c.csv
