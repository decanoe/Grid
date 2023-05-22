Grid
=====
pour compiler :
---------------
### si cmake est installé et fonctionne:
1. se placer dans le répertoire *build*
2. exécuter la commande
    <br>*cmake ..*
3. exécuter la commande
    <br>*make*
### si cmake n'est pas installé ou ne fonctionne pas :
1. se placer dans le répertoire *build*
2. exécuter les commandes suivantes :
        <br>*g++ -Wall -C ../Class/Grid.cpp -o ./Grid.o*
        <br>*g++ -Wall -C ../Class/PartialSolution.cpp -o ./PartialSolution.o*
        <br>*g++ -Wall -C ../Funcions/Compute.cpp -o ./Compute.o*
        <br>*g++ -Wall -C ../Funcions/InputOutput.cpp -o ./InputOutput.o*
        <br>*g++ -Wall -C ../main.cpp -o ./main.o*
3. exécuter la commande
        <br>*g++ ./main.o ./InputOutput.o ./Compute.o ./PartialSolution.o ./Grid.o -o ./Grid.out*

pour exécuter le programme :
----------------------------
1. se placer dans le même répertoire que l'exécutable
2. exécuter la commande suivante :
    <br>*Grid.out <fichier\>*
    <br>où <fichier\> est le chemin vers le fichier texte contenant la grille à résoudre
3. arguments suplémentaires :
    - \-t <temps\> *pour donner une limite de temps en secondes (par défaut 60s)*
    - \-s <seed\> *pour indiquer une seed (0 pour une seed aléatoire)*
    - \-o <fichier\> *pour indiquer un fichier dans lequel écrire la solution trouvée*
