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



	int puissance2 = 4;


	Matrice matrice1;
	Matrice matrice2;

	new_Matrice(puissance2, &matrice1);

	new_Matrice(puissance2, &matrice2);

	delimitationZonneInterne(&matrice1, puissance2 , 36);
	delimitationZonneExterne(&matrice1);


	display(&matrice1);





	int a = 0;
	while(a < 1000000){
		a++;

		parcourt(&matrice1,&matrice2);


		matrice1 = matrice2;

	}

	display(&matrice2);

}