
simulation : bin/Main.o bin/Matrice.o bin/Stats.o
	gcc -std=c99 -o simulation bin/Main.o bin/Matrice.o bin/Stats.o 

bin/Main.o : src/Main.c
	gcc -std=c99 -o bin/Main.o -c src/Main.c 

bin/Matrice.o : src/Matrice.h src/Matrice.c
	gcc -std=c99 -o bin/Matrice.o -c src/Matrice.c 
	
bin/Stats.o : src/Stats.h src/Stats.c
	gcc -std=c99 -o bin/Stats.o -c src/Stats.c 

clean : 
	rm -f simulation bin/Matrice.o bin/Stats.o bin/Main.o 