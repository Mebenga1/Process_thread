#include "process_thread.h"

int main(int argc, char* argv[]) {

	 if( argc != 3)
   	 {
    		fprintf(stderr, "Usage: %s <nombre de processus> <nombre de threads>\n", argv[0]);
        	exit(EXIT_FAILURE);
   	 }
    

    int n = atoi(argv[1]); // nombres de processus
    
    int num_thread = atoi(argv[2]); // nombre de threads
   
    int* tab= malloc(max_size * sizeof(int)); //initialisation du tableau

    for (int i = 1; i <= n; i++) {
        pid_t process = fork();  // creation des n processus

        if (process < 0) {
            perror("fork fail");
            exit(-1);
        }
        else if (process == 0) {
            fprintf(stdout, "Processus %d : Pid = %d, PPid= %d\n", i, getpid(), getppid()); // affichages du PID et DU PPID du processus créés

            if (i % 2 == 0) {
            
            // Initialisation du tableau et Ecriture du tableau dans un fichier pour les processus paires

		tab = init_tab(max_size,Rand_Max,i);
		
		tab_file(tab,max_size,i);

            // création des threads
            	create_threads(num_thread, max_size, tab,i);    
            }

            exit(0);
        }
        else {
            wait(NULL);
        }
    }

    return 0;
}
