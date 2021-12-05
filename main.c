#include "exe.h"


int main(int argc, char *argv[]) {

  while(1){
    // indique que le Minishellest prêt à recevoir une nouvelle commande
    printf("$ ");

    //Acquisition de la commande
    char input[TAILLE_MAX];
    char** tabchar = NULL;
    get_input(input,TAILLE_MAX);

    // Découpage de la commande en tableau
    tabchar = separe(input);


    // Traitement des commandes builtin pwd et cd et de la fermeture du Minishell
    if(!strcmp(tabchar[0],"pwd")){
      char path[TAILLE_MAX];

      if(getcwd(path,TAILLE_MAX) == NULL) //Si error lors de l'acquisition du path
        perror("pwd Error"); // On indique l'erreur

      else printf("%s\n", path); // sinon on affiche le path
    }

    else if(!strcmp(tabchar[0],"cd")){
      //  execution de cd + affichage de l'erreur en cas de problème
      if(chdir(tabchar[1]))
        perror("cd Error");
    }

    else if(!strcmp(tabchar[0],"exit"))
      return 0; // quitte le Minishell en cas d'exit

    // execution des commandes non builtin
    else execute (tabchar);

  }

  return 0;
}
