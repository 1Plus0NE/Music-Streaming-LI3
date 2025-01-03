/**
 * @file album.h
 * @brief Definição da entidade álbum.
 */

#ifndef ALBUM_H
#define ALBUM_H
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils.h"
#include "glib.h"

/**
 * @struct album
 * @brief Estrutura que armazena a informação de um álbum.
 */
typedef struct album Album;

/**
 * @brief Cria uma nova instância de um álbum.
 * @details Função que aloca memória para uma nova instância de um álbum e inicializa os seus valores.
 * 
 * @param id ID do álbum.
 * @param title Título do álbum.
 * @param artist_ids IDs dos artistas que participaram no álbum.
 * @param num_artists Número de artistas que participaram no álbum.
 * @param year Ano de lançamento do álbum.
 * @param producers Produtores do álbum.
 * @param num_producers Número de produtores do álbum.
 *
 * @return Retorna um ponteiro para a nova instância de álbum.
 */
Album* createAlbum(long int id, char* title, long int* artist_ids, int num_artists,  int year, char** producers, int num_producers);

/**
 * @brief Liberta a memória alocada para um álbum.
 * @details Função que liberta a memória alocada para um álbum.
 * 
 * @param album Ponteiro para o álbum a ser libertado.
 */
void freeAlbum(Album* album);

/**
 * @brief Função que liberta a memória alocada para um álbum numa hashtable.
 * @details Função que liberta a memória alocada para um álbum numa hashtable.
 * 
 * @param album Ponteiro para o álbum a ser libertado.
 */
void freeAlbumInTable(gpointer value);

/**
 * @brief Função que devolve o ID de um álbum.
 * @details Função que devolve o ID de um álbum.
 * 
 * @param album Ponteiro para o álbum.
 * 
 * @return Retorna o ID do álbum.
 */
long int getAlbumId(Album* album);

/**
 * @brief Função que devolve o título de um álbum.
 * @details Função que devolve o título de um álbum.
 * 
 * @param album Ponteiro para o álbum.
 * 
 * @return Retorna o título do álbum.
 */
char* getAlbumTitle(Album* album);

/**
 * @brief Função que devolve os IDs dos artistas que participaram num álbum.
 * @details Função que devolve os IDs dos artistas que participaram num álbum.
 * 
 * @param album Ponteiro para o álbum.
 * 
 * @return Retorna os IDs dos artistas que participaram no álbum.
 */
long int* getAlbumArtistIds(Album* album);

/**
 * @brief Função que devolve o número de artistas que participaram num álbum.
 * @details Função que devolve o número de artistas que participaram num álbum.
 * 
 * @param album Ponteiro para o álbum.
 * 
 * @return Retorna o número de artistas que participaram no álbum.
 */
int getAlbumNumArtists(Album* album);

/**
 * @brief Função que devolve o ano de lançamento de um álbum.
 * @details Função que devolve o ano de lançamento de um álbum.
 * 
 * @param album Ponteiro para o álbum.
 * 
 * @return Retorna o ano de lançamento do álbum.
 */
int getAlbumYear(Album* album);

/**
 * @brief Função que devolve os produtores de um álbum.
 * @details Função que devolve os produtores de um álbum.
 * 
 * @param album Ponteiro para o álbum.
 * 
 * @return Retorna os produtores do álbum.
 */
char** getAlbumProducers(Album* album);

/**
 * @brief Função que devolve o número de produtores de um álbum.
 * @details Função que devolve o número de produtores de um álbum.
 * 
 * @param album Ponteiro para o álbum.
 * 
 * @return Retorna o número de produtores do álbum.
 */
int getAlbumNumProducers(Album* album);

/**
 * @brief Função que atualiza o ID de um álbum.
 * @details Função que atualiza o ID de um álbum.
 * 
 * @param album Ponteiro para o álbum.
 * @param id Novo ID do álbum.
 */
void setAlbumId(Album* album, long int id);

/**
 * @brief Função que atualiza o título de um álbum.
 * @details Função que atualiza o título de um álbum.
 * 
 * @param album Ponteiro para o álbum.
 * @param title Novo título do álbum.
 */
void setAlbumTitle(Album* album, char* title);

/**
 * @brief Função que atualiza os IDs dos artistas que participaram num álbum.
 * @details Função que atualiza os IDs dos artistas que participaram num álbum.
 * 
 * @param album Ponteiro para o álbum.
 * @param artist_ids Novos IDs dos artistas que participaram no álbum.
 * @param num_artists Novo número de artistas que participaram no álbum.
 */
void setAlbumArtistIds(Album* album, long int* artist_ids, int num_artists);

/**
 * @brief Função que atualiza o número de artistas que participaram num álbum.
 * @details Função que atualiza o número de artistas que participaram num álbum.
 * 
 * @param album Ponteiro para o álbum.
 * @param num_artists Novo número de artistas que participaram no álbum.
 */
void setAlbumNumArtists(Album* album, int num_artists);

/**
 * @brief Função que atualiza o ano de lançamento de um álbum.
 * @details Função que atualiza o ano de lançamento de um álbum.
 * 
 * @param album Ponteiro para o álbum.
 * @param year Novo ano de lançamento do álbum.
 */
void setAlbumYear(Album* album, int year);

/**
 * @brief Função que atualiza os produtores de um álbum.
 * @details Função que atualiza os produtores de um álbum.
 * 
 * @param album Ponteiro para o álbum.
 * @param producers Novos produtores do álbum.
 * @param num_producers Novo número de produtores do álbum.
 */
void setAlbumProducers(Album* album, char** producers, int num_producers);

/**
 * @brief Função que atualiza o número de produtores de um álbum.
 * @details Função que atualiza o número de produtores de um álbum.
 * 
 * @param album Ponteiro para o álbum.
 * @param num_producers Novo número de produtores do álbum.
 */
void setAlbumNumProducers(Album* album, int num_producers);

#endif