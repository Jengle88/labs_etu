CC=gcc
FLAGS=-c

build_proj: build_all clean

build_all: start.o sentence.o text.o word.o
	$(CC) start.o sentence.o text.o word.o -o START

start.o: start.c
	$(CC) $(FLAGS) start.c

sentence.o: sentence.c sentence.h
	$(CC) $(FLAGS) sentence.c

text.o: text.c text.h
	$(CC) $(FLAGS) text.c

word.o: word.c word.h
	$(CC) $(FLAGS) word.c

clean:
	rm -f *.o
