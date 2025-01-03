/**
 * @file user_likes.h
 * @brief Definição da estrutura de likes de um utilizador
 */
#ifndef USER_LIKES_H
#define USER_LIKES_H
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>

/**
 * @brief Estrutura que guarda os likes de um utilizador
 *
 */
typedef struct user_likes UserLikes;

/**
 * @brief Função que inicializa a estrutura de likes de um utilizador
 * 
 * @param genres Array de generos
 * @param likes Array de likes
 * @param size Tamanho dos arrays
 * @param age Idade do utilizador
 * @return UserLikes* Apontador para a estrutura de likes
 */
UserLikes* createUserLikes(char** genres, long int* likes, int size, int age);

/**
 * @brief Função que retorna uma cópia do array de generos da estrutura de likes
 * 
 * @param userLikes Estrutura de likes
 * @return char** Array de generos
 */
char** getUserLikesArrayGenres(UserLikes* userLikes);

/**
 * @brief Função que retorna uma cópia do array de likes da estrutura de likes
 * 
 * @param userLikes Estrutura de likes
 * @return long int* Array de likes
 */
long int* getUserLikesArrayLikes(UserLikes* userLikes);

/**
 * @brief Função que retorna o tamanho do array de generos da estrutura de likes
 * 
 * @param userLikes Estrutura de likes
 * @return int Tamanho do array de generos
 */
int getUserLikesSizeArray(UserLikes* userLikes);

/**
 * @brief Função que retorna a idade da estrutura de likes
 * 
 * @param userLikes Estrutura de likes
 * @return int Idade do utilizador
 */
int* getUserLikesAge(UserLikes* userLikes);

/**
 * @brief Função que retorna a idade da estrutura de likes
 * 
 * @param userLikes Estrutura de likes
 * @return int Idade do utilizador
 */
int getUserLikesAgeInt(UserLikes* userLikes);

/**
 * @brief Função que retorna o número de likes da estrutura de likes
 * 
 * @param userLikes Estrutura de likes
 * @return int Número de likes
 */
void setUserLikesArrayGenres(UserLikes* userLikes, char** newGenres, int newSize);

/**
 * @brief Função que retorna o número de likes da estrutura de likes
 * 
 * @param userLikes Estrutura de likes
 * @return int Número de likes
 */
void setUserLikesArrayLikes(UserLikes* userLikes, long int* newLikes, int newSize);

/**
 * @brief Função que liberta a memória alocada para a estrutura de likes
 * 
 * @param userLikes Estrutura de likes
 */
void freeUserLikes(UserLikes* userLikes);

#endif