/**
 * @file artist.h
 * @brief Definição da entidade artista e das funções que a manipulam.
 */
#ifndef ARTIST_H
#define ARTIST_H
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils.h"
#include "glib.h"

/**
 * @struct artist
 * @brief Estrutura que armazena a informação de um artista.
 */
typedef struct artist Artist;

/**
 * @struct artist_data
 * @brief Estrutura que armazena a informação de um artista numa hashtable.
 */
typedef struct artist_data ArtistData;

/**
 * @brief Enumeração que representa o tipo de artista.
 * 
 */
typedef enum {
    INDIVIDUAL,
    GRUPO
} ArtistType;

/**
 * @brief Cria uma nova instância de um artista.
 * @details Função que aloca memória para uma nova instância de um artista e inicializa os seus valores.
 * 
 * @param id ID do artista.
 * @param name Nome do artista.
 * @param recipe_per_stream Receita por stream do artista.
 * @param id_constituent IDs dos artistas que constituem o artista.
 * @param num_constituent Número de artistas que constituem o artista.
 * @param country País de origem do artista.
 * @param type Tipo do artista.
 *
 * @return Retorna um ponteiro para a nova instância de artista.
 */
Artist* createArtist(long int id, char* name, float recipe_per_stream, long int* id_constituent, int num_constituent, char* country, ArtistType type);

/**
 * @brief Cria uma nova instância de um artista numa hashtable.
 * @details Função que aloca memória para uma nova instância de um artista numa hashtable e inicializa os seus valores.
 * 
 * @param artist_id ID do artista.
 * @param total_reproduction Total de reproduções do artista.
 *
 * @return Retorna um ponteiro para a nova instância de artista numa hashtable.
 */
ArtistData* createArtistData(long int artist_id, int total_reproduction);

/**
 * @brief Conversão de uma string para um tipo de artista.
 * 
 * @param type_str String com o tipo de artista.
 * @return Retorna o tipo de artista correspondente à string.
 */
ArtistType stringToArtistType(char* type_str);

/**
 * @brief Liberta a memória alocada para um artista.
 * @details Função que liberta a memória alocada para um artista.
 * 
 * @param artist Ponteiro para o artista a ser libertado.
 */
void freeArtist(Artist* artist);

/**
 * @brief Liberta a memória alocada para um artista numa hashtable.
 * @details Função que liberta a memória alocada para um artista numa hashtable.
 * 
 * @param artist_data Ponteiro para a estrutura de dados do artista a ser libertado.
 */
void freeArtistData(ArtistData* artist_data);

/**
 * @brief Liberta a memória alocada para um artista numa hashtable.
 * @details Função que liberta a memória alocada para um artista numa hashtable.
 * 
 * @param artist Ponteiro para o artista a ser libertado.
 */
void freeArtistInTable(gpointer value);

/**
 * @brief Função que devolve o ID de um artista.
 * @details Função que devolve o ID de um artista.
 * 
 * @param a Ponteiro para o artista.
 * 
 * @return Retorna o ID do artista.
 */
long int getArtistId(Artist* a);

/**
 * @brief Função que devolve o nome de um artista.
 * @details Função que devolve o nome de um artista.
 * 
 * @param a Ponteiro para o artista.
 * 
 * @return Retorna o nome do artista.
 */
char* getArtistName(Artist* a);

/**
 * @brief Função que devolve a receita por stream de um artista.
 * @details Função que devolve a receita por stream de um artista.
 * 
 * @param a Ponteiro para o artista.
 * 
 * @return Retorna a receita por stream do artista.
 */
float getArtistRecipePerStream(Artist* a);

/**
 * @brief Função que devolve os IDs dos artistas que constituem um artista.
 * @details Função que devolve os IDs dos artistas que constituem um artista.
 * 
 * @param a Ponteiro para o artista.
 * 
 * @return Retorna os IDs dos artistas que constituem o artista.
 */
long int* getArtistIdConstituent(Artist* a);

/**
 * @brief Função que devolve o número de artistas que constituem um artista.
 * @details Função que devolve o número de artistas que constituem um artista.
 * 
 * @param a Ponteiro para o artista.
 * 
 * @return Retorna o número de artistas que constituem o artista.
 */
