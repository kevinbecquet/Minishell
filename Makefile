EXEC = main

all: $(EXEC)

main : main.o exe.o
	gcc -o $(EXEC) exe.o main.o

exe.o: exe.c exe.h
	gcc -c exe.c -Wall

main.o: main.c exe.h
	gcc -c main.c -Wall

clean :
	rm *.o
vclean : clean
	rm $(EXEC)
