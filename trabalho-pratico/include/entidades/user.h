/**
 * @file user.h
 * @brief Definição da estrutura de utilizador e das funções que a manipulam.
 */
#ifndef USER_H
#define USER_H
#ifndef _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils.h"
#include <glib.h>

/**
 * @brief Estrutura que armazena a informação de um utilizador.
 * 
 */
typedef struct user User;

/**
 * @brief Enumeração que representa o tipo de subscrição de um utilizador.
 * 
 */
typedef enum {
    PREMIUM,
    NORMAL
} SubscriptionType;

/**
 * @brief Função que cria uma entidade do tipo utilizador.
 * @details A função recebe o username, o email, o primeiro nome, o último nome, a data de nascimento, o país, o tipo de subscrição, os ids das músicas gostadas e o número de músicas gostadas e cria uma entidade do tipo utilizador.
 *
 * @param username Username.
 * @param email Email.
 * @param first_name Primeiro nome.
 * @param last_name Último nome.
 * @param birth_date Data de nascimento.
 * @param country País.
 * @param subscription_type Tipo de subscrição.
 * @param liked_musics_id Ids das músicas gostadas.
 * @param num_liked_musics Número de músicas gostadas
 * @return Apontador para a entidade do tipo utilizador.
 */
User* createUser(char* username, char* email, char* first_name, char* last_name, char* birth_date , char* country, SubscriptionType subscription_type, long int* liked_musics_id, int num_liked_musics);

/**
 * @brief Função que liberta a memória ocupada pela entidade do tipo utilizador.
 * 
 * @param user Apontador para a entidade do tipo utilizador.
 */
void freeUser(User* user);

/**
 * @brief Função que insere uma entidade do tipo utilizador numa hashtable.
 * @details A função recebe um apontador para a hashtable e um apontador para a entidade do tipo utilizador e insere a entidade do tipo utilizador na hashtable.
 *
 * @param key Chave da entidade do tipo utilizador.
 * @param value Apontador para a entidade do tipo utilizador.
 * @param user_data Apontador para a hashtable.
 */
gboolean freeUserInTable(gpointer key, gpointer value, gpointer user_data);

/**
 * @brief Função que retorna o username de um utilizador.
 * @details A função recebe um apontador para a entidade do tipo utilizador e retorna o username do utilizador.
 *
 * @param u Apontador para a entidade do tipo utilizador.
 */
char* getUserUsername(User* u);

/**
 * @brief Função que retorna o email de um utilizador.
 * @details A função recebe um apontador para a entidade do tipo utilizador e retorna o email do utilizador.
 *
 * @param u Apontador para a entidade do tipo utilizador.
 */
char* getUserEmail(User* u);

/**
 * @brief Função que retorna o primeiro nome de um utilizador.
 * @details A função recebe um apontador para a entidade do tipo utilizador e retorna o primeiro nome do utilizador.
 *
 * @param u Apontador para a entidade do tipo utilizador.
 */
char* getUserFirstName(User* u);

/**
 * @brief Função que retorna o último nome de um utilizador.
 * @details A função recebe um apontador para a entidade do tipo utilizador e retorna o último nome do utilizador.
 *
 * @param u Apontador para a entidade do tipo utilizador.
 */
char* getUserLastName(User* u);

/**
 * @brief Função que retorna a data de nascimento de um utilizador.
 * @details A função recebe um apontador para a entidade do tipo utilizador e retorna a data de nascimento do utilizador.
 *
 * @param u Apontador para a entidade do tipo utilizador.
 */
char* getUserBirthDate(User* u);

/**
 * @brief Função que retorna o país de um utilizador.
 * @details A função recebe um apontador para a entidade do tipo utilizador e retorna o país do utilizador.
 *
 * @param u Apontador para a entidade do tipo utilizador.
 */
char* getUserCountry(User* u);

/**
 * @brief Função que retorna o tipo de subscrição de um utilizador.
 * @details A função recebe um apontador para a entidade do tipo utilizador e retorna o tipo de subscrição do utilizador.
 *
 * @param u Apontador para a entidade do tipo utilizador.
 */
SubscriptionType getUserSubscriptionType(User* u);

