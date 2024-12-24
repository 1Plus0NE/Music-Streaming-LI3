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

// Função que retorna o número de álbuns individuais de um artista.
int getNumAlbumsIndividual(GestorAlbum* gestorAlbum, long int artist_id){
    int num_albums_individual = 0;

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, gestorAlbum -> table);
    while (g_hash_table_iter_next(&iter, &key, &value)){
        Album* album = (Album*)value;
        int* artists_ids = getAlbumArtistIds(album);
        int num_artists = getAlbumNumArtists(album);
        if (num_artists == 1 && artists_ids[0] == artist_id) {
            num_albums_individual++;
        }
    }

    printf("Número de álbuns individuais: %d\n", num_albums_individual);
    return num_albums_individual;
}

// Função que retorna o número de álbuns de um artista.
Album* findAlbumByMusicId(GestorAlbum* gestorAlbum, int music_id) {
    // Validate parameters
    if (!gestorAlbum || !gestorAlbum->table) {
        printf("Erro: Gestor álbum ou tabela inválida!\n");
        return NULL;
    }

    GHashTableIter iter;
    gpointer key, value;
    
    printf("Procurando álbum v2...\n");
    printf("Table address: %p\n", (void*)gestorAlbum->table);
    printf("Table size: %u\n", g_hash_table_size(gestorAlbum->table));
    g_hash_table_iter_init(&iter, gestorAlbum->table);

    printf("Iterador inicializado.\n");

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        if (!value) continue;  // Skip if value is NULL
        
        printf("Iterando sobre a tabela de álbuns...\n");
        Album* album = (Album*)value;
        
        int* artists_ids = getAlbumArtistIds(album);
        int num_artists = getAlbumNumArtists(album);
        
        if (!artists_ids) {
            printf("Erro: Lista de artistas inválida!\n");
            continue;
        }
        
        printf("Número de artistas: %d\n", num_artists);
        printf("ID da música: %d\n", music_id);
        
        // Verifica se a música pertence ao álbum atual
        for (int i = 0; i < num_artists; i++) {
            if (artists_ids[i] == music_id) {
                return album;
            }
        }
    }
    
    return NULL;
}

// Função que determina se uma música pertence a um artista.
bool isMusicByArtist(long int music_id, long int artist_id, GestorAlbum* gestorAlbum){
    printf("Procurando álbum...\n");
    Album* album = findAlbumByMusicId(gestorAlbum, music_id);
    printf("Álbum encontrado.\n");
    if(!album) return false;

    int* artists_ids = getAlbumArtistIds(album);
    int num_artists = getAlbumNumArtists(album);
    for(int i = 0; i < num_artists; i++){
        printf("ID do artista: %d\n", artists_ids[i]);
        if(artists_ids[i] == artist_id){
            printf("Música pertence ao artista.\n");
            return true;
        }
    }
    return false;
}