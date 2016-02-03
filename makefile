

main : Main.c Matrice.h Matrice.c
	gcc -std=c99 Main.c Matrice.c -o main


clean : 
	rm -f main