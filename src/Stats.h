/*
 * Stats.h
 *
 *              Auteur: Quentin Laborde [qlaborde@polytech.unice.fr]
 *						Clément Sibut [clement.sibut@etu.unice.fr]
 */
/*
 *Cette fonction calcule le temps moyen d'execution à partir de plusieurs temps passe sous forme de tableau en parametre
 *Les 2 extremes sont retires lors du calcul de la moyenne
 *Le deuxieme parametre contient le nombre de temps contenue dans le tableau
 */
int calculerMoyenne(int tempsExecutions[], int nbTemps);
