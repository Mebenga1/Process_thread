#include "process_thread.h"

// Structure des données des threads
struct Thread_Datas{
	int *data; // tableau de la portion du tableau dyu processus par un thread
	int start; // indice de début du tableau du tableau du thread
	int end; // indice de fin du tableau du thread
	int num_portion; // taillle du tableau du thread
	int num; // numero du thread
	int process_id; // id du processus auquel le thread appartient
};

/******************** Initialisation du tableau ***************************************************************************
***************************************************************************************************************************/

int* init_tab(int size,int rand_max, int id)
{
	srand(time(NULL));
                int* tab = malloc(size * sizeof(int)); // allocation dynamique du tableau d'entiers

                for (int j = 0; j < size; j++) {
                    tab[j] = rand() % (rand_max + id); // génération aléatoire et affections des nombres dans le tableau
                }
                
        return tab;
} 


/********************************* Ecriture du tableau dans un fichier ****************************************************
***************************************************************************************************************************/           
  
FILE* tab_file(int* tab,int size,int id )       
{
                char filename[32];
                sprintf(filename, "./file/tab_file_%d.txt", id);

                FILE* file = fopen(filename, "w");

                if (file != NULL) {
                    fprintf(file, " Tableau du Processus [%d]: \n", id);

                    for (int j = 0; j < size; j++) {
                        fprintf(file, "%d ", tab[j]); // Ecriture du Tableau généré dans un fichier
                    }
                    fprintf(file, "\n");
                    fclose(file);
                }
                else {
                    fprintf(stdout, "Impossible d'ouvrir le fichier \n");
                }

	return file;
}



/***************** fonction qui calcule les occurrences ************************************************
********************************************************************************************************/

void* occurences(void* arg) {

    thread datas = (thread)arg;
    
	// initialisation des données du thread

    int start = datas->start;
    int end = datas->end;
    int num = datas->num;
    int t = datas->num_portion;
    int p_id = datas->process_id;
    
    
    
    // Écrire le travail dans un fichier
    char filename[40];
    sprintf(filename, "./file/process(%d)_thread_%d.txt",p_id, num);

    FILE* file = fopen(filename, "a");

    if (file != NULL) {
        fprintf(file, "Processus ID %d, Thread ID: %d \n\n",p_id, num);
        fprintf(file, "Portion du tableau: de l'indice %d à l'indice %d  \n\n", start, end);

	fprintf(file, "Portion du Tableau:  ");
	

        for (int i = 0; i < t; i++) {
            fprintf(file, "%d ", datas->data[i]); // affectation des éléments de la portion du tableau du thread dans un fichier
        }
	fprintf(file, "\n\n");

        fprintf(file, " OCCURENCES : \n");

        for (int i = 0; i < t; i++) {
            if (datas->data[i] != -1) { // vérification si une valeur du tableau a déjà été traitée

                int count = 1;

                for (int j = i + 1; j < t; j++) {
                    if (datas->data[i] == datas->data[j]) { // calcul du nombre d'occurences
                        count++;
                        datas->data[j] = -1;
                    }
                }

                fprintf(file, "Valeur %d: %d occurrence(s) \n", datas->data[i], count);  // écriture des données du thread dans un fichier
            }
        }
    }
    else {
        printf("Impossible d'ouvrir le fichier \n");
        exit(-1);
    }
    fclose(file);

    pthread_exit(NULL);
}



/*********************************** création de threads ************************************************
*********************************************************************************************************/
void create_threads(int nbr_thread, int size, int* tab, int id)
{
	 pthread_t Thread[nbr_thread];

                thread Datas[nbr_thread];
                int portion = size / nbr_thread; /* calcul du nombre d'éléments de la portion du tableau du thread ( taille du tableau du processus sur le le nombre de threads) */

                for (int k = 0; k < nbr_thread; k++) {  // initialisation des données du thread

                    Datas[k] = malloc(sizeof(struct Thread_Datas));
                    Datas[k]->num = k + 1;
                    Datas[k]->num_portion = portion;
                    Datas[k]->process_id = id;
                    Datas[k]->start = k * portion;
                    Datas[k]->end = (k + 1) * portion -1; 
                    Datas[k]->data = malloc(portion * sizeof(int));

                    for (int y = Datas[k]->start; y <= Datas[k]->end; y++) {
                        Datas[k]->data[y - Datas[k]->start] = tab[y];
                    }
                     

                    pthread_create(&Thread[k], NULL, occurences, (void*)Datas[k]);
                }

                // attendre la fin de chaque thread
                for (int k = 0; k < nbr_thread; k++) {
                    pthread_join(Thread[k], NULL);
                    free(Datas[k]->data); // libérer la mémoire allouée pour les données
                    free(Datas[k]); // libérer la mémoire allouée pour la structure
                }
}

