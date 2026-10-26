CC = gcc
OBj :=$(patsubst %.c, %.o, $(wildcard *.c))
a.exe : $(OBj)
	gcc -o $@ $^
clean: 
	rm *.o *.exe