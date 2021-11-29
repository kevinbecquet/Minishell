#ifndef EXE_H
#define EXE_H

#define TAILLE_MAX 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void get_input(char* input, int taille_max);
void execute(char*input);
char* separe(char* input);



#endif
