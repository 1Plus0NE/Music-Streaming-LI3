/**
 * @file discography.h
 * @brief Definição da estrutura de discografia e das funções que a manipulam.
 */
#ifndef DISCOGRAPHY_H
#define DISCOGRAPHY_H
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils.h"
#include "glib.h"

/**
 * @brief Estrutura que armazena a discografia de um artista.
 * 
 */
typedef struct discography Discography;

/**
 * @brief Funcão que ordena a discografia de um artista por ordem crescente de duração.
 * @details A função recebe um apontador para a cabeça da lista ligada de discografia e ordena a lista por ordem crescente de duração.
 *
 * @param head Apontador para a cabeça da lista ligada de discografia.
 */
void sortByDuration(Discography** head);

/**
 * @brief Função que adiciona uma duracao à discografia de um artista.
 * @details A função recebe um apontador para a cabeça da lista ligada de discografia, a duração a adicionar e o id da música a que a duração corresponde.
 *
 * @param disco Apontador para a cabeça da lista ligada de discografia.
 * @param duration Duração a adicionar.
 * @param id Id da música a que a duração corresponde.
 */
void durationAdd(Discography* disco, const char* duration, long int id);

/**
 * @brief Função que liberta a memória alocada para a discografia de um artista.
 * @details A função recebe um apontador para a cabeça da lista ligada de discografia e liberta a memória alocada para a discografia.
 *
 * @param disco Apontador para a cabeça da lista ligada de discografia.
 */
void freeDiscography(Discography* disco);

/**
 * @brief Função que insere um artista na discografia de um artista.
 * @details A função recebe um apontador para a cabeça da lista ligada de discografia, o id do artista, o nome do artista, o país do artista e o tipo do artista e insere o artista na discografia.
 *
 * @param disco Apontador para a cabeça da lista ligada de discografia.
 * @param id Id do artista.
 * @param name Nome do artista.
 * @param country País do artista.
 * @param type Tipo do artista.
 */
void artistInsert(Discography** disco, long int id, const char* name, const char* country, ArtistType type);

/**
 * @brief Função que devolve o id da discografia.
 * @details A função recebe um apontador para a discografia e devolve o id da discografia.
 *
 * @param d Apontador para a discografia.
 * @return Id da discografia.
 */
long int* getDiscographyId(Discography* d);

/**
 * @brief Função que devolve o nome da discografia.
 * @details A função recebe um apontador para a discografia e devolve o nome da discografia.
 *
 * @param d Apontador para a discografia.
 * @return Nome da discografia.
 */
char* getDiscographyName(Discography* d);

/**
 * @brief Função que devolve o país da discografia.
 * @details A função recebe um apontador para a discografia e devolve o país da discografia.
 *
 * @param d Apontador para a discografia.
 * @return País da discografia.
 */
char* getDiscographyCountry(Discography* d);

/**
 * @brief Função que devolve a duração da discografia.
 * @details A função recebe um apontador para a discografia e devolve a duração da discografia.
 *
 * @param d Apontador para a discografia.
 * @return Duração da discografia.
 */
int getDiscographyDuration(Discography* d);

/**
 * @brief Função que devolve o tipo da discografia.
 * @details A função recebe um apontador para a discografia e devolve o tipo da discografia.
 *
 * @param d Apontador para a discografia.
 * @return Tipo da discografia.
 */
ArtistType getDiscographyType(Discography* d);

/**
 * @brief Função que devolve o apontador para a próxima discografia.
 * @details A função recebe um apontador para a discografia e devolve o apontador para a próxima discografia.
 *
 * @param d Apontador para a discografia.
 * @return Apontador para a próxima discografia.
 */
Discography* getDiscographyNext(Discography* d);

/**
 * @brief Função que define o id da discografia.
 * @details A função recebe um apontador para a discografia e o id da discografia e define o id da discografia.
 *
 * @param d Apontador para a discografia.
 * @param id Id da discografia.
 */
void setDiscographyId(Discography* d, long int id);

/**
 * @brief Função que define o nome da discografia.
 * @details A função recebe um apontador para a discografia e o nome da discografia e define o nome da discografia.
 *
 * @param d Apontador para a discografia.
 * @param name Nome da discografia.
 */
void setDiscographyName(Discography* d, char* name);

/**
 * @brief Função que define o país da discografia.
 * @details A função recebe um apontador para a discografia e o país da discografia e define o país da discografia.
 *
 * @param d Apontador para a discografia.
 * @param country País da discografia.
 */
void setDiscographyCountry(Discography* d, char* country);

/**
 * @brief Função que define a duração da discografia.
 * @details A função recebe um apontador para a discografia e a duração da discografia e define a duração da discografia.
 *
 * @param d Apontador para a discografia.
 * @param duration Duração da discografia.
 */
void setDiscographyDuration(Discography* d, int duration);

/**
 * @brief Função que define o tipo da discografia.
 * @details A função recebe um apontador para a discografia e o tipo da discografia e define o tipo da discografia.
 *
 * @param d Apontador para a discografia.
 * @param type Tipo da discografia.
 */
void setDiscographyType(Discography* d, ArtistType type);

/**
 * @brief Função que define o apontador para a próxima discografia.
 * @details A função recebe um apontador para a discografia e o apontador para a próxima discografia e define o apontador para a próxima discografia.
 *
 * @param d Apontador para a discografia.
 * @param next Apontador para a próxima discografia.
 */
void setDiscographyNext(Discography* d, Discography* next);

#endif