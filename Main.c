#include <stdio.h>
#include <stdlib.h>

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

	//int taille = 2<<indice_N;

	int taille = 10;

	// float matriceT0[taille][taille];

	// float matriceT1[taille][taille];

	// // parcourt()

	// matriceT1[0][0] = 1.1;

	Matrice matrice1;
	Matrice matrice2;

	new_Matrice(taille, &matrice1);
	new_Matrice(taille, &matrice2);

	//m1.tab[0][0] = 3.3;


	printf("coucou\n");

	temperatureCentre(&matrice1, 36);


	printf("%f\n",(float) matrice1.taille);

	printf("%f\n",(float) matrice1.tab2[0][0].temp);

	display(&matrice1);

	// matrice1.tab2[-2][0].temp = 222;

	// printf("\n\n");

	// display(&matrice1);



	int a = 0;
	while(a < 10000){
		a++;

		parcourt(&matrice1,&matrice2);

		display(&matrice2);

		matrice1 = matrice2;

	}


}