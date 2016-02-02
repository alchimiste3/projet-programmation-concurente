

main : Main.c Matrice.h
	gcc -std=c99 Main.c Matrice.c -o main


clean : 
	rm -f *.o *.out