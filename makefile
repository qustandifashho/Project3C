myprogram: main.o champion.o
	gcc main.o champion.o -o myprogram
		
main.o: main.c champion.h
	gcc -c main.c -o main.o

myfunctions.o: champion.c champion.h
	gcc -c champion.c -o champion.o

clean:
	rm -rf *.o
	rm myprogram