int getArtistNumConstituent(Artist* a);

/**
 * @brief Função que devolve o país de origem de um artista.
 * @details Função que devolve o país de origem de um artista.
 * 
 * @param a Ponteiro para o artista.
 * 
 * @return Retorna o país de origem do artista.
 */
char* getArtistCountry(Artist* a);

/**
 * @brief Função que devolve o tipo de um artista.
 * @details Função que devolve o tipo de um artista.
 * 
 * @param a Ponteiro para o artista.
 * 
 * @return Retorna o tipo do artista.
 */
ArtistType getArtistType(Artist* a);

/**
 * @brief Função que atualiza o ID de um artista.
 * @details Função que atualiza o ID de um artista.
 * 
 * @param a Ponteiro para o artista.
 * @param id Novo ID do artista.
 */
void setArtistId(Artist* a, int id);

/**
 * @brief Função que atualiza o nome de um artista.
 * @details Função que atualiza o nome de um artista.
 * 
 * @param a Ponteiro para o artista.
 * @param name Novo nome do artista.
 */
void setArtistName(Artist* a, char* name);

/**
 * @brief Função que atualiza a receita por stream de um artista.
 * @details Função que atualiza a receita por stream de um artista.
 * 
 * @param a Ponteiro para o artista.
 * @param recipe_per_stream Nova receita por stream do artista.
 */
void setArtistRecipePerStream(Artist* a, float recipe_per_stream);

/**
 * @brief Função que atualiza os IDs dos artistas que constituem um artista.
 * @details Função que atualiza os IDs dos artistas que constituem um artista.
 * 
 * @param a Ponteiro para o artista.
 * @param id_constituent Novos IDs dos artistas que constituem o artista.
 * @param num_constituent Novo número de artistas que constituem o artista.
 */
void setArtistIdConstituent(Artist* a, int* id_constituent, int num_constituent);

/**
 * @brief Função que atualiza o país de origem de um artista.
 * @details Função que atualiza o país de origem de um artista.
 * 
 * @param a Ponteiro para o artista.
 * @param country Novo país de origem do artista.
 */
void setArtistCountry(Artist* a, char* country);

/**
 * @brief Função que atualiza o tipo de um artista.
 * @details Função que atualiza o tipo de um artista.
 * 
 * @param a Ponteiro para o artista.
 * @param type Novo tipo do artista.
 */
void setArtistType(Artist* a, ArtistType type);

/**
 * @brief Função que devolve o ID de um artista numa hashtable.
 * @details Função que devolve o ID de um artista numa hashtable.
 * 
 * @param a Ponteiro para a estrutura de dados do artista.
 * 
 * @return Retorna o ID do artista.
 */
long int getArtistIdFromData(ArtistData* a);

/**
 * @brief Função que devolve o total de reproduções de um artista numa hashtable.
 * @details Função que devolve o total de reproduções de um artista numa hashtable.
 * 
 * @param a Ponteiro para a estrutura de dados do artista.
 * 
 * @return Retorna o total de reproduções do artista.
 */
int getArtistTotalReproduction(ArtistData* a);

/**
 * @brief Função que atualiza o ID de um artista numa hashtable.
 * @details Função que atualiza o ID de um artista numa hashtable.
 * 
 * @param a Ponteiro para a estrutura de dados do artista.
 * @param artist_id Novo ID do artista.
 */
void setArtistIdFromData(ArtistData* a, long int artist_id);

/**
 * @brief Função que atualiza o total de reproduções de um artista numa hashtable.
 * @details Função que atualiza o total de reproduções de um artista numa hashtable.
 * 
 * @param a Ponteiro para a estrutura de dados do artista.
 * @param total_reproduction Novo total de reproduções do artista.
 */
void setArtistTotalReproduction(ArtistData* a, int total_reproduction);

/**
 * @brief Função que imprime a informação de um artista.
 * @details Função que imprime a informação de um artista.
 * 
 * @param a Ponteiro para o artista.
 */
char* typeToString(ArtistType type);

/**
 * @brief Função que imprime a informação de um artista.
 * @details Função que imprime a informação de um artista.
 * 
 * @param a Ponteiro para o artista.
 */
int isValidArtistType(char* type_str);

#endif