#ifndef PROCESS_THREAD_H
#define PROCESS_THREAD_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <pthread.h>
#include <stdio.h>


#define Rand_Max 10 // plage de nombres générés


struct Thread_Datas; // Structure des données des threads

typedef struct Thread_Datas *thread;

int* init_tableau(long int size_array,int rand_max, int process_id); // Initialisation du tableau 

FILE* ecrire_tableau_fichier(int* array,long int size_array,int process_id ); //Ecriture du tableau dans un fichier

void create_threads(int nombre_thread, int taille_tableau, int* tableau, int process_id); //création de threads

void* occurences(void* arg); // Fonction pour compter les occurrences

#endif
