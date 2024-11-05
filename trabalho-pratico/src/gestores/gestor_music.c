#include "../../include/gestores/gestor_music.h"

// função para criar uma tabela de músicas.
GHashTable* createMusicTable(){
    GHashTable* table = g_hash_table_new(g_int_hash, g_int_equal);
    if (table == NULL) {
        perror("Falha ao criar a tabela de hashing de musicas.\n");
        return NULL;
    }

    return table;
}

// função que adiciona uma música á tabela de músicas.
void addMusic(GHashTable* table, Music* music){
    g_hash_table_insert(table, getMusicID(music), music);
}

// função que remove uma música da tabela de músicas.
void removeMusic(GHashTable* table, long int id){
    g_hash_table_remove(table, &id);
}

// função que encontra uma música pelo id na tabela.
Music* searchMusic(GHashTable* table, long int id){
    return (Music*) g_hash_table_lookup(table, &id);
}

// Função para liberar a memória da tabela de músicas.
void freeMusicTable(GHashTable* table){
    g_hash_table_foreach(table,freeMusicInTable,NULL);
    g_hash_table_destroy(table);
}