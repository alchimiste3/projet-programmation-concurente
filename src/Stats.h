/*
 * Stats.h
 *
 *              Auteur: Quentin Laborde [qlaborde@polytech.unice.fr]
 *						Clement Sibut [clement.sibut@etu.unice.fr]
 *    Date de creation: 19-02-1016 11:00:00 (Clement)
 * Dernier mise a jour: 19-02-1016 17:35:31 (Clement)
 */
/*

 *Cette fonction calcule le temps moyen d'execution a partir de plusieurs temps passe sous forme de tableau en parametre
 *Les 2 extremes sont retires lors du calcul de la moyenne
 *Le deuxieme parametre contient le nombre de temps contenue dans le tableau
 */
int calculerMoyenne(int tempsExecutions[], int nbTemps);
