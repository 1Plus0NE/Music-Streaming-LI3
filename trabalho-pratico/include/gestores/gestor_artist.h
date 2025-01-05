/**
 * @file gestor_artist.h
 * @brief Definição da estrutura do gestor de artistas e das funções que a manipulam.
 */
#ifndef GESTOR_ARTIST_H
#define GESTOR_ARTIST_H
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../entidades/artist.h"
#include "../entidades/discography.h"
#include <glib.h>

/**
 * @brief Estrutura que armazena a informação dos artistas.
 * 
 */
typedef struct gestor_artist GestorArtist;

typedef void (*GHFunc)(void *key, void *value, void *user_data);

/**
 * @brief Função que cria uma entidade do tipo gestor de artistas.
 * @details A função aloca memória para a estrutura do gestor de artistas e inicializa a tabela de artistas.
 * 
 * @return Apontador para a entidade do tipo gestor de artistas.
 */
GestorArtist* createGestorArtist();

/**
 * @brief Função que adiciona um artista à tabela.
 * 
 * @param gestorArtist Apontador para a entidade do tipo gestor de artistas.
 * @param artist Artista a ser adicionado.
 */
void addArtist(GestorArtist* gestorArtist, Artist* artist);

/**
 * @brief Função que remove um artista da tabela.
 * @details A função recebe o id de um artista e remove-o da tabela de artistas.
 * 
 * @param gestorArtist Apontador para a entidade do tipo gestor de artistas.
 * @param id Id do artista a ser removido.
 */
void removeArtist(GestorArtist* gestorArtist, long int id);

/**
 * @brief Função que retorna um artista da tabela.
 * @details A função recebe o id de um artista e retorna-o da tabela de artistas.
 * 
 * @param gestorArtist Apontador para a entidade do tipo gestor de artistas.
 * @param id Id do artista a ser retornado.
 * @return Apontador para o artista.
 */
Artist* searchArtist(GestorArtist* gestorArtist, long int id);

/**
 * @brief Função que faz um ciclo sobre a tabela de artistas.
 * 
 * @param gestorArtist Apontador para a entidade do tipo gestor de artistas.
 * @param func Função a ser aplicada a cada artista.
 * @param user_data Dados a serem passados à função.
 */
void foreachArtist(GestorArtist* gestorArtist, GHFunc func, gpointer user_data);

/**
 * @brief Função que liberta a memória alocada para o gestor de artistas.
 * @details A função liberta a memória alocada para o gestor de artistas.
 * 
 * @param gestorArtist Apontador para a entidade do tipo gestor de artistas.
 */
void freeGestorArtist(GestorArtist* gestorArtist);

/**
 * @brief Função que adiciona um artista à tabela de contador de álbuns.
 * 
 * @param gestorArtist Apontador para a entidade do tipo gestor de artistas.
 * @param artist_id Id do artista a ser adicionado.
 * @param count Número de álbuns do artista.
 */
void addIndividualAlbumCount(GestorArtist* gestorArtist, long int artist_id, int count);

/**
 * @brief Função que atualiza o número de álbuns de um artista na tabela de contador de álbuns.
 * 
 * @param gestorArtist Apontador para a entidade do tipo gestor de artistas.
 * @param artist_id Id do artista a ser atualizado.
 * @param count Novo número de álbuns do artista.
 */
void updateIndividualAlbumCount(GestorArtist* gestorArtist, long int artist_id, int count);

/**
 * @brief Função que retorna o número de álbuns de um artista na tabela de contador de álbuns.
 * 
 * @param gestorArtist Apontador para a entidade do tipo gestor de artistas.
 * @param artist_id Id do artista a ser retornado.
 * @return Número de álbuns do artista.
 */
int getIndividualAlbumCount(GestorArtist* gestorArtist, long int artist_id);

/**
 * @brief Função que remove um artista da tabela de contador de álbuns.
 * 
 * @param gestorArtist Apontador para a entidade do tipo gestor de artistas.
 * @param artist_id Id do artista a ser removido.
 */
void removeIndividualAlbumCount(GestorArtist* gestorArtist, long int artist_id);

