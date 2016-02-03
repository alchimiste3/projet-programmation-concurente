#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "Matrice.h"


double coofVHNume = 4;
double coofDeno = 36;



int positionnement(Cel * c, int i, int y, int taille){
	if(i == 0) c->bordHaut = 1;
	if(i == taille-1) c->bordBas = 1;
	if(y == 0) c->bordGauche = 1;
	if(y == taille-1) c->bordDroite = 1;

}


int new_Matrice(int taille, Matrice *matrice){

	Matrice m = *matrice;

	//taille de la matrice carre
	m.taille = taille;



	//allocation mémoire de la matrice

	m.tab2 = (Cel**) malloc(taille*sizeof(Cel));

	//allocation mémoire de chaque ligne
	for(int i = 0; i< taille; i++){

		m.tab2[i] = (Cel*) malloc(taille*sizeof(Cel));
	}

		//allocation mémoire de chaque ligne
	for(int i = 0; i< taille; i++){
		for(int y = 0; y < taille ; y++){
			//printf("i = %d et y = %d\n",i,y );

			m.tab2[i][y].temp = 0;
			m.tab2[i][y].tempConst = 0;

			//printf("temp = %d\n\n",m.tab2[i][y].temp);

			positionnement(&(m.tab2[i][y]), i, y , taille);

		}



	}



	*matrice = m;


	// printf("tempssff = %d \n",m.tab2[0][0].temp);

	// printf("tempAAA = %d \n",matrice->tab2[0][0].temp);

	return 0;
}

int temperatureCentre(Matrice *m, double temp){
	int taille = m->taille;

	m->tab2[taille/2][taille/2].temp = temp;
	// m->tab2[taille/2+1][taille/2].temp  = temp;
	// m->tab2[taille/2][taille/2+1].temp  = temp;
	// m->tab2[taille/2+1][taille/2+1].temp  = temp;

	m->tab2[taille/2][taille/2].tempConst = 1;
	// m->tab2[taille/2+1][taille/2].tempConst  = 1;
	// m->tab2[taille/2][taille/2+1].tempConst  = 1;
	// m->tab2[taille/2+1][taille/2+1].tempConst  = 1;

}

int calculeTempCel(Matrice *matrice1, Matrice *matrice2, int i, int y){

	Cel ** m = matrice1->tab2;

	Cel * c = &(matrice2->tab2[i][y]);

	if((matrice1->tab2[i][y]).tempConst){

		c->temp = (matrice1->tab2[i][y]).temp;
	}


/////////// Si la Cel est sur l'un des "coins" de la grille. //////////////////

	else if(c->bordHaut && c->bordDroite){
		c->temp = ((m[i+1][y].temp + m[i][y-1].temp)*coofVHNume + m[i+1][y-1].temp)/coofDeno;
	}
	else if(c->bordHaut && c->bordGauche){
		c->temp =  ((m[i+1][y].temp + m[i][y+1].temp)*coofVHNume + m[i+1][y+1].temp)/coofDeno;

	}
	else if(c->bordBas && c->bordDroite){
		c->temp =  ((m[i-1][y].temp + m[i][y-1].temp)*coofVHNume + m[i-1][y-1].temp)/coofDeno;


	}
	else if(c->bordBas && c->bordGauche){
		c->temp = ((m[i-1][y].temp + m[i][y+1].temp)*coofVHNume + m[i-1][y+1].temp)/coofDeno;
	}

/////////// Si la Cel est sur l'un des "bords" de la grille. //////////////////

	else if(c->bordHaut){
		c->temp = ((m[i+1][y].temp + m[i][y-1].temp + m[i][y+1].temp)*coofVHNume + m[i+1][y-1].temp + m[i+1][y+1].temp)/coofDeno;
	}

	else if(c->bordBas){
		c->temp = ((m[i-1][y].temp + m[i][y-1].temp + m[i][y+1].temp)*coofVHNume + m[i-1][y-1].temp + m[i-1][y+1].temp)/coofDeno;
	}

	else if(c->bordDroite){
		c->temp = ((m[i-1][y].temp + m[i+1][y].temp + m[i][y+1].temp)*coofVHNume + m[i+1][y+1].temp + m[i-1][y+1].temp)/coofDeno;
	}

	else if(c->bordGauche){
		c->temp = ((m[i-1][y].temp + m[i+1][y].temp + m[i][y-1].temp)*coofVHNume + m[i-1][y-1].temp + m[i+1][y-1].temp)/coofDeno;
	}

////////// Cas general /////////////

	else{
		c->temp = ((m[i-1][y].temp + m[i+1][y].temp + m[i][y-1].temp + m[i][y+1].temp)*coofVHNume + m[i-1][y-1].temp + m[i+1][y-1].temp + m[i+1][y+1].temp + m[i-1][y+1].temp)/coofDeno;
	}


	c->tempConst = (matrice1->tab2[i][y]).tempConst;



	return 0;

}

int parcourt(Matrice *matrice1, Matrice *matrice2){



	Matrice m1 = *matrice1;
	Matrice m2 = *matrice2;


	int taille = matrice1->taille;



	for(int i = 0; i < taille ; i++){
		for(int y = 0; y < taille ; y++){
			//printf("i = %d et y = %d\n",i,y );

			calculeTempCel(&m1, &m2 , i, y);
		}
	}

	matrice1->tab2 = m1.tab2;
	matrice2->tab2 = m2.tab2;

	return 0;
}




int display(Matrice *m){

	printf("\n\n\nAffiche matrice : \n\n");

	int taille = m->taille;

	for(int i = 0; i < taille ; i++){
		printf("\n");
		for(int y = 0; y < taille ; y++){
			printf("%f - ", (double)(m->tab2[i][y]).temp); 
		}
	}


	return 0;
}
