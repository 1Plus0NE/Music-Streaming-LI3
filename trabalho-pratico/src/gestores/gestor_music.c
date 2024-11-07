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
    g_hash_table_foreach_remove(table,freeMusicInTable,NULL);
    g_hash_table_destroy(table);
}

// Função principal para percorrer a hash table e atualizar as durações dos artistas
Discography* updateArtistsDurationFromMusic(GHashTable* musicTable, Discography* disco){

    g_hash_table_foreach(musicTable, artistDurationAdd, &disco);
    return disco;
}

// Função para processar cada música e atualizar a duração nos artistas correspondentes
void artistDurationAdd(G_GNUC_UNUSED gpointer musicId, gpointer musicData, gpointer discoPtr){
   
    //Music* music = (Music*)musicData;
    Discography* disco = *((Discography**)discoPtr);
    int numArtists = getMusicNumArtists(musicData);
    char* duration = getMusicDuration(musicData);
    long int* musicArtistsId = getMusicArtistIDs(musicData);
    
    for(int i=0; i<numArtists; i++){
        durationAdd(disco, duration, musicArtistsId[i]);
    }
}