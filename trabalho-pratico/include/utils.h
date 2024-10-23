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
#include "entidades/artist.h"
#include "entidades/user.h"

//funções de manipulação de strings
char* remove_aspas(char* str);
char* remove_espacos(char* input);

//funções de validação
int strDigit(char *str);

int nameVerify(char *name);

int emailVerify(char *email);

int birthDateVerify(char* birth_date);

int verify_duration(char* duration);

int verify_year(int year);

//funções de conversão
int calculaIdade(char* birthdate);

// Função que verifica se o formato do ID é válido, i.e, tem que ser [ID]
int isFormatValid(const char *input);

// Função que dado um array de IDs converte de char para long int
long int* convertID(const char *input, int *count);

// Função que remove new lines
void removeEnters(char *input);

#endif