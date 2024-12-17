#include "../../include/entidades/album.h"

struct album{
    long int id;
    char* title;
    long int* artist_ids;
    int num_artists;
    int year;
    char** producers;
    int num_producers;
};

// função para criar uma estrutura da entidade álbum parametrizada.
Album* createAlbum(long int id, char* title, long int* artist_ids, int num_artists,  int year, char** producers, int num_producers){
    Album* album = (Album*)malloc(sizeof(Album));
    if (!album) {
        perror("Erro ao alocar memória para o álbum.\n");
        exit(EXIT_FAILURE);
    }

    album->id = id;

    album->title = malloc(strlen(title) + 1);
    if(!album->title){
        perror("Erro ao alocar memória para o título do álbum.\n");
        free(album);
        exit(EXIT_FAILURE);
    }
    strcpy(album->title, title);

    album->artist_ids = malloc(num_artists * sizeof(long int));
    if(!album->artist_ids){
        perror("Erro ao alocar memória para os IDs dos artistas.\n");
        free(album->title);
        free(album);
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < num_artists; i++){
        album->artist_ids[i] = artist_ids[i];
    }
    album->num_artists = num_artists;

    album->year = year;

    album->producers = malloc(num_producers * sizeof(char*));
    if(!album->producers){
        perror("Erro ao alocar memória para os produtores do álbum.\n");
        free(album->artist_ids);
        free(album->title);
        free(album);
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < num_producers; i++){
        album->producers[i] = malloc(strlen(producers[i]) + 1);
        if(!album->producers[i]){
            perror("Erro ao alocar memória para o nome de um produtor.\n");
            for(int j = 0; j < i; j++){
                free(album->producers[j]);
            }
            free(album->producers);
            free(album->artist_ids);
            free(album->title);
            free(album);
            exit(EXIT_FAILURE);
        }
        strcpy(album->producers[i], producers[i]);
    }
    album->num_producers = num_producers;

    return album;
}

// Função para liberar a memória de uma entidade do tipo álbum.
void freeAlbum(Album* album) {
    if(!album) return;

    for(int i = 0; i < album->num_producers; i++){
        free(album->producers[i]);
    }
    free(album->producers);
    free(album->artist_ids);
    free(album->title);
    free(album);
}

// Função para liberar a memória de um álbum em uma hash table.
gboolean freeAlbumInTable(gpointer key, gpointer value, gpointer user_data){
    (void)key;
    (void)user_data;
    Album* album = (Album*)value;

    for(int i = 0; i < album->num_producers; i++){
        free(album->producers[i]);
    }
    free(album->producers);
    free(album->artist_ids);
    free(album->title);
    free(album);

    return TRUE;
}

// getters e setters de álbum.
long int getAlbumId(Album* album){
    return album ? album->id : -1;
}

char* getAlbumTitle(Album* album){
    return album->title ? strdup(album->title) : NULL;
}

long int* getAlbumArtistIds(Album* album){
    if(!album || album->num_artists == 0) return NULL;
    long int* copy = malloc(album->num_artists * sizeof(long int));
    memcpy(copy, album->artist_ids, album->num_artists * sizeof(long int));
    return copy;
}

int getAlbumNumArtists(Album* album){
    return album ? album->num_artists : 0;
}

int getAlbumYear(Album* album){
    return album ? album->year : 0;
}

char** getAlbumProducers(Album* album){
    if(!album || album->num_producers == 0) return NULL;
    char** copy = malloc(album->num_producers * sizeof(char*));
    for(int i = 0; i < album->num_producers; i++){
        copy[i] = strdup(album->producers[i]);
    }
    return copy;
}

int getAlbumNumProducers(Album* album){
    return album ? album->num_producers : 0;
}

void setAlbumId(Album* album, long int id){
    if(album) album->id = id;
}

void setAlbumTitle(Album* album, char* title){
    if(album->title) free(album->title);
    album->title = strdup(title);
}

void setAlbumArtistIds(Album* album, long int* artist_ids, int num_artists){
    if(album->artist_ids) free(album->artist_ids);
    album->artist_ids = malloc(num_artists * sizeof(long int));
    memcpy(album->artist_ids, artist_ids, num_artists * sizeof(long int));
    album->num_artists = num_artists;
}

void setAlbumYear(Album* album, int year){
    if(album) album->year = year;
}

void setAlbumProducers(Album* album, char** producers, int num_producers){
    if(album->producers){
        for(int i = 0; i < album->num_producers; i++){
            free(album->producers[i]);
        }
        free(album->producers);
    }
    album->producers = malloc(num_producers * sizeof(char*));
    for(int i = 0; i < num_producers; i++){
        album->producers[i] = strdup(producers[i]);
    }
    album->num_producers = num_producers;
}