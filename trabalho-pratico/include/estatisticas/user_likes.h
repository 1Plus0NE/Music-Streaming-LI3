#ifndef USER_LIKES_H
#define USER_LIKES_H
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>

typedef struct user_likes UserLikes;

// CONSTRUCTOR

// Função para criar uma estrutura de likes 
UserLikes* createUserLikes(char** genres, long int* likes, int size, int age);

// GETTERS

// Função que retorna uma cópia do array de generos da estrutura de likes
char** getUserLikesArrayGenres(UserLikes* userLikes);

// Função que retorna uma cópia do array de likes da estrutura de likes
long int* getUserLikesArrayLikes(UserLikes* userLikes);

// Função que retorna o tamanho dos arrays da estrutura de likes
int getUserLikesSizeArray(UserLikes* userLikes);

// Função que retorna o apontador da idade da estrutura de likes
int* getUserLikesAge(UserLikes* userLikes);

// Função que retorna a idade da estrutura de likes
int getUserLikesAgeInt(UserLikes* userLikes);

// SETTERS

// Função que altera o array de generos da estrutura de likes
void setUserLikesArrayGenres(UserLikes* userLikes, char** newGenres, int newSize);

// Função que altera o array de likes da estrutura de likes
void setUserLikesArrayLikes(UserLikes* userLikes, long int* newLikes, int newSize);

// FREE

// Função auxiliar para fazer free da estrutura de likes 
void freeUserLikes(UserLikes* userLikes);

#endif