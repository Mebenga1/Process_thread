#ifndef PROCESS_THREAD_H
#define PROCESS_THREAD_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <pthread.h>
#include <stdio.h>

#define max_size 10000 // taille du tableau
#define Rand_Max 10 // plage de nombres générés


struct Thread_Datas; // Structure des données des threads

typedef struct Thread_Datas *thread;

int* init_tab(int size,int rand_max, int id); // Initialisation du tableau 

FILE* tab_file(int* tab,int size,int id ); //Ecriture du tableau dans un fichier

void* occurences(void* arg); // Fonction pour compter les occurrences

void create_threads(int nbr_thread, int size, int* tab, int id); // Création des threads

#endif