/**
 * @brief Função que retorna os ids das músicas gostadas por um utilizador.
 * @details A função recebe um apontador para a entidade do tipo utilizador e retorna os ids das músicas gostadas pelo utilizador.
 *
 * @param u Apontador para a entidade do tipo utilizador.
 */
long int* getUserLikedMusics(User* u);

/**
 * @brief Função que retorna o número de músicas gostadas por um utilizador.
 * @details A função recebe um apontador para a entidade do tipo utilizador e retorna o número de músicas gostadas pelo utilizador.
 *
 * @param u Apontador para a entidade do tipo utilizador.
 */
int getUserNumLikedMusics(User* u);

/**
 * @brief Função que altera o username de um utilizador.
 * @details A função recebe um apontador para a entidade do tipo utilizador e um apontador para uma string e altera o username do utilizador.
 *
 * @param u Apontador para a entidade do tipo utilizador.
 * @param username Username.
 */
void setUserUsername(User* u, char* username);

/**
 * @brief Função que altera o email de um utilizador.
 * @details A função recebe um apontador para a entidade do tipo utilizador e um apontador para uma string e altera o email do utilizador.
 *
 * @param u Apontador para a entidade do tipo utilizador.
 * @param email Email.
 */
void setUserEmail(User* u, char* email);

/**
 * @brief Função que altera o primeiro nome de um utilizador.
 * @details A função recebe um apontador para a entidade do tipo utilizador e um apontador para uma string e altera o primeiro nome do utilizador.
 *
 * @param u Apontador para a entidade do tipo utilizador.
 * @param first_name Primeiro nome.
 */
void setUserFirstName(User* u, char* first_name);

/**
 * @brief Função que altera o último nome de um utilizador.
 * @details A função recebe um apontador para a entidade do tipo utilizador e um apontador para uma string e altera o último nome do utilizador.
 *
 * @param u Apontador para a entidade do tipo utilizador.
 * @param last_name Último nome.
 */
void setUserLastName(User* u, char* last_name);

/**
 * @brief Função que altera a data de nascimento de um utilizador.
 * @details A função recebe um apontador para a entidade do tipo utilizador e um apontador para uma string e altera a data de nascimento do utilizador.
 *
 * @param u Apontador para a entidade do tipo utilizador.
 * @param birth_date Data de nascimento.
 */
void setUserBirthDate(User* u, char* birth_date);

/**
 * @brief Função que altera o país de um utilizador.
 * @details A função recebe um apontador para a entidade do tipo utilizador e um apontador para uma string e altera o país do utilizador.
 *
 * @param u Apontador para a entidade do tipo utilizador.
 * @param country País.
 */
void setUserCountry(User* u, char* country);

/**
 * @brief Função que altera o tipo de subscrição de um utilizador.
 * @details A função recebe um apontador para a entidade do tipo utilizador e um tipo de subscrição e altera o tipo de subscrição do utilizador.
 *
 * @param u Apontador para a entidade do tipo utilizador.
 * @param subscription_type Tipo de subscrição.
 */
void setUserSubscriptionType(User* u, SubscriptionType subscription_type);

/**
 * @brief Função que altera os ids das músicas gostadas por um utilizador.
 * @details A função recebe um apontador para a entidade do tipo utilizador, um apontador para um array de ids de músicas e o número de músicas gostadas e altera os ids das músicas gostadas pelo utilizador.
 *
 * @param u Apontador para a entidade do tipo utilizador.
 * @param liked_musics_id Ids das músicas gostadas.
 * @param num_liked_musics Número de músicas gostadas.
 */
void setUserLikedMusics(User* u, long int* liked_musics_id, int num_liked_musics);

/**
 * @brief Função que altera o número de músicas gostadas por um utilizador.
 * @details A função recebe um apontador para a entidade do tipo utilizador e um número e altera o número de músicas gostadas pelo utilizador.
 *
 * @param u Apontador para a entidade do tipo utilizador.
 * @param num_liked_musics Número de músicas gostadas.
 */
void setUserNumLikedMusics(User* u, int num_liked_musics);

/**
 * @brief Função que converte uma string para o tipo de subscrição.
 * @details A função recebe uma string e converte-a para o tipo de subscrição correspondente.
 *
 * @param subType String.
 * @return Tipo de subscrição.
 */
SubscriptionType stringToSubscriptionType(char* subType);

#endif