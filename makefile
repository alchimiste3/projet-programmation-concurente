

main : Main.c 
	gcc -std=c99 Main.c -o main


clean : 
	rm -f *.o *.out