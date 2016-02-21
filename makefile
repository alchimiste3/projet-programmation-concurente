#
#  makefile
#             Auteur: Quentin Laborde [qlaborde@polytech.unice.fr]
#					  Clément Sibut [clement.sibut@etu.unice.fr]
#   Date de creation: 2-02-1016 11:00:00 (Quentin)
#Dernier mise à jour: 21-02-1016 19:48 (Quentin)


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