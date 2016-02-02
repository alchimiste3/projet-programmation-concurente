#include <stdio.h>
#include "Matrice.h"

int indice_N = 4;
int nbInteration = 10000;


/// git commit -m -a "sddcfzeefzeer"



// int parcourt(float ** m1, float ** m2, size_t taille){
// 	for(int i = 0; i < taille ; i++){
// 		for(int y = 0; y < taille ; y++){
// 			m2[i][y]
// 		}
// 	}
// }

void main(void){

	int taille = 2<<indice_N;

	float matriceT0[taille][taille];

	float matriceT1[taille][taille];

	// parcourt()

	matriceT1[0][0] = 1.1;


	printf("coucou\n");

	printf("%d\n", test());

}
