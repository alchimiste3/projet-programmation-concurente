
main : bin/Main.o bin/Matrice.o
	gcc -std=c99 -o main bin/Main.o bin/Matrice.o 

bin/Main.o : src/Main.c
	gcc -std=c99 -o bin/Main.o -c src/Main.c 

bin/Matrice.o : src/Matrice.h src/Matrice.c
	gcc -std=c99 -o bin/Matrice.o -c src/Matrice.c 

clean : 
	rm -f main