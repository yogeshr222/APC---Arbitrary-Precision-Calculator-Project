apc.exe : main.o addition.o subtraction.o multiplication.o division.o my_func.o
	gcc -o apc.exe main.o addition.o subtraction.o multiplication.o division.o my_func.o

main.o : main.c apc.h
	gcc -c main.c

addition.o : addition.c apc.h
	gcc -c addition.c

subtraction.o : subtraction.c apc.h
	gcc -c subtraction.c

multiplication.o : multiplication.c apc.h
	gcc -c multiplication.c

division.o : division.c apc.h
	gcc -c division.c

my_func.o : my_func.c apc.h
	gcc -c my_func.c

clean :
	rm *.exe *.o