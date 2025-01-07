#include "../../include/gestores/gestor_music.h"

//estrutura do gestor de músicas.
struct gestor_music {
    GHashTable* table;
    Wrapped* wrap;
};

// função para criar uma tabela de músicas.
GestorMusic* createGestorMusic(){
    GestorMusic* gestorMusic = malloc(sizeof(GestorMusic));
    if (gestorMusic == NULL) {
        perror("Falha ao criar a struct GestorMusic.\n");
        free(gestorMusic);
        return NULL;
    }

    gestorMusic -> table = g_hash_table_new_full(g_int_hash, g_int_equal, free, freeMusicInTable);
    if(gestorMusic -> table == NULL){
        perror("Falha ao criar a tabela de hashing de artistas.\n");
        free(gestorMusic);
        return NULL;
    }
    gestorMusic->wrap = NULL;
    return gestorMusic;
}

GestorMusic* createGestorMusicWrapped(GestorMusic* gestorMusic){
    if(gestorMusic){
        gestorMusic -> wrap = wrappedInit();
        return gestorMusic;
    }
    return NULL;
}

// função que adiciona uma música á tabela de músicas.
void addMusic(GestorMusic* gestorMusic, Music* music){
    if(gestorMusic && gestorMusic -> table){
        long int* key = malloc(sizeof(long int));
        if(!key){
            perror("Erro ao alocar memória para a chave da música.\n");
            return;
        }
        *key = getMusicID(music);
        g_hash_table_insert(gestorMusic -> table, key, music);
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
void foreachMusic(GestorMusic* gestorMusic, GHFunc func, gpointer user_data){
    if (gestorMusic && gestorMusic->table && func){
        g_hash_table_foreach(gestorMusic->table, func, user_data);
    }
}

// Função para liberar a memória da tabela de músicas.
void freeGestorMusic(GestorMusic* gestorMusic){
    if(gestorMusic){
        if(gestorMusic -> table){
            g_hash_table_destroy(gestorMusic -> table);
        }
        if(gestorMusic -> wrap){
            freeWrapped(gestorMusic -> wrap);
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
   
    Discography* disco = *((Discography**)discoPtr);
    int numArtists = getMusicNumArtists(musicData);
    char* duration = getMusicDuration(musicData);
    long int* musicArtistsId = getMusicArtistIDs(musicData);
    
    for(int i=0; i<numArtists; i++){
        durationAdd(disco, duration, musicArtistsId[i]);
    }
    free(duration);
}

// Função responsável por popular o array de generos e contar o numero total de likes no array de likes
void countUserLikedMusics(GestorMusic* gestorMusic, char*** genres, long int** genre_likes, int* genre_count, long int* likedMusics, int numLikedMusics){
    Music* music = NULL;
    char* genre;
    int index;

    for(int i=0;i<numLikedMusics;i++){
        music = searchMusic(gestorMusic, likedMusics[i]);

        if(music != NULL){ // em principio nunca falha porque as liked musics do user ja sao verificadas no parsing 
            genre = getMusicGenre(music);
            index = getGenreIndex(genre, *genres, *genre_count);

            if(index == -1){
                *genres = realloc(*genres, (*genre_count + 1) * sizeof(char*));
                *genre_likes = realloc(*genre_likes, (*genre_count + 1) * sizeof(long int));

                (*genres)[*genre_count] = strdup(genre);
                (*genre_likes)[*genre_count] = 1;
                (*genre_count)++;
            }
            else (*genre_likes)[index]++;  
            free(genre);
        }
    }
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

Wrapped* getMusicWrap(GestorMusic* gestorMusic){
    if(!gestorMusic->wrap) return NULL;
    return gestorMusic->wrap;
}

void setMusicWrap(GestorMusic* gestorMusic, Wrapped* wrap){
    if(gestorMusic && wrap){
        gestorMusic->wrap = wrap;
    }
}

void freeMusicWrap(GestorMusic* gestorMusic){
    if(gestorMusic && gestorMusic->wrap){
        freeWrapped(gestorMusic->wrap);
        gestorMusic->wrap = NULL;
    }
}


// Função que percorre a Hash de History e preenche o wrap do user no ano especificado
void yearResumed(G_GNUC_UNUSED gpointer key, gpointer value, gpointer q6data){

    History* history = (History*)value; // Possível erro
    GestorMusic** query6Data = (GestorMusic**)q6data;

    Wrapped* wrap = (Wrapped*) getMusicWrap(*query6Data); 
    GestorMusic* table = (GestorMusic*) (*query6Data); 

    // Obtenção dos userId para comparação wrap
    long int userId = getHistoryUserId(history);
    if(userId==-1){
        perror("Erro getHistoryUserId, função 'yearResumed'\n");
    }
    
    long int userIdWrap = getWrapUserId(wrap); 
    if(userIdWrap==0){
        perror("Erro getWrapUserId, função 'yearResumed'\n");
    }
    // Ano do wrap/query para comparação ...
    char* anoWrap = getWrapAno(wrap);
    
    
    // Obtenção e formatação propriamente ditas
    char* timeStampPtr = getHistoryTimestamp(history); // LEAK 
    char* anoTimeStamp =(char*)malloc(4*sizeof(char));
    strncpy(anoTimeStamp, timeStampPtr, 4);
    anoTimeStamp[4] = '\0';

    //Verificar se o registo do histórico é relevante
    if(userId==userIdWrap && strcmp(anoTimeStamp,anoWrap)==0){
        long int musicId = getHistoryMusicId(history);
        Music* music = searchMusic(table, musicId);
        long int albumId = getMusicAlbumId(music);
        int numArtists = getMusicNumArtists(music);
        long int* artist_id = getMusicArtistIDs(music);
        char* genre = getMusicGenre(music);

        // Extrair e calcular a duração a incrementar (segundos)
        char* duration = getHistoryDuration(history);
        int h,m,s;
        if(sscanf(duration, "%d:%d:%d", &h, &m, &s)!=3){
            perror("Erro sscanf, função 'yearResumed'\n");
            exit(EXIT_FAILURE);
        }
        int segundos = h*3600 + m*60 + s;

        //Preennchimento do Wrapped e consequentemente da Query6data
        setWrapAlbum(wrap, albumId, segundos);
        setWrapHoras(wrap, timeStampPtr, segundos);
        setWrapGeneros(wrap, genre, segundos);
        setWrapDias(wrap, timeStampPtr, segundos);
        setWrapArtistTime(wrap, artist_id, numArtists, musicId, segundos);

        free(duration);
        free(genre);
        free(artist_id);
    }
    //free(timeStampPtr); // double free, usar apenas getHistoryTimestamp?
    free(anoTimeStamp);
    free(anoWrap);
}

