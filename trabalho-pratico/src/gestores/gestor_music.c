#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "gestor_music.h"
#include "music.h"
#include <glib.h>

// função para criar uma tabela de músicas.
GHashTable* createMusicTable(){
    return g_hash_table_new(g_int_hash, g_int_equal);
}

// função que adiciona uma música á tabela de músicas.
void addMusic(GHashTable* table, Music* music){
    g_hash_table_insert(table, music -> id, music);
}

// função que remove uma música da tabela de músicas.
void removeMusic(GHashTable* table, int id){
    g_hash_table_remove(table, &id);
}

// função que encontra uma música pelo id na tabela.
Music* searchMusic(GHashTable* table, int id){
    return (Music*) g_hash_table_lookup(table, &id);
}

// Função para liberar a memória da tabela de músicas.
void freeMusicTable(GHashTable* table) {
    g_hash_table_destroy(table);
}