/**
 * @file gestor_album.h
 * @brief Definição da estrutura do gestor de álbuns e das funções que a manipulam.
 */
#ifndef GESTOR_ALBUM_H
#define GESTOR_ALBUM_H
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../entidades/album.h"
#include <glib.h>

/**
 * @brief Estrutura que armazena a informação dos álbuns.
 * 
 */
typedef struct gestor_album GestorAlbum;

typedef void (*GHFunc)(void *key, void *value, void *user_data);

/**
 * @brief Função que cria uma entidade do tipo gestor de álbuns.
 * @details A função aloca memória para a estrutura do gestor de álbuns e inicializa a tabela de álbuns.
 * 
 * @return Apontador para a entidade do tipo gestor de álbuns.
 */
GestorAlbum* createGestorAlbum();

/**
 * @brief Função que retorna a tabela de álbuns.
 * 
 * @param gestorAlbum Apontador para a entidade do tipo gestor de álbuns.
 * @param album Album a ser adicionado.
 */
void addAlbum(GestorAlbum* gestorAlbum, Album* album);

/**
 * @brief Função que remove um álbum da tabela.
 * @details A função recebe o id de um álbum e remove-o da tabela de álbuns.
 * 
 * @param gestorAlbum Apontador para a entidade do tipo gestor de álbuns.
 * @param id Id do álbum a ser removido.
 */
void removeAlbum(GestorAlbum* gestorAlbum, long int id);

/**
 * @brief Função que retorna um álbum da tabela.
 * @details A função recebe o id de um álbum e retorna-o da tabela de álbuns.
 * 
 * @param gestorAlbum Apontador para a entidade do tipo gestor de álbuns.
 * @param id Id do álbum a ser retornado.
 * @return Apontador para o álbum.
 */
Album* searchAlbum(GestorAlbum* gestorAlbum, long int id);

/**
 * @brief Função que faz um ciclo sobre a tabela de álbuns.
 * 
 * @param gestorAlbum Apontador para a entidade do tipo gestor de álbuns.
 * @param func Função a ser aplicada.
 * @param user_data Dados a serem passados para a função.
 */
void foreachAlbum(GestorAlbum* gestorAlbum, GHFunc func, gpointer user_data);

/**
 * @brief Função que liberta a memória alocada para o gestor de álbuns.
 * @details Função que liberta a memória alocada para o gestor de álbuns.
 * 
 * @param gestorAlbum Ponteiro para o gestor de álbuns a ser libertado.
 */
void freeGestorAlbum(GestorAlbum* gestorAlbum);

/**
 * @brief Função que verifica se um álbum existe na tabela de álbuns.
 * @details Função que verifica se um álbum existe na tabela de álbuns.
 * 
 * @param gestorAlbum Ponteiro para o gestor de álbuns.
 * @param id Id do álbum a ser verificado.
 * 
 * @return Retorna verdadeiro se o álbum existir e falso caso contrário.
 */
bool containsAlbumID(GestorAlbum* gestorAlbum, long int id);

/**
 * @brief Função que verifica se uma lista de álbuns existe na tabela de álbuns.
 * @details Função que verifica se uma lista de álbuns existe na tabela de álbuns.
 * 
 * @param gestorAlbum Ponteiro para o gestor de álbuns.
 * @param idList Lista de IDs dos álbuns a serem verificados.
 * @param N Número de álbuns a serem verificados.
 * 
 * @return Retorna verdadeiro se todos os álbuns existirem e falso caso contrário.
 */
bool validateAlbumIDs(GestorAlbum* gestorAlbum, long int *idList, int N);

#endif