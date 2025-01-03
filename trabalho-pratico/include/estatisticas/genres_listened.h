/**
 * @file genres_listened.h
 * @brief Definição da estrutura de géneros ouvidos e das funções que a manipulam.
 */
#ifndef GENRES_LISTENED_H
#define GENRES_LISTENED_H
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>

/**
 * @brief Estrutura que armazena a informação dos géneros ouvidos.
 * 
 */
typedef struct genres_listened GenresListened;

/**
 * @brief Função que cria uma entidade do tipo géneros ouvidos.
 * @details A função recebe o username, um array de géneros, um array de músicas ouvidas e o tamanho dos arrays e cria uma entidade do tipo géneros ouvidos.
 *
 * @param username Username.
 * @param genres Array de géneros.
 * @param listened Array de músicas ouvidas.
 * @param size Tamanho dos arrays.
 * @return Apontador para a entidade do tipo géneros ouvidos.
 */
GenresListened* createGenresListened(char* username, char** genres, int* listened, int size);

/**
 * @brief Função que retorna o username de um utilizador.
 * @details A função recebe um apontador para a entidade do tipo géneros ouvidos e retorna o username do utilizador.
 *
 * @param genresListened Apontador para a entidade do tipo géneros ouvidos.
 */
char* getGenresListenedUsername(const GenresListened* genresListened);

/**
 * @brief Função que retorna o array de géneros ouvidos por um utilizador.
 * @details A função recebe um apontador para a entidade do tipo géneros ouvidos e retorna o array de géneros ouvidos pelo utilizador.
 *
 * @param genresListened Apontador para a entidade do tipo géneros ouvidos.
 */
char** getGenresListenedArrayGenres(GenresListened* genresListened);

/**
 * @brief Função que retorna o array de músicas ouvidas por um utilizador.
 * @details A função recebe um apontador para a entidade do tipo géneros ouvidos e retorna o array de músicas ouvidas pelo utilizador.
 *
 * @param genresListened Apontador para a entidade do tipo géneros ouvidos.
 */
int* getGenresListenedArrayListened(GenresListened* genresListened);

/**
 * @brief Função que retorna o tamanho dos arrays de géneros e músicas ouvidas por um utilizador.
 * @details A função recebe um apontador para a entidade do tipo géneros ouvidos e retorna o tamanho dos arrays de géneros e músicas ouvidas pelo utilizador.
 *
 * @param genresListened Apontador para a entidade do tipo géneros ouvidos.
 */
int getGenresListenedArraysSize(const GenresListened* genresListened);

/**
 * @brief Função que retorna a similaridade entre dois utilizadores.
 * @details A função recebe um apontador para a entidade do tipo géneros ouvidos e retorna a similaridade entre dois utilizadores.
 *
 * @param genresListened Apontador para a entidade do tipo géneros ouvidos.
 */
int getGenresListenedSimilarity(const GenresListened* genresListened);

/**
 * @brief Função que altera o array de géneros ouvidos por um utilizador.
 * @details A função recebe um apontador para a entidade do tipo géneros ouvidos e um array de géneros e altera o array de géneros ouvidos pelo utilizador.
 *
 * @param genresListened Apontador para a entidade do tipo géneros ouvidos.
 * @param newGenres Array de géneros.
 * @param newSize Tamanho do array de géneros.
 */
void setGenresListenedArrayGenres(GenresListened* genresListened, char** newGenres, int newSize);

/**
 * @brief Função que altera o array de músicas ouvidas por um utilizador.
 * @details A função recebe um apontador para a entidade do tipo géneros ouvidos e um array de músicas ouvidas e altera o array de músicas ouvidas pelo utilizador.
 *
 * @param genresListened Apontador para a entidade do tipo géneros ouvidos.
 * @param newListened Array de músicas ouvidas.
 * @param newSize Tamanho do array de músicas ouvidas.
 */
void setGenresListenedArrayListened(GenresListened* genresListened, int* newListened, int newSize);

/**
 * @brief Função que altera a similaridade entre dois utilizadores.
 * @details A função recebe um apontador para a entidade do tipo géneros ouvidos e a similaridade entre dois utilizadores e altera a similaridade entre os dois utilizadores.
 *
 * @param genresListened Apontador para a entidade do tipo géneros ouvidos.
 * @param newSimilarityScore Similaridade entre dois utilizadores.
 */
void setSimilarityScore(GenresListened* genresListened, int newSimilarityScore);

/**
 * @brief Função que liberta a memória alocada para a entidade do tipo géneros ouvidos.
 * @details A função recebe um apontador para a entidade do tipo géneros ouvidos e liberta a memória alocada para a entidade.
 *
 * @param genresListened Apontador para a entidade do tipo géneros ouvidos.
 */
void freeGenresListened(GenresListened* genresListened);

/** 
 * @brief Função que liberta a memória alocada para a entidade do tipo géneros ouvidos 
 * 
 * 
 * 
*/
void freeGenresListenedInTable(gpointer data);

#endif