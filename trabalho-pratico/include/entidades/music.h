/**
 * @file music.h
 * @brief Definição da estrutura de música e das funções que a manipulam.
 */
#ifndef MUSIC_H
#define MUSIC_H
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include "../utils.h"
#include "glib.h"

/**
 * @brief Estrutura que armazena a informação de uma música.
 * 
 */
typedef struct music Music;

/**
 * @brief Função que cria uma entidade do tipo música.
 * @details A função recebe o id da música, o título, o id do(s) artista(s), o número de artistas, o id do álbum, a duração, o género, o ano e a letra da música e cria uma entidade do tipo música.
 *
 * @param id Id da música.
 * @param title Título da música.
 * @param artist_id Id do(s) artista(s).
 * @param num_artists Número de artistas.
 * @param album_id Id do álbum.
 * @param duration Duração.
 * @param genre Género.
 * @param year Ano.
 * @param lyrics Letra.
 * @return Apontador para a entidade do tipo música.
 */
Music* createMusic(long int id, char* title, long int* artist_id, int num_artists, long int album_id, char* duration, char* genre, int year, char* lyrics);

/**
 * @brief Função que retorna o id de uma entidade do tipo música.
 * 
 * @param m Apontador para a entidade do tipo música.
 * @return Id da entidade do tipo música.
 */
long int* getMusicID(Music* m);

/**
 * @brief Função que retorna o título de uma entidade do tipo música.
 * 
 * @param m Apontador para a entidade do tipo música.
 * @return Título da entidade do tipo música.
 */
char* getMusicTitle(Music* m);

/**
 * @brief Função que retorna o id do(s) artista(s) de uma entidade do tipo música.
 * 
 * @param m Apontador para a entidade do tipo música.
 * @return Id do(s) artista(s) da entidade do tipo música.
 */
long int* getMusicArtistIDs(Music* m);

/**
 * @brief Função que retorna o número de artistas de uma entidade do tipo música.
 * 
 * @param m Apontador para a entidade do tipo música.
 * @return Número de artistas da entidade do tipo música.
 */
int getMusicNumArtists(Music* m);

/**
 * @brief Função que retorna o id do álbum de uma entidade do tipo música.
 * 
 * @param m Apontador para a entidade do tipo música.
 * @return Id do álbum da entidade do tipo música.
 */
long int getMusicAlbumId(Music* m);

/**
 * @brief Função que retorna a duração de uma entidade do tipo música.
 * 
 * @param m Apontador para a entidade do tipo música.
 * @return Duração da entidade do tipo música.
 */
char* getMusicDuration(Music* m);

/**
 * @brief Função que retorna o género de uma entidade do tipo música.
 * 
 * @param m Apontador para a entidade do tipo música.
 * @return Género da entidade do tipo música.
 */
char* getMusicGenre(Music* m);

/**
 * @brief Função que retorna o ano de uma entidade do tipo música.
 * 
 * @param m Apontador para a entidade do tipo música.
 * @return Ano da entidade do tipo música.
 */
int getMusicYear(Music* m);

/**
 * @brief Função que retorna a letra de uma entidade do tipo música.
 * 
 * @param m Apontador para a entidade do tipo música.
 * @return Letra da entidade do tipo música.
 */
char* getMusicLyrics(Music* m);

/**
 * @brief Função que modifica o id de uma entidade do tipo música.
 * 
 * @param m Apontador para a entidade do tipo música.
 * @param newID Novo id da entidade do tipo música.
 */
void setMusicID(Music* m, long int newID);

/**
 * @brief Função que modifica o título de uma entidade do tipo música.
 * 
 * @param m Apontador para a entidade do tipo música.
 * @param newTitle Novo título da entidade do tipo música.
 */
void setMusicTitle(Music* m, char* newTitle);

/**
 * @brief Função que modifica o id do(s) artista(s) de uma entidade do tipo música.
 * 
 * @param m Apontador para a entidade do tipo música.
 * @param newArtistID Novo id do(s) artista(s) da entidade do tipo música.
 * @param newNumArtists Novo número de artistas da entidade do tipo música.
 */
void setMusicArtistIDs(Music* m, long int* newArtistID, int newNumArtists);

/**
 * @brief Função que modifica o id do álbum de uma entidade do tipo música.
 * 
 * @param m Apontador para a entidade do tipo música.
 * @param newAlbumId Novo id do álbum da entidade do tipo música.
 */
void setMusicAlbumId(Music* m, long int newAlbumId);

/**
 * @brief Função que modifica a duração de uma entidade do tipo música.
 * 
 * @param m Apontador para a entidade do tipo música.
 * @param newDuration Nova duração da entidade do tipo música.
 */
void setMusicDuration(Music* m, char* newDuration);

/**
 * @brief Função que modifica o género de uma entidade do tipo música.
 * 
 * @param m Apontador para a entidade do tipo música.
 * @param newGenre Novo género da entidade do tipo música.
 */
void setMusicGenre(Music* m, char* newGenre);

/**
 * @brief Função que modifica o ano de uma entidade do tipo música.
 * 
 * @param m Apontador para a entidade do tipo música.
 * @param newYear Novo ano da entidade do tipo música.
 */
void setMusicYear(Music* m, int newYear);

/**
 * @brief Função que modifica a letra de uma entidade do tipo música.
 * 
 * @param m Apontador para a entidade do tipo música.
 * @param newLyrics Nova letra da entidade do tipo música.
 */
void setMusicLyrics(Music* m, char* newLyrics);

/**
 * @brief Função que liberta a memória ocupada pela entidade do tipo música.
 * 
 * @param music Apontador para a entidade do tipo música.
 */
void freeMusic(Music* music);

/**
 * @brief Função que insere uma entidade do tipo música numa hashtable.
 * @details A função recebe um apontador para a hashtable e um apontador para a entidade do tipo música e insere a entidade do tipo música na hashtable.
 *
 * @param key Chave da entidade do tipo música.
 * @param value Apontador para a entidade do tipo música.
 * @param user_data Apontador para a hashtable.
 * @return TRUE se a entidade do tipo música foi inserida na hashtable e FALSE caso contrário.
 */
gboolean freeMusicInTable(gpointer key, gpointer value, gpointer user_data);

#endif