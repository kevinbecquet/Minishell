#include "exe.h"


int main(int argc, char const *argv[]) {


char input[TAILLE_MAX];

get_input(input,TAILLE_MAX);
//printf("chaine : %s\n",input );
execute (input);
separe(input);
/*
char input[100];
str commands[];
while(1){
    input = acquisition();
    exe_input(input);
    if( command exit ) break;
}
*/
  return 0;
}
