#ifndef EXE_H
#define EXE_H

#define TAILLE_MAX 256
#define TAILLE_ARGUMENT 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void get_input(char* input, int taille_max);
void execute(char** input,int arr_plan);
char** separe(char* input, int* nb_espaces);
void free_tab(char** tab, int n);
void affiche(char** tab);


#endif
