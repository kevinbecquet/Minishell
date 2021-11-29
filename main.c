#include "exe.h"


int main(int argc, char const *argv[]) {


char input[TAILLE_MAX];
char** tabchar = NULL;
get_input(input,TAILLE_MAX);

tabchar = separe(input);
printf("______________________\n");
for(int i = 0; i<10; i++){
  printf("%s\n",tabchar[i]);
}

//execute (input);

  return 0;
}
