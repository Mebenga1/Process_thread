#include "process_thread.h"

// Structure des données des threads
struct Thread_Datas{
	int *data; // tableau de la portion du tableau dyu processus par un thread
	int start; // indice de début du tableau du tableau du thread
	int end; // indice de fin du tableau du thread
	int taille_portion; // taillle du tableau du thread
	int numero_thread; // numero du thread
	int process_id; // id du processus auquel le thread appartient
};

/******************** Initialisation du tableau ***************************************************************************
***************************************************************************************************************************/

int* init_tableau(long int size_array,int rand_max, int process_id)
{
	srand(time(NULL));
               int* tableau = malloc(size_array * sizeof( long int)); // allocation dynamique du tableau d'entiers

                for (int j = 0; j < size_array; j++) {
                    tableau[j] = rand() % (rand_max + process_id); // génération aléatoire et affections des nombres dans le tableau
                }
                
        return tableau;
} 


/********************************* Ecriture du tableau dans un fichier ****************************************************
***************************************************************************************************************************/           
  
FILE* ecrire_tableau_fichier(int* array,long int size_array,int process_id )     
{
                char* filename = malloc(32*sizeof(char));
                sprintf(filename, "./file/tab_file_%d.txt", process_id);

                FILE* fichier = fopen(filename, "w");

                if (fichier != NULL) {
                    fprintf(fichier, " Tableau du Processus [%d]: \n", process_id);

                    for (int j = 0; j < size_array; j++) {
                        fprintf(fichier, "%d ", array[j]); // Ecriture du Tableau généré dans un fichier
                    }
                    fprintf(fichier, "\n");
                    fclose(fichier);
                    free(filename);
                }
                else {
                    fprintf(stdout, "Impossible d'ouvrir le fichier \n");
                }

	return fichier;
}



/***************** fonction qui calcule les occurrences ************************************************
********************************************************************************************************/

void* occurences(void* arg) {

    thread thread_datas = (thread)arg;
    
	// initialisation des données du thread

    int start = thread_datas->start;
    int end = thread_datas->end;
    int numero_thread = thread_datas->numero_thread;
    int taille_portion = thread_datas->taille_portion;
    int process_id = thread_datas->process_id;
    
    // Écrire le travail dans un fichier
    char* file_thread_name= malloc( 32 * sizeof(char));
    sprintf(file_thread_name, "./file/process(%d)_thread_%d.txt",process_id, numero_thread);

    FILE* file_thread = fopen(file_thread_name, "a");

    if (file_thread != NULL) {
        fprintf(file_thread, "Processus ID %d, Thread ID: %d \n\n",process_id, numero_thread);
        fprintf(file_thread, "Portion du tableau: de l'indice %d à l'indice %d  \n\n", start, end);

	fprintf(file_thread, "Portion du Tableau:  ");
	

        for (int i = 0; i < taille_portion; i++) {
            fprintf(file_thread, "%d ", thread_datas->data[i]); // affectation des éléments de la portion du tableau du thread dans un fichier
        }
	fprintf(file_thread, "\n\n");

        fprintf(file_thread, " OCCURENCES : \n");

        for (int i = 0; i < taille_portion; i++) {
            if (thread_datas->data[i] != -1) { // vérification si une valeur du tableau a déjà été traitée

                int count = 1;

                for (int j = i + 1; j < taille_portion; j++) {
                    if (thread_datas->data[i] == thread_datas->data[j]) { // calcul du nombre d'occurences
                        count++;
                        thread_datas->data[j] = -1;
                    }
                }

                fprintf(file_thread, "Valeur %d: %d occurrence(s) \n", thread_datas->data[i], count);  // écriture des données du thread dans un fichier
            }
        }
    }
    else {
        printf("Impossible d'ouvrir le fichier \n");
        exit(-1);
    }
    fclose(file_thread);
    free(file_thread_name);
    pthread_exit(NULL);
}


/*********************************** création de threads ************************************************
*********************************************************************************************************/
void create_threads(int nombre_thread, int taille_tableau, int* tableau, int process_id)
{
            	pthread_t Thread[nombre_thread];
		
                thread *thread_Datas= malloc(nombre_thread * sizeof(struct Thread_Datas)) ;
                int portion = taille_tableau / nombre_thread; /* calcul du nombre d'éléments de la portion du tableau du thread ( taille du tableau du processus sur le le nombre de threads) */

                for (int k = 0; k < nombre_thread; k++) {  // initialisation des données du thread

                    thread_Datas[k] = malloc(sizeof(struct Thread_Datas));
                    thread_Datas[k]->numero_thread = k + 1;
                    thread_Datas[k]->start = k * portion;
                    thread_Datas[k]->end = (k + 1) * portion -1; 
                    thread_Datas[k]->taille_portion = portion;
                    thread_Datas[k]->process_id = process_id;
                    thread_Datas[k]->data = malloc(portion * sizeof(int));

                    for (int y = thread_Datas[k]->start; y <= thread_Datas[k]->end; y++) {
                        thread_Datas[k]->data[y - thread_Datas[k]->start] = tableau[y];
                    }
                     

                    pthread_create(&Thread[k], NULL, occurences, (void*)thread_Datas[k]);
                }

                // attendre la fin de chaque thread
                for (int k = 0; k < nombre_thread; k++) {
                    pthread_join(Thread[k], NULL);
                    free(thread_Datas[k]->data); // libérer la mémoire allouée pour les données
                    free(thread_Datas[k]); // libérer la mémoire allouée pour la structure
                } 
}
