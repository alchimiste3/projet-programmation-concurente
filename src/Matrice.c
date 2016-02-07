/*
 * Matrice.c 
 *
 *              Auteur: Quentin Laborde [qlaborde@polytech.unice.fr]
 *						Clément Sibut []
 *    Date de creation: 2-02-1016 11:00:00 (Quentin)
 * Dernier mise à jour: 4-02-1016 17:35:19 (Quentin)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "Matrice.h"


float coofNume1 = 4;
float coofNume2 = 16;
float coofDeno = 36;




int new_Matrice(int puissance2, Matrice *matrice){

	// Creation d'une matrice locale pour ne pas travaille avec un pointeur.
	Matrice m = *matrice;

	//taille de la matrice carre
	m.taillePuissance2 = puissance2;
	m.taillePlaque = 2<<puissance2;
	m.tailleGrille = m.taillePlaque + 2;



	//allocation mémoire de la matrice
	m.grille = (Cel**) malloc((m.tailleGrille)*sizeof(Cel*));


	//allocation mémoire de chaque ligne
	for(int i = 0; i< m.tailleGrille; i++){
		m.grille[i] = (Cel*) malloc(m.tailleGrille*sizeof(Cel));
	}


	//initialisation de la temperature de chaque cellule
	for(int i = 0; i < m.tailleGrille; i++){
		for(int y = 0; y < m.tailleGrille ; y++){
			m.grille[i][y].temp = 0;

		}
	}

	//Modification de la matrice mit en parametre
	*matrice = m;

	return 0;
}

// On delimite la zonne interne où les cellule ont une température constante TEMPS_CHAUD.
// On indique leur position avec la variable zonneInterne
int delimitationZonneInterne(Matrice *m, int puissance2, float temp){

	// Calcule des indice min et max qui delimite la zonne interne
	int indiceMin = (1<<(puissance2-1)) - (1<<(puissance2-4)) + 1;
	int indiceMax = (1<<(puissance2-1)) + (1<<(puissance2-4)) + 1;


	// printf("%d\n", indiceMin);
	// printf("%d\n", indiceMax);

	// Initialisation de la temperature et indiquatif de zonne interne mit à 1.
	for(int i = indiceMin; i < indiceMax; i++){
		for(int y = indiceMin; y < indiceMax; y++){
			m->grille[i][y].temp = temp;
			m->grille[i][y].zonneInterne = 1;
		}
	}

	return 0;

}

// On delimite la zonne externe où les cellule ont une température constante TEMPS_FROID.
// On indique leur position avec la variable zonneExterne
int delimitationZonneExterne(Matrice *m){

	for(int i = 0; i < m->tailleGrille; i++){
		for(int y = 0; y < m->tailleGrille; y++){

			// Si la cellule est en bas de la plaque
			if(i == m->tailleGrille - 1){
 				m->grille[i][y].zonneExterne = 1;
 				m->grille[i][y].bordBas = 1;
			} 
			// Si la cellule est en haut de la plaque
			else if(i == 0){
 				m->grille[i][y].zonneExterne = 1;
 				m->grille[i][y].bordHaut = 1;
			}

			// Si la cellule est en droite de la plaque
			if(y == m->tailleGrille - 1){
 				m->grille[i][y].zonneExterne = 1;
 				m->grille[i][y].bordDroite = 1;
			}

			// Si la cellule est en gauche de la plaque
			else if(y == 0){
 				m->grille[i][y].zonneExterne = 1;				
 				m->grille[i][y].bordGauche = 1;
			}

		}
	}

	return 0;

}


//Permet de calculer la temperature d'une cellule à un temps donne t avec les temperature à t - 1.
int calculeTempCel(Matrice *matrice1, Matrice *matrice2, int i, int y){

	// la matrice en t0
	Cel ** m = matrice1->grille;

	// la cellure à modifier pour qu'elle soit en t1
	Cel * c = &(matrice2->grille[i][y]);


	// Si la cellule ce trouve au centre de la grille (en zonne interne).
	// La température reste constante
	if(m[i][y].zonneInterne){
		c->temp = m[i][y].temp;
		return 0;
	}

	// Si la cellule ce trouve en bourdure de la grille (en zonne externe) 
	// On calcule ca température pour qu'elle soit égale a la cellule voisine 
	// qui est sur la plaque afin d'obtenir un échange de chaleur nulle avec la zonne externe.
	if(m[i][y].zonneExterne){

		// Si la cellule est sur l'un des angle de la grille
		if(m[i][y].bordHaut && m[i][y].bordGauche){
			i++;
			y++;
		}
		else if(m[i][y].bordHaut && m[i][y].bordDroite){
			i++;
			y--;
		}
		else if(m[i][y].bordBas && m[i][y].bordGauche){
			i--;
			y++;
		}
		else if(m[i][y].bordBas && m[i][y].bordDroite){
			i--;
			y--;
		}

		// Si la cellule est sur l'un des bord de la grille
		else if(m[i][y].bordHaut){
			i++;
		}
		else if(m[i][y].bordDroite){
			y--;
		}
		else if(m[i][y].bordGauche){
			y++;
		}
		else if(m[i][y].bordBas){
			i--;
		}
	}

	// On calcule la temperature de la cellule pour un temps t donne avec les temperatures des 8 cellule voisine plus la sienne au temps t - 1. 
	// On utilise pour l'instant des cooficients constants pour la diffusion.  
	c->temp = ((m[i-1][y].temp + m[i+1][y].temp + m[i][y-1].temp + m[i][y+1].temp)*coofNume1 + m[i][y].temp*coofNume2 + m[i-1][y-1].temp + m[i+1][y-1].temp + m[i+1][y+1].temp + m[i-1][y+1].temp )/coofDeno;


	return 0;

}

int parcourt(Matrice *matrice1, Matrice *matrice2){

	// On recupere la taille de la grille pour la parcourire.
	int tailleGrille = matrice1->tailleGrille;

	// Calcule pour chaque cellule de sa nouvelle temperature a t+1
	for(int i = 0; i < tailleGrille ; i++){
		for(int y = 0; y < tailleGrille ; y++){
			calculeTempCel(matrice1, matrice2 , i, y);
		}
	}

	return 0;
}



// Permet d'afficher le quart haut-gauche de la plaque.  
int display(Matrice *m){

	// On calcule le "pseudo" centre de la plaque
	int indiceMinZonneInterne = (1<<(m->taillePuissance2-1)) - (1<<(m->taillePuissance2-4));
	int indiceMaxZonneInterne = (1<<(m->taillePuissance2-1)) + (1<<(m->taillePuissance2-4));
	int indicePsedoCentre = (indiceMaxZonneInterne + indiceMinZonneInterne)/2;

	printf("\nAffiche plaque : \n");

	for(int i = 1; i <= indicePsedoCentre; i++){
		printf("\n");
		for(int y = 1; y <= indicePsedoCentre; y++){
			printf("%f - ", (float)(m->grille[i][y]).temp); 
		}
	}


	return 0;
}
