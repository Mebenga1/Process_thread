#include "process_thread.h"

int main(int argc, char* argv[]) {

	clock_t start, end;
    	double cpu_time_used;

    	start = clock(); // Enregistre le temps de début

	 if( argc != 4 )
   	 {
    		fprintf(stderr, "Usage: %s <nombre de processus> <nombre de threads> <taille du tableau>\n", argv[0]);
        	exit(EXIT_FAILURE);
   	 }
    

     int nombre_processus = atoi(argv[1]); // nombres de processus
    
     int nombre_thread = atoi(argv[2]); // nombre de threads
   
    long int taille_tableau = atoi(argv[3]); // taille du tableau
    int* tableau= malloc( taille_tableau * sizeof(long int)); //initialisation du tableau

    for (int i = 1; i <= nombre_processus; i++) {
        pid_t pid = fork();  // creation des n processus

        if (pid < 0) {
            perror("fork fail");
            exit(-1);
        }
        else if (pid == 0) {
            fprintf(stdout, "Processus %d : Pid = %d, PPid= %d\n", i, getpid(), getppid()); // affichages du PID et du PPID du processus créés

            if (i % 2 == 0) {
            
            // Initialisation du tableau et Ecriture du tableau dans un fichier pour les processus paires

		tableau = init_tableau(taille_tableau,Rand_Max,i);
		
		ecrire_tableau_fichier(tableau,taille_tableau,i);

            // creation de threads
            	create_threads(nombre_thread,taille_tableau, tableau,i);
            }

            exit(0);
        }
        else {
            wait(NULL);
        }
    }
    
    free(tableau); // Libérer la mémoire allouée pour le tableau
    
    end = clock(); // Enregistre le temps de fin

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // Calcule le temps écoulé en secondes
    printf("Temps d'execution : %f secondes\n", cpu_time_used);

    return 0;
}
