/*
 * Stats.c
 *
 *              Auteur: Quentin Laborde [qlaborde@polytech.unice.fr]
 *						Clément Sibut [clement.sibut@etu.unice.fr]
 */

#include <stdio.h>
#include <stdlib.h>
#include "Stats.h"

int calculerMoyenne(int tempsExecutions[], int nbTemps)
{
    int min = tempsExecutions[0];
    int max = tempsExecutions[0];
    int indiceMin = 0;
    int indiceMax = 0;
    //On cherche les indices minimums et maximus
    for (int i = 0; i < nbTemps; i++)
    {
        if (tempsExecutions[i] > max)
        {
            max = tempsExecutions[i];
            indiceMax = i;
        }
        else if (tempsExecutions[i] < min)
        {
            min = tempsExecutions[i];
            indiceMin = i;
        }
    }
    //On calcule la somme des 10 temps moins les 2 extremes
    int somme = 0;
    for (int i = 0; i < nbTemps; i++)
    {
        if (i != indiceMin && i != indiceMax)
            somme = somme + tempsExecutions[i];

    }
    //On calcule la moyenne
    int moyenne = somme / (nbTemps - 2);
    return moyenne;
}
