#ifndef GESTOR_HISTORY_H
#define GESTOR_HISTORY_H
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../entidades/history.h"
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

// função que libera a memória alocada para a tabela de históricos.
void freeGestorHistory(GestorHistory* gestorHistory);

// Função que verifica se a chave existe na tabela de históricos.
bool containsHistoryID(GestorHistory* gestorHistory, long int id);

// Função que verifica se todos a lista de ids existe na tabela de históricos.
bool validateHistoryIDs(GestorHistory* gestorHistory, long int *idList, int N);

#endif