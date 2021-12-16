#include "exe.h"


void get_input(char* input, int taille_max){
  fgets(input,taille_max,stdin);

  // on remplace le retour à la ligne par une fin de chaine
  input[strlen(input)-1] = '\0';
}


void execute(char** tabchar, int arr_plan){
/*
Cette fonction nous permet d'executer la commande entrées dans le shell préalablement decoupée
*/

  // Traitement des commandes builtin pwd et cd

  if(!strcmp(tabchar[0],"pwd")){
    char path[TAILLE_MAX];

    // affiche le repetoire courant ou l'erreur si impossible
    if(getcwd(path,TAILLE_MAX))
       printf("%s\n", path);

    else perror("pwd Error");


  }

  else if(!strcmp(tabchar[0],"cd")){
    //  execution de cd + affichage de l'erreur en cas de problème
    if(chdir(tabchar[1]))
      perror("cd Error");

  }

  else{
    //traitement des commandes non builtin
    int pid = fork();
    switch(pid){

      case -1 :
        puts("Couldn't fork");
        exit(-1);

      case 0: ;// execution dans le processus enfant

        // creation d'une chaine pour le chemin d'acces
        char path[TAILLE_MAX];
        strcpy(path,"/bin/");
        strcat(path, tabchar[0]);

        //Execution de la commande associée a path
        int err = execvp(tabchar[0], tabchar);
        if (err) perror("Error  "); // affiche erreur d'execution

        exit(0);

      default :
      // processus parent attend la fin de l'execution du processus enfant avant de se fermer si on execute en premier plan
        if(!arr_plan){
          wait(NULL);
        }
        else{//sinon on attends pas et on affiche le pid, comme dans le vrai shell je suppose
          printf("[1] %d\n",pid);
        }
        break;
    }
  }
}

char** separe(char* input, int* nb_espaces){

  //les espaces nous indiquent les séparations entre les differents arguments d'input
  int meme_espace = 1;
  for(int i = 0;i<strlen(input);i++){
    if(input[i] == ' ' && !meme_espace){
       *nb_espaces = *nb_espaces + 1;// la syntaxe *nb_espaces++ ne marche pas (╯°□°)╯︵ ┻━┻
       meme_espace = 1;
    }
    else if(input[i] != ' ') meme_espace = 0;
  }

  char** tabchar = (char**)malloc((*nb_espaces+1)*sizeof(char*));//malloc pour créer un tableau de chaines de caractères, une par argument + la commande elle-même
  for(int i = 0;i<*nb_espaces;i++) tabchar[i] = (char*)malloc(TAILLE_ARGUMENT*sizeof(char));
  tabchar[*(nb_espaces+1)] = NULL;

  char delimiteur = ' ';//délimiteur pour strtok();
  char* token;//token pour utiliser strtok();
  token = strtok(input,&delimiteur);//strtok -> découpe la chaine en sous-chaines
  int count = 0;//compteur de "mots"

  while (token != NULL) {
    count++;
    tabchar[count-1] = token;
    token = strtok(NULL, &delimiteur);
  }
  tabchar[*nb_espaces+1] = '\0';
  return tabchar;
}


void affiche(char** tab){
  int i = 0;
  while(tab[i]){
    printf("%s \n",tab[i]);
    i++;
  }
}

void free_tab(char** tab, int n){
// fonction de desallocation memoir d'un tableau de strings

  for(int i=0;i<n;i++){
    free(tab[i]);
  }

  free(tab);
}
