/*
 * Main.c
 *
 *              Auteur: Quentin Laborde [qlaborde@polytech.unice.fr]
 *						Clément Sibut [clement.sibut@etu.unice.fr]
 *    Date de creation: 2-02-1016 11:00:00 (Quentin)
 * Dernier mise à jour: 4-02-1016 17:35:19 (Quentin)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "Matrice.h"
#include "Stats.h"

int indices_N[20];
int tailleIndices = 0;
int nbIteration = 10000;
bool affichageTemperature = false;
bool affichageTemps = false;
unsigned int etapes = 0;
int threads[20];
int tailleThreads = 0;

enum Etapes {
    ITERATIF = 1,
    THREAD_BAR = 2,
    THREAD_BAR_COND = 4,
    THREAD_BAR_SEMAPHORE = 8,
    OPENCL_CPU = 16,
    OPENCL_GPU = 32
};


/// git commit -ma "sddcfzeefzeer"


// Methode principale qui récupère les option de l'utilisateur et lance les différents scanarios demande.
void main(int argc, char *argv[]){
    //Lecture des options
    if (argc > 1) {
        for (int i = 1; argv[i]; i++)
        {
            char *mot = argv[i];
            if (mot[0] == '-')
            {
                if (mot[1] == 's')
                {
                    // On lit la taille des données voulues
                    i++;
                    if (i <= argc && argv[i])
                    {
                        char c;
                        while((c = *argv[i]) != '\0')
                        {
                            if (c >= '0' && c <= '9')
                            {
                                indices_N[tailleIndices] = c - '0';
                                tailleIndices++;
                            }
                            argv[i]++;
                        }
                    }
                }
                else if (mot[1] == 'm')
                {
                    //Si l'option -m est présente on affiche le temps d'execution et la trace n'apparait plus
                    affichageTemps = true;
                }
                else if (mot[1] == 'a')
                {
                    //Si l'option -a est présente on affiche les températures initiales et finales
                    affichageTemperature = true;
                }
                else if (mot[1] == 'i')
                {
                    //On lit le nombre d'itérations
                    i++;
                    if (i <= argc && argv[i])
                    {
                        int nb = atoi(argv[i]);
                        if (nb == 0)
                            printf("Le nombre d'itérations n'est pas valide\n");
                        else
                            nbIteration = nb;
                    }
                }
                else if (mot[1] == 'e')
                {
                    /*Les étapes du programme à exécuter sont stockés dans la variable étapes
                     * qui est une combinaison de plusieurs flags stockés
                    Plusieurs choix peuvent donc être renseignés pour cette option*/
                    i++;
                    if (i <= argc && argv[i])
                    {
                        char c;
                        while((c = *argv[i]) != '\0')
                        {
                            switch(c) {
                            case '0':
                                etapes |= ITERATIF; break;
                            case '1':
                                etapes |= THREAD_BAR; break;
                            case '2':
                                etapes |= THREAD_BAR_COND; break;
                            case '3':
                                etapes |= THREAD_BAR_SEMAPHORE; break;
                            case '4':
                                etapes |= OPENCL_CPU; break;
                            case '5':
                                etapes |= OPENCL_GPU; break;
                            default:
                                printf("Etape inconnue : %c\n", c);
                            }
                            argv[i]++;
                        }
                    }
                }
                else if (mot[1] == 't')
                {
                    /*On lit le nombre de thread voulu (4**t)
                On boucle afin de récupérer les différentes valeurs
                car le programme va tester différents nombres de threads*/
                    i++;
                    if (i <= argc && argv[i])
                    {
                        char c;
                        while((c = *argv[i]) != '\0')
                        {
                            if (c >= '0' && c <= '5')
                            {
                                threads[tailleThreads] = c - '0';
                                tailleThreads++;
                            }
                            else
                            {
                                printf("Nombre de threads invalide, saisi %d alors qu'il doit etre compris entre 0 et 5\n", c - '0');
                            }
                            argv[i]++;
                        }
                    }
                }
                else break;

            }
        }
    }


    // On définit des valeurs par défaut pour les tableaux
    // 2**(4+4) = 256 plaque de taille 256*256
    if (tailleIndices < 1)
    {
        indices_N[0] = 4;
        tailleIndices = 1;
    }

    // 4**t donc 4**1 = 4 threads
    if (tailleThreads < 1)
    {
        threads[0] = 1;
        tailleThreads = 1;
    }

    // Creation deux deus matrice pour représenter la plaque sur deux temps différents.
    Matrice matrice1;
    Matrice matrice2;
    new_Matrice(indices_N[0], &matrice1);
    new_Matrice(indices_N[0], &matrice2);

    int tempsExecutions[10];
    int nbExecutions = 1;
    if (affichageTemps)
        nbExecutions = 10;

    for (int i = 0; i < nbExecutions; i++)
    {
        // Initialisation zonne Interne et Externe de la plaque
        delimitationZonneInterne(&matrice1, indices_N[0] , 36);
        delimitationZonneExterne(&matrice1);
        delimitationZonneInterne(&matrice2, indices_N[0] , 36);
        delimitationZonneExterne(&matrice2);

        //Affichage de la plaque à t = 1
        if (affichageTemperature)
            printf("\nTempérature initiale de la plaque :\n");
            display(&matrice1);

        //Temps initial avant l'execution de l'algo
        clock_t temps_initial, temps_final, temps_cpu;
        temps_initial = clock ();
        int a = 0;

        //Boucle d'intération pour simuler la diffusion de la chaleur sur plusieur itérations
        while(a < nbIteration){
            a++;
            parcourt(&matrice1,&matrice2);
            matrice1 = matrice2;

        }
        //Temps final apres execution de l'algo puis stockage dans un tableau
        temps_final = clock ();
        temps_cpu = temps_final - temps_initial;
        tempsExecutions[i] = temps_cpu;

        //Affichage de la plaque à t = nbIteration
        if (affichageTemperature)
            printf("\nTempérature final de la plaque :\n");
            display(&matrice2);
    }
    //Si l'option -m est présente on affiche le temps d'execution en moyenne
    if (affichageTemps)
    {
        int moyenne = calculerMoyenne(tempsExecutions, 10);
        printf("\nTemps d'execution en moyenne: %d ms\n", moyenne);

    }

}
