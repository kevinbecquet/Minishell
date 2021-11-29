#include "exe.h"


void get_input(char* input, int taille_max){
  printf("§ ");
  fgets(input,taille_max,stdin);
}


void execute(char*input){

  char* argv1[2];
  switch(fork()){

    case -1 :
      puts("Couldn't fork");
      exit(-1);

    case 0:
      argv1[0] = input;
      argv1[1] = NULL; // toujours terminer avec NULL
      strcat("/bin/",argv1[0]);
      execv(argv1[0],argv1[1]);
      exit(0);

    default :
      printf("\n");
      break;
  }

}
/*
char* separe(char* input){
  char a[TAILLE_MAX];
  return a;
}
*/
