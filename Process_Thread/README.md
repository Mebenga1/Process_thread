# Process_thread
Ce programme en C crée n processus, chacun affichant son PID et PPID, et pour les processus pairs, initialise un grand tableau, crée p threads pour compter les occurrences de chaque valeur du tableau, écrit le tableau dans un fichier, et enregistre le travail de chaque thread dans un fichier distinct.

topic

1. Ecrivez un programme C qui prend en entrée un entier n et crée n processus.
2. Chaque processus a un numéro (de 1 à n).
3. Tous les processus doivent afficher leur identité (PID) et l'identité de leur parent (PPID).
4. En plus de l'exigence précédente, les processus pairs doivent initialiser un tableau de grande taille et créer p threads, chacun comptant le nombre d'occurrences de chaque valeur du tableau.
5. Le tableau généré doit être écrit dans un fichier.
6. Le travail de chaque thread doit être enregistré dans un fichier distinct spécifiant la portion du fichier sur laquelle le thread travaillait.
