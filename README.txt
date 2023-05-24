Grid
=====
pour compiler :
---------------
si cmake est installé et fonctionne:
    1. se placer dans le répertoire *build*
    2. exécuter la commande
        cmake ..
    3. exécuter la commande
        make
si cmake n'est pas installé ou ne fonctionne pas :
    1. se placer dans le répertoire *build*
    2. exécuter les commandes suivantes :
        g++ -Wall -C ../Class/Grid.cpp -o ./Grid.o
        g++ -Wall -C ../Class/PartialSolution.cpp -o ./PartialSolution.o
        g++ -Wall -C ../Funcions/Compute.cpp -o ./Compute.o
        g++ -Wall -C ../Funcions/InputOutput.cpp -o ./InputOutput.o
        g++ -Wall -C ../main.cpp -o ./main.o
    3. exécuter la commande
        g++ ./main.o ./InputOutput.o ./Compute.o ./PartialSolution.o ./Grid.o -o ./Grid.out

pour exécuter le programme :
----------------------------
1. se placer dans le même répertoire que l'exécutable
2. exécuter la commande suivante :
    Grid.out <fichier>
    où <fichier> est le chemin vers le fichier texte contenant la grille à résoudre
3. arguments suplémentaires :
    -t <temps> pour donner une limite de temps en secondes (par défaut 60s)
    -s <seed> pour indiquer une seed (0 pour une seed aléatoire)
    -o <fichier> pour indiquer un fichier dans lequel écrire la solution trouvée
