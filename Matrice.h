
typedef struct cel{
	int tempConst;
	double temp;

	int bordDroite;
	int bordGauche;
	int bordHaut;
	int bordBas;

} Cel;

typedef struct matrice{
	int taille;
	float **tab;
	Cel **tab2;
} Matrice;


int new_Matrice(int taille, Matrice *matrice);
int temperatureCentre(Matrice *m, double temp);


int display(Matrice *m);
int parcourt(Matrice *m1, Matrice *m2);

