#include "exe.h"


void get_input(char* input, int taille_max){
  printf("§ ");
  fgets(input,taille_max,stdin);

  input[strlen(input)-1] = '\0';// o, remplace le retour à la ligne par une fin de chaine
}


void execute(char** tabchar){

  char path[TAILLE_MAX];

  switch(fork()){

    case -1 :
      puts("Couldn't fork");
      exit(-1);

    case 0:


      //argv1[0] = input;
      //argv1[1] = NULL; // toujours terminer avec NULL

      // creation d'une chaine pour le chemin d'acces
      strcpy(path,"/bin/");
      strcat(path, tabchar[0]);
      int err = execvp(tabchar[0], tabchar);
      if (err) perror("Error  ");

      exit(0);

    default :
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
