/**
 * @file gestor_music.h
 * @brief Definição da estrutura do gestor de músicas e das funções que a manipulam.
 */
#ifndef GESTOR_MUSIC_H
#define GESTOR_MUSIC_H
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "../entidades/music.h"
#include "../entidades/discography.h"
#include "../entidades/wrapped.h"
#include <glib.h>
#include <stdbool.h>
#define MAX_GENRES 10

/**
 * @brief Estrutura que armazena a informação das músicas.
 * 
 */
typedef struct gestor_music GestorMusic;

typedef void (*GHFunc)(void *key, void *value, void *user_data);

/**
 * @brief Função que cria uma entidade do tipo gestor de músicas.
 * @details A função aloca memória para a estrutura do gestor de músicas e inicializa a tabela de músicas.
 * 
 * @return Apontador para a entidade do tipo gestor de músicas.
 */
GestorMusic* createGestorMusic();
GestorMusic* createGestorMusicWrapped(GestorMusic* gestorMusic);

/**
 * @brief Função que adiciona uma música à tabela.
 * 
 * @param gestorMusic Apontador para a entidade do tipo gestor de músicas.
 * @param music Música a ser adicionada.
 */
void addMusic(GestorMusic* gestorMusic, Music* music);

/**
 * @brief Função que remove uma música da tabela.
 * 
 * @param gestorMusic Apontador para a entidade do tipo gestor de músicas.
 * @param id Id da música a ser removida.
 */
void removeMusic(GestorMusic* gestorMusic, long int id);

/**
 * @brief Função que procura uma música na tabela.
 * 
 * @param gestorMusic Apontador para a entidade do tipo gestor de músicas.
 * @param id Id da música a ser procurada.
 * @return Apontador para a música encontrada.
 */
Music* searchMusic(GestorMusic* gestorMusic, long int id);

/**
 * @brief Função que faz um ciclo sobre todas as músicas da tabela.
 * 
 * @param gestorMusic Apontador para a entidade do tipo gestor de músicas.
 * @param func Função a ser aplicada a cada música.
 * @param user_data Dados a serem passados para a função.
 */
void foreachMusic(GestorMusic* gestorMusic, GHFunc func, gpointer user_data);

/**
 * @brief Função que liberta a memória alocada para a entidade do tipo gestor de músicas.
 * 
 * @param gestorMusic Apontador para a entidade do tipo gestor de músicas.
 */
void freeGestorMusic(GestorMusic* gestorMusic);

/**
 * @brief Função que atualiza a duração dos artistas de uma discografia.
 * 
 * @param gestorMusic Apontador para a entidade do tipo gestor de músicas.
 * @param disco Apontador para a discografia.
 */
Discography* updateArtistsDurationFromMusic(GestorMusic* gestorMusic, Discography* disco);

/**
 * @brief Função que adiciona a duração dos artistas a uma discografia.
 * 
 * @param musicId Id da música.
 * @param musicData Dados da música.
 * @param discoPtr Apontador para a discografia.
 */
void artistDurationAdd(G_GNUC_UNUSED gpointer musicId, gpointer musicData, gpointer discoPtr);

/**
 * @brief Função que conta o número de músicas gostadas por género.
 * 
 * @param gestorMusic Apontador para a entidade do tipo gestor de músicas.
 * @param genres Géneros das músicas.
 * @param genre_likes Número de gostos por género.
 * @param genre_count Número de músicas por género.
 * @param likedMusics Músicas gostadas.
 * @param numLikedMusics Número de músicas gostadas.
 */
void countUserLikedMusics(GestorMusic* gestorMusic, char*** genres, long int** genre_likes, int* genre_count, long int* likedMusics, int numLikedMusics);

/**
 * @brief Função que valida o id de uma música.
 * 
 * @param gestorMusic Apontador para a entidade do tipo gestor de músicas.
 * @param id Id da música.
 * @param N Número de músicas.
 * @return true Se o id for válido.
 */
bool validateMusicId(GestorMusic* gestorMusic, long int* id, int N);

/**
 * @brief Função que verifica se uma música existe.
 * 
 * @param gestorMusic Apontador para a entidade do tipo gestor de músicas.
 * @param id Id da música.
 * @return true Se a música existir.
 */
bool containsMusicID(GestorMusic* gestorMusic, long int id);
Wrapped* getMusicWrap(GestorMusic* gestorMusic);
GHashTable* getMusicTable(GestorMusic* gestorMusic);
void yearResumed(G_GNUC_UNUSED gpointer key, gpointer value, gpointer q6data);
void setMusicWrap(GestorMusic* gestorMusic, Wrapped* wrap);
void freeMusicWrap(GestorMusic* gestorMusic);

#endif