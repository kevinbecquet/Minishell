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
    int nb_espaces = 0;
    tabchar = separe(input, &nb_espaces);

    if(!strcmp(tabchar[0],"exit")){
      printf("Shell exited\n");
      free_tab(tabchar,nb_espaces);
      return 0; // quitte le Minishell en cas d'exit
    }
    // execution des commandes (non exit)
    /*if (strcmp(tabchar[nb_espaces],"&")){
      printf("test\n");
      tabchar[nb_espaces] = '\0';
    }*/
    /*printf("%d\n", nb_espaces);
    for(int i = 0; i<=nb_espaces+1;i++){
      printf("%s\n", tabchar[i]);
    }*/
    //execute (tabchar);
    affiche(tabchar);
    //free_tab(tabchar,nb_espaces);//"double free or corruption"
    free(tabchar);//ça, ça exectute bien, mais est-ce-que ça free bien ? ¯\_(ツ)_/¯
  }

  return 0;
}
