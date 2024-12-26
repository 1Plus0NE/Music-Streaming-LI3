#include "../../include/gestores/gestor_history.h"

// Estrutura do gestor de histórico.
struct gestor_history {
    GHashTable* table;
};

// Função para criar um gestor de histórico.
GestorHistory* createGestorHistory(){
    GestorHistory* gestorHistory = malloc(sizeof(GestorHistory));
    if(gestorHistory == NULL){
        perror("Falha ao criar a struct GestorHistory.\n");
        free(gestorHistory);
        return NULL;
    }

    gestorHistory -> table = g_hash_table_new(g_int_hash, g_int_equal);
    if(gestorHistory -> table == NULL){
        perror("Falha ao criar a tabela de hashing de histórico.\n");
        free(gestorHistory);
        return NULL;
    }
    return gestorHistory;
}

// Função que adiciona um histórico à tabela.
void addHistory(GestorHistory* gestorHistory, History* history){
    if(gestorHistory && gestorHistory -> table){
        long int* key = malloc(sizeof(long int));
        if(!key){
            perror("Erro ao alocar memória para a chave do histórico");
            return;
        }
        *key = getHistoryId(history);
        g_hash_table_insert(gestorHistory -> table, key, history);
    }
}

// Função que remove um histórico da tabela.
void removeHistory(GestorHistory* gestorHistory, long int id){
    if(gestorHistory && gestorHistory -> table){
        g_hash_table_remove(gestorHistory -> table, &id);
    }
}

// Função que encontra um histórico pelo id na tabela.
History* searchHistory(GestorHistory* gestorHistory, long int id){
    if(gestorHistory && gestorHistory -> table){
        return (History*) g_hash_table_lookup(gestorHistory -> table, &id);
    }
    return NULL;
}

// Função que aplica uma função callback em cada item da tabela de histórico.
void foreachHistory(GestorHistory* gestorHistory, GHFunc func, gpointer user_data){
    if(gestorHistory && gestorHistory -> table && func){
        g_hash_table_foreach(gestorHistory -> table, func, user_data);
    }
}

// Função que libera a memória alocada para a tabela de histórico.
void freeGestorHistory(GestorHistory* gestorHistory){
    if(gestorHistory){
        if(gestorHistory -> table){
            g_hash_table_foreach_remove(gestorHistory -> table, freeHistoryInTable, NULL);
            g_hash_table_destroy(gestorHistory -> table);
        }
        free(gestorHistory);
    }
}

// Função que verifica se a chave existe na tabela de histórico.
bool containsHistoryID(GestorHistory* gestorHistory, long int id){
    if(gestorHistory && gestorHistory -> table){
        return g_hash_table_contains(gestorHistory -> table, &id);
    }
    return false;
}

// Função que verifica se todos os IDs existem na tabela de histórico.
bool validateHistoryIDs(GestorHistory* gestorHistory, long int* idList, int N){
    if(gestorHistory && gestorHistory -> table){
        for(int i = 0; i < N; i++){
            if(!containsHistoryID(gestorHistory, idList[i])){
                return false;
            }
        }
        return true;
    }
    return false;
}