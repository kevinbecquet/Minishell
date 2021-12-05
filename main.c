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

    if(!strcmp(tabchar[0],"exit")){
      free_tab(tabchar);
      return 0; // quitte le Minishell en cas d'exit
    }
    // execution des commandes (non exit)
    execute (tabchar);
    free_tab(tabchar);
  }

  return 0;
}
