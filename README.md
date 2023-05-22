**Grid**
pour compiler :
\- se placer dans le repertoir *build*
cas 1 cmake est installé et fonctionne:
    \- executer la commande *cmake ..*
    \- executer la commande *make*
cas 2 cmake n'est pas installé ou ne fonctionne pas :
    \- executer les commandes suivantes :
        *g++ -Wall -C ../Class/Grid.cpp -o ./Grid.o*
        *g++ -Wall -C ../Class/PartialSolution.cpp -o ./PartialSolution.o*
        *g++ -Wall -C ../Funcions/Compute.cpp -o ./Compute.o*
        *g++ -Wall -C ../Funcions/InputOutput.cpp -o ./InputOutput.o*
        *g++ -Wall -C ../main.cpp -o ./main.o*
    \- executer la commande
        *g++ ./main.o ./InputOutput.o ./Compute.o ./PartialSolution.o ./Grid.o -o ./Grid.out*

pour executer le programme :
    \- se placer dans le même repertoire que l'executable
    \- executer la commande suivante :
        *Grid.out <fichier>*