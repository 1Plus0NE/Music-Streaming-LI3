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

int verifyConstituent(char* type, char* constituent);

// Função que verifica se o formato do ID é válido, i.e, tem que ser [ID]
int isFormatValid(const char *input);

// Função que dado um array de IDs converte de char para long int
long int* convertID(const char *input, int *count);

//função auxiliar para libertar a memória de um array de strings.
void freeStringArray(char** array, int num_elements);

//função que divide uma string em substrings com base num delimitador.
char** splitString(const char* str, const char* delimiter, int* num_elements);

// Função que remove new lines
void removeEnters(char *input);

// Função para voltar a transformar o total de segundos na discografia no formato "hh:mm:ss"
char* secondsToString(int totSeconds);

// Função que dado um genero, retorna a posição do genero no array
int getGenreIndex(char *genre, char **genre_array, int genre_count);

// Função que faz sorting do array de generos e o array de likes em função do maior numero de likes
void sortGenresByLikes(char* genres[], long int genre_likes[], int genre_count);

// Função que verifica se uma dada idade está compreendida entre os intervalos de idades
int isAgeInRange(int age, int minAge, int maxAge);

// Função que dados novos arrays de generos e likes, atualiza o conteúdo dos arrays originais de generos e likes
void updateGenresAndLikes(char*** genres, long int** likes, int* size, char** newGenres, long int* newLikes, int newSize);

// Função que converte um inteiro para uma string
char* intToString(int value);

// Converte um long int para uma string
char* longToString(long value);

// Converte um array de long ints para um array de strings
char** longArrayToStringArray(const long* array, int size);

// Função que dado um array de strings, liberta a memória de cada string do array
void freeStringArray(char** string_array, int size);

// Função que cria a diretoria "dataset-errors" e respetivos ficheiros com cabeçalhos
void errosDir();

// Função que recebe uma linha e escreve no csv de erros
void writeErrors(char* line, int csvFile);

#endif