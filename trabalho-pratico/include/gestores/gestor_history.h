#ifndef GESTOR_HISTORY_H
#define GESTOR_HISTORY_H
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../entidades/history.h"
#include "../estatisticas/genres_listened.h"
#include <glib.h>

//estrutura do gestor de históricos.
typedef struct gestor_history GestorHistory;

typedef void (*GHFunc)(void *key, void *value, void *user_data);

typedef bool (*IsMusicByArtistFunc)(long int music_id, long int artist_id);

// função para criar uma tabela de históricos.
GestorHistory* createGestorHistory();

// função que adiciona um histórico á tabela de históricos.
void addHistory(GestorHistory* gestorHistory, History* history);

// função que remove um histórico da tabela de históricos.
void removeHistory(GestorHistory* gestorHistory, long int id);

// função que encontra um histórico pelo id na tabela.
History* searchHistory(GestorHistory* gestorHistory, long int id);

// função que aplica uma função callback em cada item da tabela de históricos.
void foreachHistory(GestorHistory* gestorHistory, GHFunc func, gpointer user_data);

// Função que verifica se a chave existe na tabela de históricos.
bool containsHistoryID(GestorHistory* gestorHistory, long int id);

// Função que verifica se todos a lista de ids existe na tabela de históricos.
bool validateHistoryIDs(GestorHistory* gestorHistory, long int *idList, int N);

// Função que produra um GenresListened na tabela de GenresListened
GenresListened* searchGenresListened(GestorHistory* gestorHistory, char* username);

// Função que adiciona/atualiza uma estrutura GenresListened à tabela 
void addGenresListened(GestorHistory* gestorHistory, char* username, char* genre);

// Função que retorna o array que contem todos os elementos da estrutura userLikes
GPtrArray* getGenresListenedArray(GestorHistory* gestorHistory);

// Função que retorna um elemento do array que armazena a estrutura de userLikes
GenresListened* getGenresListenedFromArray(GestorHistory* gestorHistory, int index);

// Função que dá store de utilizadores semelhantes temporariamente
void addSimilarUsers(GestorHistory* gestorHistory, GenresListened* targetUser);

// Função que retorna o array que contem todos os elementos da estrutura GenresListened filtrados
GPtrArray* getSimilarUsersArray(GestorHistory* gestorHistory);

// Função que retorna um elemento filtrado do array que armazena a estrutura de GenresListened
GenresListened* getSimilarUsersFromArray(GestorHistory* gestorHistory, int index);


int compareUsersBySizeAndSimilarity(gconstpointer a, gconstpointer b);

void sortSimilarUsers(GestorHistory* gestorHistory);


// Função limpa a memoria alocada de um GPtrArray para utilizadores semelhantes
void freeSimilarUsersArray(GestorHistory* gestorHistory);

// função que libera a memória alocada para a tabela de históricos.
void freeGestorHistory(GestorHistory* gestorHistory);

#endif