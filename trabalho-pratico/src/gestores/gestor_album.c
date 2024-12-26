#include "../../include/gestores/gestor_album.h"

// Estrutura do gestor de álbuns.
struct gestor_album {
    GHashTable* table;
};

// Função para criar um gestor de álbuns.
GestorAlbum* createGestorAlbum() {
    GestorAlbum* gestorAlbum = malloc(sizeof(GestorAlbum));
    if (gestorAlbum == NULL) {
        perror("Falha ao criar a struct GestorAlbum.\n");
        free(gestorAlbum);
        return NULL;
    }

    gestorAlbum->table = g_hash_table_new(g_int_hash, g_int_equal);
    if (gestorAlbum->table == NULL) {
        perror("Falha ao criar a tabela de hashing de álbuns.\n");
        free(gestorAlbum);
        return NULL;
    }
    return gestorAlbum;
}

// Função que adiciona um álbum à tabela.
void addAlbum(GestorAlbum* gestorAlbum, Album* album){
    if(gestorAlbum && gestorAlbum -> table){
        long int* key = malloc(sizeof(long int));
        if(!key){
            perror("Erro ao alocar memória para a chave do álbum");
            return;
        }
        *key = getAlbumId(album);
        g_hash_table_insert(gestorAlbum -> table, key, album);
    }
}

// Função que remove um álbum da tabela.
void removeAlbum(GestorAlbum* gestorAlbum, long int id) {
    if (gestorAlbum && gestorAlbum->table) {
        g_hash_table_remove(gestorAlbum->table, &id);
    }
}

// Função que encontra um álbum pelo id na tabela.
Album* searchAlbum(GestorAlbum* gestorAlbum, long int id) {
    if (gestorAlbum && gestorAlbum->table) {
        return (Album*) g_hash_table_lookup(gestorAlbum->table, &id);
    }
    return NULL;
}

// Função que aplica uma função callback em cada item da tabela de álbuns.
void foreachAlbum(GestorAlbum* gestorAlbum, GHFunc func, gpointer user_data) {
    if (gestorAlbum && gestorAlbum->table && func) {
        g_hash_table_foreach(gestorAlbum->table, func, user_data);
    }
}

// Função que libera a memória alocada para a tabela de álbuns.
void freeGestorAlbum(GestorAlbum* gestorAlbum) {
    if (gestorAlbum) {
        if (gestorAlbum->table) {
            g_hash_table_foreach_remove(gestorAlbum->table, freeAlbumInTable, NULL);
            g_hash_table_destroy(gestorAlbum->table);
        }
        free(gestorAlbum);
    }
}

// Função que verifica se a chave existe na tabela de álbuns.
bool containsAlbumID(GestorAlbum* gestorAlbum, long int id) {
    if (gestorAlbum && gestorAlbum->table) {
        return g_hash_table_contains(gestorAlbum->table, &id);
    }
    return false;
}

// Função que verifica se todos os IDs existem na tabela de álbuns.
bool validateAlbumIDs(GestorAlbum* gestorAlbum, long int* idList, int N) {
    if (gestorAlbum && gestorAlbum->table) {
        for (int i = 0; i < N; i++) {
            if (!containsAlbumID(gestorAlbum, idList[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}