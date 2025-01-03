/**
 * @file gestor_user.h
 * @brief Definição da estrutura do gestor de utilizadores e das funções que a manipulam.
 */
#ifndef GESTOR_USER_H
#define GESTOR_USER_H
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "../entidades/user.h"
#include "../estatisticas/user_likes.h"
#include <glib.h>
#include <stdbool.h>

/**
 * @brief Estrutura que armazena a informação dos utilizadores.
 * 
 */
typedef struct gestor_user GestorUser;

/**
 * @brief Estrutura que armazena a informação dos iterador de utilizadores.
 * 
 */
typedef struct user_iterator UserIterator;

typedef void (*GHFunc)(void *key, void *value, void *user_data);

/**
 * @brief Função que cria uma entidade do tipo gestor de utilizadores.
 * @details A função aloca memória para a estrutura do gestor de utilizadores e inicializa a tabela de utilizadores.
 * 
 * @return Apontador para a entidade do tipo gestor de utilizadores.
 */
GestorUser* createGestorUser();

/**
 * @brief Função que adiciona um utilizador à tabela.
 * 
 * @param gestorUser Apontador para a entidade do tipo gestor de utilizadores.
 * @param user Utilizador a ser adicionado.
 */
void addUser(GestorUser* gestorUser, User* user);

/**
 * @brief Função que remove um utilizador da tabela.
 * 
 * @param gestorUser Apontador para a entidade do tipo gestor de utilizadores.
 * @param username Username do utilizador a ser removido.
 */
void removeUser(GestorUser* gestorUser, char* username);

/**
 * @brief Função que procura um utilizador na tabela.
 * 
 * @param gestorUser Apontador para a entidade do tipo gestor de utilizadores.
 * @param username Username do utilizador a ser procurado.
 * @return Apontador para o utilizador encontrado.
 */
User* searchUser(GestorUser* gestorUser, char* username);

/**
 * @brief Função que faz um ciclo sobre todos os utilizadores da tabela.
 * 
 * @param gestorUser Apontador para a entidade do tipo gestor de utilizadores.
 * @param func Função a ser aplicada a cada utilizador.
 * @param user_data Dados a serem passados para a função.
 */
void foreachUser(GestorUser* gestorUser, GHFunc func, gpointer user_data);

/**
 * @brief Função que cria um iterador de utilizadores.
 * 
 * @param gestorUser Apontador para a entidade do tipo gestor de utilizadores.
 * @return Apontador para o iterador de utilizadores.
 */
UserIterator* createUserIterator(GestorUser* gestorUser);

/**
 * @brief Função que retorna o próximo utilizador do iterador.
 * 
 * @param iterator Apontador para o iterador de utilizadores.
 * @return Apontador para o próximo utilizador.
 */
User* getNextUser(UserIterator* iterator);

/**
 * @brief Função que liberta a memória alocada para o iterador de utilizadores.
 * 
 * @param iterator Apontador para o iterador de utilizadores.
 */
void freeUserIterator(UserIterator* iterator);

/**
 * @brief Função que procura uma entidade do tipo userLikes na tabela.
 * 
 * @param gestorUser Apontador para a entidade do tipo gestor de utilizadores.
 * @param age Idade do utilizador.
 */
UserLikes* searchUserLikes(GestorUser* gestorUser, int age);

/**
 * @brief Função que adiciona uma entidade do tipo userLikes à tabela.
 * 
 * @param gestorUser Apontador para a entidade do tipo gestor de utilizadores.
 * @param genres Array de géneros.
 * @param likes Array de likes.
 * @param size Tamanho dos arrays.
 * @param age Idade do utilizador.
 */
void addUserLikes(GestorUser* gestorUser, char** genres, long int* likes, int size, int age);

/**
 * @brief Função que devolve o array de userLikes.
 * 
 * @param gestorUser Apontador para a entidade do tipo gestor de utilizadores.
 * @return Apontador para o array de userLikes.
 */
GPtrArray* getUserLikesArray(GestorUser* gestorUser);

/**
 * @brief Função que devolve o userLikes de um determinado index do array.
 * 
 * @param gestorUser Apontador para a entidade do tipo gestor de utilizadores.
 * @param index Index do userLikes no array.
 * @return Apontador para o userLikes.
 */
UserLikes* getUserLikeFromArray(GestorUser* gestorUser, int index);

/**
 * @brief Função que liberta a memória alocada para a entidade do tipo gestor de utilizadores.
 * 
 * @param gestorUser Apontador para a entidade do tipo gestor de utilizadores.
 */
void freeGestorUser(GestorUser* gestorUser);

#endif