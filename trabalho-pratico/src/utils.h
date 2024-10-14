#ifndef UTILS_H
#define UTILS_H
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

//funções de manipulação de strings
char* remove_aspas(char* str);

//funções de validação
int strDigit(char *str);

int nameVerify(char *name);

int emailVerify(char *email);

int birthDateVerify(char* birth_date);

int verify_music(char* duration);

int verify_year(int year);

//funções de conversão
int calculaIdade(char* birthdate);

#endif