#include "../../include/gestores/gestor_music.h"

struct gestor_music {
    GHashTable* table;
};

// função para criar uma tabela de músicas.
GestorMusic* createGestorMusic(){
    GestorMusic* gestorMusic = malloc(sizeof(GestorMusic));
    if (gestorMusic == NULL) {
        perror("Falha ao criar a struct GestorMusic.\n");
        free(gestorMusic);
        return NULL;
    }

    gestorMusic -> table = g_hash_table_new(g_int_hash, g_int_equal);
    if(gestorMusic -> table == NULL){
        perror("Falha ao criar a tabela de hashing de artistas.\n");
        free(gestorMusic);
        return NULL;
    }
    return gestorMusic;
}

// função que adiciona uma música á tabela de músicas.
void addMusic(GestorMusic* gestorMusic, Music* music){
    if(gestorMusic && gestorMusic -> table){
        g_hash_table_insert(gestorMusic -> table, getMusicID(music), music);
    }
}

// função que remove uma música da tabela de músicas.
void removeMusic(GestorMusic* gestorMusic, long int id){
    if(gestorMusic && gestorMusic -> table){
        g_hash_table_remove(gestorMusic -> table, &id);
    }
}

// função que encontra uma música pelo id na tabela.
Music* searchMusic(GestorMusic* gestorMusic, long int id){
    if(gestorMusic && gestorMusic -> table){
        return (Music*) g_hash_table_lookup(gestorMusic -> table, &id);
    }
    return NULL;
}

// função que aplica uma função callback em cada item da tabela de músicas.
void foreachMusic(GestorMusic* gestorMusic, GFunc func, gpointer user_data){
    if (gestorMusic && gestorMusic->table && func){
        g_hash_table_foreach(gestorMusic->table, func, user_data);
    }
}

// Função para liberar a memória da tabela de músicas.
void freeGestorMusic(GestorMusic* gestorMusic){
    if(gestorMusic){
        if(gestorMusic -> table){
            g_hash_table_foreach_remove(gestorMusic -> table, freeMusicInTable, NULL);
            g_hash_table_destroy(gestorMusic -> table);
        }
        free(gestorMusic);
    }
}

// Função principal para percorrer a hash table e atualizar as durações dos artistas
Discography* updateArtistsDurationFromMusic(GestorMusic* gestorMusic, Discography* disco){

    g_hash_table_foreach(gestorMusic -> table, artistDurationAdd, &disco);
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
    free(duration);
}

// Função que verifica se todos os ids das musicas pertencem à tabela
bool validateMusicId(GestorMusic* gestorMusic, long int* id, int N){
    for(int i=0;i<N;i++){
        if(!containsMusicID(gestorMusic, id[i])) return false;
    }
    return true;
}

// Função que verifica a existência de uma musica pelo seu id, na tabela de musicas
bool containsMusicID(GestorMusic* gestorMusic, long int id){
    return g_hash_table_contains(gestorMusic -> table, &id);
}