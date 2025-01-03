/**
 * @file history.h
 * @brief Definição da estrutura de histórico e das funções que a manipulam.
 */
#ifndef HISTORY_H
#define HISTORY_H
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils.h"
#include "glib.h"

/**
 * @brief Estrutura que armazena o histórico de um utilizador.
 * 
 */
typedef struct history History;

/**
 * @brief Enumeração que representa a plataforma em que o utilizador ouviu a música.
 * 
 */
typedef enum {
    DESKTOP,
    MOBILE,
} Platform;

/**
 * @brief Função que cria uma entidade do tipo histórico.
 * @details A função recebe o id do histórico, o id do utilizador, o id da música, o timestamp, a duração e a plataforma e cria uma entidade do tipo histórico.
 *
 * @param id Id do histórico.
 * @param user_id Id do utilizador.
 * @param music_id Id da música.
 * @param timestamp Timestamp.
 * @param duration Duração.
 * @param platform Plataforma.
 * @return Apontador para a entidade do tipo histórico.
 */
History* createHistory(long int id, long int user_id, long int music_id, char* timestamp, char* duration, Platform platform);

/**
 * @brief Função que liberta a memória alocada para uma entidade do tipo histórico.
 * @details A função recebe um apontador para a entidade do tipo histórico e liberta a memória alocada para a entidade do tipo histórico.
 *
 * @param history Apontador para a entidade do tipo histórico.
 */
void freeHistory(History* history);

/**
 * @brief Função que insere uma entidade do tipo histórico numa hashtable.
 * @details A função recebe um apontador para a hashtable e um apontador para a entidade do tipo histórico e insere a entidade do tipo histórico na hashtable.
 *
 * @param key Chave da entidade do tipo histórico.
 * @param value Apontador para a entidade do tipo histórico.
 * @param user_data Apontador para a hashtable.
 * @return TRUE se a entidade do tipo histórico foi inserida na hashtable e FALSE caso contrário.
 */
gboolean freeHistoryInTable(gpointer key, gpointer value, gpointer user_data);

/**
 * @brief Função que converte uma string numa plataforma.
 * @details A função recebe uma string e converte-a numa plataforma.
 *
 * @param platform_str String com a plataforma.
 * @return Plataforma.
 */
Platform stringToPlatform(char* platform_str);

/**
 * @brief Função que converte uma plataforma numa string.
 * @details A função recebe uma plataforma e converte-a numa string.
 *
 * @param platform Plataforma.
 * @return String com a plataforma.
 */
char* platformToString(Platform platform);

/**
 * @brief Função que verifica se uma string é uma plataforma válida.
 * @details A função recebe uma string e verifica se é uma plataforma válida.
 *
 * @param platform_str String com a plataforma.
 * @return TRUE se a string é uma plataforma válida e FALSE caso contrário.
 */
int isValidPlatform(char* platform_str);

/**
 * @brief Função que devolve o id de uma entidade do tipo histórico.
 * @details A função recebe um apontador para a entidade do tipo histórico e devolve o id da entidade do tipo histórico.
 *
 * @param h Apontador para a entidade do tipo histórico.
 * @return Id da entidade do tipo histórico.
 */
long int* getHistoryId(History* h);

/**
 * @brief Função que devolve o id do utilizador de uma entidade do tipo histórico.
 * @details A função recebe um apontador para a entidade do tipo histórico e devolve o id do utilizador da entidade do tipo histórico.
 *
 * @param h Apontador para a entidade do tipo histórico.
 * @return Id do utilizador da entidade do tipo histórico.
 */
long int getHistoryUserId(History* h);

/**
 * @brief Função que devolve o id da música de uma entidade do tipo histórico.
 * @details A função recebe um apontador para a entidade do tipo histórico e devolve o id da música da entidade do tipo histórico.
 *
 * @param h Apontador para a entidade do tipo histórico.
 * @return Id da música da entidade do tipo histórico.
 */
long int getHistoryMusicId(History* h);

/**
 * @brief Função que devolve o timestamp de uma entidade do tipo histórico.
 * @details A função recebe um apontador para a entidade do tipo histórico e devolve o timestamp da entidade do tipo histórico.
 *
 * @param h Apontador para a entidade do tipo histórico.
 * @return Timestamp da entidade do tipo histórico.
 */
char* getHistoryTimestamp(History* h);

/**
 * @brief Função que devolve a duração de uma entidade do tipo histórico.
 * @details A função recebe um apontador para a entidade do tipo histórico e devolve a duração da entidade do tipo histórico.
 *
 * @param h Apontador para a entidade do tipo histórico.
 * @return Duração da entidade do tipo histórico.
 */
char* getHistoryDuration(History* h);

/**
 * @brief Função que devolve a plataforma de uma entidade do tipo histórico.
 * @details A função recebe um apontador para a entidade do tipo histórico e devolve a plataforma da entidade do tipo histórico.
 *
 * @param h Apontador para a entidade do tipo histórico.
 * @return Plataforma da entidade do tipo histórico.
 */
Platform getHistoryPlatform(History* h);

/**
 * @brief Função que modifica o id de uma entidade do tipo histórico.
 * @details A função recebe um apontador para a entidade do tipo histórico e um id e modifica o id da entidade do tipo histórico.
 *
 * @param h Apontador para a entidade do tipo histórico.
 * @param id Id da entidade do tipo histórico.
 */
void setHistoryId(History* h, long int id);

/**
 * @brief Função que modifica o id do utilizador de uma entidade do tipo histórico.
 * @details A função recebe um apontador para a entidade do tipo histórico e um id e modifica o id do utilizador da entidade do tipo histórico.
 *
 * @param h Apontador para a entidade do tipo histórico.
 * @param user_id Id do utilizador da entidade do tipo histórico.
 */
void setHistoryUserId(History* h, long int user_id);

/**
 * @brief Função que modifica o id da música de uma entidade do tipo histórico.
 * @details A função recebe um apontador para a entidade do tipo histórico e um id e modifica o id da música da entidade do tipo histórico.
 *
 * @param h Apontador para a entidade do tipo histórico.
 * @param music_id Id da música da entidade do tipo histórico.
 */
void setHistoryMusicId(History* h, long int music_id);

/**
 * @brief Função que modifica o timestamp de uma entidade do tipo histórico.
 * @details A função recebe um apontador para a entidade do tipo histórico e um timestamp e modifica o timestamp da entidade do tipo histórico.
 *
 * @param h Apontador para a entidade do tipo histórico.
 * @param timestamp Timestamp da entidade do tipo histórico.
 */
void setHistoryTimestamp(History* h, char* timestamp);

/**
 * @brief Função que modifica a duração de uma entidade do tipo histórico.
 * @details A função recebe um apontador para a entidade do tipo histórico e uma duração e modifica a duração da entidade do tipo histórico.
 *
 * @param h Apontador para a entidade do tipo histórico.
 * @param duration Duração da entidade do tipo histórico.
 */
void setHistoryDuration(History* h, char* duration);

/**
 * @brief Função que modifica a plataforma de uma entidade do tipo histórico.
 * @details A função recebe um apontador para a entidade do tipo histórico e uma plataforma e modifica a plataforma da entidade do tipo histórico.
 *
 * @param h Apontador para a entidade do tipo histórico.
 * @param platform Plataforma da entidade do tipo histórico.
 */
void setHistoryPlatform(History* h, Platform platform);

#endif