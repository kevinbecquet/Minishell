#include "exe.h"
#define NB_MAX_PIPES 10

int main(int argc, char *argv[]){

  while(1){
    // indique que le Minishell est prêt à recevoir une nouvelle commande
    printf("$ ");

    int arr_plan = 0;

    //Acquisition de la commande
    char input[TAILLE_MAX];
    char*** tabchar = NULL;
    char** tabchar_pipe = NULL;
    int nb_espaces[NB_MAX_PIPES];
    get_input(input,TAILLE_MAX);
    char espace = ' ';
    char pipe = '|';

    // Découpage de la commande en tableau
    int nb_pipes = 0;
    tabchar_pipe = separe(input, &nb_pipes, pipe);
    tabchar = (char***)malloc((nb_pipes+1)*sizeof(char**));//malloc pour créer un tableau de tableau chaines de caractères
    for(int i = 0; i<=nb_pipes; i++){
      nb_espaces[i] = 0;
      tabchar[i] = separe(tabchar_pipe[i], &nb_espaces[i], espace);
    }

    if(!strcmp(*tabchar[0],"exit")){
      printf("Shell exited\n");
      //free_tab(tabchar,nb_espaces);
      return 0; // quitte le Minishell en cas d'exit
    }
    // execution des commandes (non exit)
    /*
    printf("test0\n");
    for(int i = 0; i<nb_pipes; i++){
      printf("test1\n");
      if(!strcmp(tabchar[i][nb_espaces[i]],"&")){
        printf("test2\n");
        *tabchar[i][nb_espaces[i]] = '\0';
        arr_plan = 1;
      }
      printf("test3\n");
    }
*/
  execute (tabchar[i],0,nb_pipes);


    //free_tab(tabchar,nb_espaces);//"double free or corruption"
    free(tabchar);//ça, ça exectute bien, mais est-ce-que ça free bien ? ¯\_(ツ)_/¯
  }
  return 0;
}
