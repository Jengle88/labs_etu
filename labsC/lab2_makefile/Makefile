all: build_proj clear

build_proj: max.o min.o diff.o sum.o menu.o
	gcc max.o min.o diff.o sum.o menu.o -o menu
max.o: max.c max.h
	gcc -c max.c
min.o: min.c min.h
	gcc -c min.c
diff.o: diff.c diff.h
	gcc -c diff.c
sum.o: sum.c sum.h
	gcc -c sum.c
menu.o: menu.c
	gcc -c menu.c
clear:
	rm *.o