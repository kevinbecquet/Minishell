#include "exe.h"


void get_input(char* input, int taille_max){
  fgets(input,taille_max,stdin);

  // on remplace le retour à la ligne par une fin de chaine
  input[strlen(input)-1] = '\0';
}


void execute(char** tabchar){
/*
Cette fonction nous permet d'executer la commande entrées dans le shell préalablement decoupées
*/

  switch(fork()){

    case -1 :
      puts("Couldn't fork");
      exit(-1);

    case 0: // execution dans le processus enfant

      // creation d'une chaine pour le chemin d'acces
      char path[TAILLE_MAX];
      strcpy(path,"/bin/");
      strcat(path, tabchar[0]);

      //Execution de la commande associée a path
      int err = execvp(tabchar[0], tabchar);
      if (err) perror("Error  "); // affiche erreur d'execution

      exit(0);

    default :
    // processus parent attend la fin de l'execution du processus enfant avant de se fermer
      wait(NULL);
      break;
  }

}

char** separe(char* input){

  //les espaces nous indiquent les séparations entre les differents arguments d'input
  int nb_espaces = 0, meme_espace = 1;
  for(int i = 1;i<strlen(input);i++){
    if(input[i] == ' ' && !meme_espace){
       nb_espaces++;
       meme_espace = 1;
    }
    else if(input[i] != ' ') meme_espace = 0;
  }
  char** tabchar = (char**)malloc((nb_espaces+1)*sizeof(char*));
  for(int i = 0;i<nb_espaces;i++) tabchar[i] = (char*)malloc(TAILLE_ARGUMENT*sizeof(char));
  tabchar[nb_espaces] = NULL;


  char delimiteur = ' ';//délimiteur pour strtok();
  char* token;//token pour utiliser strtok();
  token = strtok(input,&delimiteur);
  int count = 0;//compteur de "mots"

  while (token != NULL) {
    count++;
    tabchar[count-1] = token;
    token = strtok(NULL, &delimiteur);
  }

  return tabchar;
}
