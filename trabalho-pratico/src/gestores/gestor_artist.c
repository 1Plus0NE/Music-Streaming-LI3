#include "../../include/gestores/gestor_artist.h"

// função para criar uma tabela de artistas.
GHashTable* createArtistTable(){
    GHashTable* table = g_hash_table_new(g_int_hash, g_int_equal);
    if (table == NULL) {
        perror("Falha ao criar a tabela de hashing de artistas.\n");
        return NULL;
    }
    return table;
}

// função que adiciona um artista á tabela de artistas.
void addArtist(GHashTable* table, Artist* artist){
    g_hash_table_insert(table, getArtistId(artist), artist);
}

// função que remove um artista da tabela de artistas.
void removeArtist(GHashTable* table, long int id){
    g_hash_table_remove(table, &id);
}

// função que encontra um artista pelo id na tabela.
Artist* searchArtist(GHashTable* table, long int id){
    return (Artist*) g_hash_table_lookup(table, &id);
}

// função que libera a memória alocada para a tabela de artistas.
void freeArtistTable(GHashTable* table){
    g_hash_table_foreach(table,freeArtistInTable,NULL);
    g_hash_table_destroy(table);
}

// Função que verifica se a chave existe na tabela de artistas.
bool containsArtistID(GHashTable* table, long int id){
    return g_hash_table_contains(table, &id);
}

// Função que verifica se todos a lista de ids existe na tabela de artistas.
bool validateArtistIDs(GHashTable *table, long int *idList, int N){
    for (int i=0;i<N;i++){
        if (!containsArtistID(table, idList[i])){
            return false; 
        }
    }
    return true; 
}