#include "exe.h"


int main(int argc, char const *argv[]) {

  while(1){
    char input[TAILLE_MAX];
    char** tabchar = NULL;
    get_input(input,TAILLE_MAX);

    tabchar = separe(input);

    if(!strcmp(tabchar[0],"exit")) break;
    
    execute (tabchar);

  }

  return 0;
}
