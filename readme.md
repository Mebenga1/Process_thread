 DESCRIPTION:
 	Ce programme en C crée n processus, chacun affichant son PID et PPID, et pour les processus pairs, initialise un grand tableau, crée p threads pour compter les occurrences de chaque valeur du tableau, écrit le tableau dans un fichier, et enregistre le travail de chaque thread dans un fichier distinct.
 	
 
 PRÉREQUIS:
 	- OS: Linux ( UBUNTU 20.04 chez moi ) 
 	- Compilateur : gcc
 	- Bibliothèque : -lpthread
 	- Utilitaire de build : make
 	
 	
 EXÉCUTION:
	1- Se positionner dans le repertoire du programe : cd /path/Process_Thread
	2- Executer la commande : make
	3- Exécuter le le fichier executable : ./process_thread << nombre de processus >> << nombre de thread >>
	
	 Exemple : ./process_thread 5 10 ( 5 est le nombre de processus à créer et 10 est le nombre de thread créé dans chaque pocessus)
	
	4- la commade : make clean permet de supprimer tous les fichier .txt, objet, executable du projet
	
	
ARBORESCENCE DU REPERTOIRE Process_Thread:
	- src : c'est le reportoire qui contient tous les fichiers sources et fichier entête (.c et .h)
	- build: c'est le repertoire qui contient tous les fichiers objets (.o)
	- file: c'est le repertoire qui contient tous les fichiers texte (.txt)
	- makefile
	- fichier exécutable
	
FICHIERS TXT:
	- tab_file_2.txt ( fichier qui contient le tableau du processus 2)
	- process(2)_thread_1.txt ( fichier qui contient les données du thread 1 du processus 2)
	