/**
 * @brief Função que liberta a memória alocada para os artistas na tabela de contador de álbuns.
 * 
 * @param key Chave da tabela.
 * @param value Valor da tabela.
 * @param user_data Dados a serem passados para a função.
 * 
 * @return TRUE para que entidade seja removida da hash table.
 */
gboolean freeAlbumCountInTable(gpointer key, gpointer value, gpointer user_data);

/**
 * @brief Função que adiciona um artista à tabela de contador de músicas.
 * 
 * @param gestorArtist Apontador para a entidade do tipo gestor de artistas.
 * @param artist_id Id do artista a ser adicionado.
 */
void addMusicReps(GestorArtist* gestorArtist, long int artist_id);

/**
 * @brief Função que atualiza o número de músicas de um artista na tabela de contador de músicas.
 * 
 * @param gestorArtist Apontador para a entidade do tipo gestor de artistas.
 * @param artist_id Id do artista a ser atualizado.
 * @param reps Novo número de músicas do artista.
 */
void updateMusicReps(GestorArtist* gestorArtist, long int artist_id, int reps);

/**
 * @brief Função que retorna o número de músicas de um artista na tabela de contador de músicas.
 * 
 * @param gestorArtist Apontador para a entidade do tipo gestor de artistas.
 * @param artist_id Id do artista a ser retornado.
 * @return Número de músicas do artista.
 */
int getMusicReps(GestorArtist* gestorArtist, long int artist_id);

/**
 * @brief Função que remove um artista da tabela de contador de músicas.
 * 
 * @param gestorArtist Apontador para a entidade do tipo gestor de artistas.
 * @param artist_id Id do artista a ser removido.
 */
void removeMusicReps(GestorArtist* gestorArtist, long int artist_id);

/**
 * @brief Função que liberta a memória alocada para os artistas na tabela de contador de músicas.
 * 
 * @param key Chave da tabela.
 * @param value Valor da tabela.
 * @param user_data Dados a serem passados para a função.
 * 
 * @return TRUE para que entidade seja removida da hash table.
 */
gboolean freeMusicRepsInTable(gpointer key, gpointer value, gpointer user_data);

/**
 * @brief Função que verifica se um artista existe na tabela de artistas.
 * 
 * @param gestorArtist Apontador para a entidade do tipo gestor de artistas.
 * @param id Id do artista a ser verificado.
 * @return TRUE se o artista existe, FALSE caso contrário.
 */
bool containsArtistID(GestorArtist* gestorArtist, long int id);

/**
 * @brief Função que verifica se uma lista de ids de artistas é válida.
 * 
 * @param gestorArtist Apontador para a entidade do tipo gestor de artistas.
 * @param idList Lista de ids de artistas.
 * @param N Número de ids na lista.
 * @return TRUE se a lista de ids é válida, FALSE caso contrário.
 */
bool validateArtistIDs(GestorArtist* gestorArtist, long int *idList, int N);

/**
 * @brief Função que devolve uma discografia preenchida com os artistas da tabela.
 * 
 * @param gestorArtist Apontador para a entidade do tipo gestor de artistas.
 * @param disco Apontador para a discografia.
 * @return Apontador para a discografia preenchida.
 */
Discography* fillWithArtists(GestorArtist* gestorArtist, Discography* disco);

/**
 * @brief Função que devolve uma lista ligada de artistas.
 * 
 * @param gpointer artistId Id do artista.
 * @param gpointer artistData Dados do artista.
 * @param gpointer discoPtr Apontador para a discografia.
 */
void artistFromTableToLL(G_GNUC_UNUSED gpointer artistId, gpointer artistData, gpointer discoPtr);

/**
 * @brief Função que devolve uma lista com os coletivos que contêm um artista individual.
 * 
 * @param gestorArtist Apontador para a entidade do tipo gestor de artistas.
 * @param individual_artist_id Id do artista individual.
 * @return Lista com os coletivos que contêm o artista individual.
 */
GList* getCollectiveArtistsContaining(GestorArtist* gestorArtist, long int individual_artist_id);

#endif