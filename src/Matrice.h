/*
 * Matrice.h 
 *
 *              Auteur: Quentin Laborde [qlaborde@polytech.unice.fr]
 *						Clément Sibut []
 *    Date de creation: 2-02-1016 11:00:00 (Quentin)
 * Dernier mise à jour: 4-02-1016 17:35:31 (Quentin)
 */


// Structure qui permet de representation d'une cellule, 
// C'est a dire un "morceau" de plaque avec une temperature uniforme sur sa la surface.
// C'est la combinaison de ces cellules qui permet la représentation de la diffussion de la chaleur sur la plaque.
typedef struct cel{
	//Temperature de la cellule
	float temp;

	// Indicatif qui permet de savoir, si la cellule est dans la zonne externe, qui est sa cellule voisine. 
	//Par exemple, si bordDroite = 1 et que touts les autres sont à 0 alors, la cellule voisine sur la plaque est à gauche de celle-ci.
	int bordDroite;
	int bordGauche;
	int bordHaut;
	int bordBas;

	// Indicatif qui permet de savoir si la cellule est dans une zonne a temperature constante.
	int zonneInterne;
	int zonneExterne;

} Cel;

// Structure qui permet la representation d'une plaque divice en cellules de meme taille avec une zone externe et une interne a temperature constante
// Le transfert de chaleur entre les cellules de la zonne externe et les autre cellule n'est pas possible.
typedef struct matrice{
	// l'indice de la puissace de 2 pour la taille
	int taillePuissance2;

	// nombre de lignes/colonnes de la grille sans la bordure, donc la plaque
	int taillePlaque;

	// nombre de lignes/colonnes de la grille avec les bordure.
	int tailleGrille;

	//Double tableaux qui contient les cellules de la plaque plus la bordure
	Cel **grille;

} Matrice;


int new_Matrice(int taille, Matrice *matrice);

int delimitationZonneInterne(Matrice *m, int puissance2, float temp);

int delimitationZonneExterne(Matrice *m);

int display(Matrice *m);

int parcourt(Matrice *m1, Matrice *m2);

