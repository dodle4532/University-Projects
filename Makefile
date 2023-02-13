.PHONY: all clean run
all: fin clean run
clean:
	rm *.o
run: fin
	./a.out
main.o: main.c
	gcc -c main.c
bin.o: bin.c
	gcc -c bin.c
fin : main.o bin.o
	gcc -std=c99 main.o bin.o -o a.out
