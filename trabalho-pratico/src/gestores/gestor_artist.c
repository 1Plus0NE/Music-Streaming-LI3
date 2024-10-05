#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "gestor_artist.h"
#include "artist.h"
#include <glib.h>

// função para criar uma tabela de artistas.
GHashTable* createArtistTable(){
    return g_hash_table_new(g_int_hash, g_int_equal);
}

// função que adiciona um artista á tabela de artistas.
void addArtist(GHashTable* table, Artist* artist){
    g_hash_table_insert(table, artist -> id, artist);
}

// função que remove um artista da tabela de artistas.
void removeArtist(GHashTable* table, int id){
    g_hash_table_remove(table, &id);
}

// função que encontra um artista pelo id na tabela.
Artist* searchArtist(GHashTable* table, int id){
    return (*Artist) g_hash_table_lookup(table, &id);
}

// função que libera a memória alocada para a tabela de artistas.
void freeArtistTable(GHashTable* table){
    g_hash_table_destroy(table);
}