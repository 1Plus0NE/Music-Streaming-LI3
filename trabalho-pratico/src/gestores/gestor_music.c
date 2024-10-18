#include "gestor_music.h"

// função para criar uma tabela de músicas.
void createMusicTable(){
    return g_hash_table_new(g_int_hash, g_int_equal);
}

// função que adiciona uma música á tabela de músicas.
void addMusic(GHashTable* table, Music* music){
    g_hash_table_insert(table, getMusicID(music), music);
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

// função que verifica se as musicas que o utilizador tem like efetivamente existem.
/* int verifyLikedMusics(char* liked_musics_str, MusicTable* music_table){
    char* liked_musics = strdup(liked_musics_str);
    char* music_id_str;
    
    int liked_musics_id[MAX_MUSICS];
    int count = 0;

    while ((music_id_str = strsep(&liked_musics, ",")) != NULL) {
        int music_id = atoi(music_id_str);
        liked_musics_id[count++] = music_id;

        if (!searchMusic(music_table, music_id)) {
            free(liked_musics);
            return 1;
        }
    }

    free(liked_musics);
    return 0;
} */