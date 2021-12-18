#include "exe.h"


void get_input(char* input, int taille_max){
  fgets(input,taille_max,stdin);

  // on remplace le retour à la ligne par une fin de chaine
  input[strlen(input)-1] = '\0';
}


void execute(char** tabchar, int arr_plan, int pipe){
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

char** separe(char* input, int* nb_separateurs, char separateur){

  //les espaces nous indiquent les séparations entre les differents arguments d'input
  compte_separateurs(input,nb_separateurs,separateur);


  char** tabchar = (char**)malloc((*nb_separateurs+1)*sizeof(char*));//malloc pour créer un tableau de chaines de caractères, une par argument + la commande elle-même
  for(int i = 0;i<*nb_separateurs;i++) tabchar[i] = (char*)malloc(TAILLE_ARGUMENT*sizeof(char));
  //tabchar[*(nb_espaces+1)] = NULL;

  char* token;//token pour utiliser strtok();
  token = strtok(input,&separateur);//strtok -> découpe la chaine en sous-chaines
  int count = 0;//compteur de "mots"

  while (token != NULL) {
    count++;
    tabchar[count-1] = token;
    token = strtok(NULL, &separateur);
  }
  tabchar[*nb_separateurs+1] = '\0';
  return tabchar;
}

void compte_separateurs(char* input, int* nb_separateurs, char separateur){

  int meme_separateur = 1;
  for(int i = 0;i<strlen(input);i++){
    if(input[i] == separateur && !meme_separateur){
       *nb_separateurs = *nb_separateurs + 1;// la syntaxe *nb_espaces++ ne marche pas (╯°□°)╯︵ ┻━┻
       meme_separateur = 1;
    }
    else if(input[i] != separateur) meme_separateur = 0;
  }
}

void affiche(char** tab){
  int i = 0;
  while(tab[i]){
    printf("tab %d = %s \n",i,tab[i]);
    i++;
  }
  //printf("%s \n",tab[1]);
}

void free_tab(char** tab, int n){
// fonction de desallocation memoir d'un tableau de strings

  for(int i=0;i<n;i++){
    free(tab[i]);
  }

  free(tab);
}
