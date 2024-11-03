#include "../../include/entidades/music.h"

struct music {
    long int id;
    char* title;
    long int* artist_id;
    int num_artists;
    char* duration;
    char* genre;
    int year;
    char* lyrics;
};

// Função para criar uma estrutura da entidade música parametrizada.
Music* createMusic(long int id, char* title, long int* artist_id, int num_artists, char* duration, char* genre, int year, char* lyrics){
    Music* music = (Music*)malloc(sizeof(Music));
    if(!music){
        perror("erro ao alocar memória para a música.\n");
        exit(EXIT_FAILURE);
    }

    music -> id = id;

    music -> title = malloc(strlen(title) + 1);
    if(!music -> title){
        perror("erro ao alocar memória para o título.\n");
        free(music);
        exit(EXIT_FAILURE);
    }
    strcpy(music -> title, title);

    music -> artist_id = malloc(num_artists * sizeof(long int));
    if(!music -> artist_id){
        perror("erro ao alocar memória para a lista de artistas.\n");
        free(music -> title);
        free(music);
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < num_artists; i++){
        music -> artist_id[i] = artist_id[i];
    }
    music -> num_artists = num_artists;

    music -> duration = malloc(strlen(duration) + 1);
    if(!music -> duration){
        perror("erro ao alocar memória para a duracao.\n");
        free(music -> title);
        free(music -> artist_id);
        free(music);
        exit(EXIT_FAILURE);
    }
    strcpy(music -> duration, duration);
    
    music -> genre = malloc(strlen(genre) + 1);
    if(!music -> genre){
        perror("erro ao alocar memória para o género da música.\n");
        free(music -> title);
        free(music -> artist_id);
        free(music -> duration);
        free(music);
        exit(EXIT_FAILURE);
    }
    strcpy(music -> genre, genre);

    music -> year = year;

    music->lyrics = malloc(strlen(lyrics) + 1);
    if(!music -> lyrics){
        perror("erro ao alocar memória para a letra da música.\n");
        free(music -> title);
        free(music -> artist_id);
        free(music -> duration);
        free(music -> genre);
        free(music);
        exit(EXIT_FAILURE);
    }
    strcpy(music -> lyrics, lyrics);

    return music;
}

// GETTERS

// Função que retorna o ID da música
long int* getMusicID(Music* m){
    return m->id ? &(m->id) : NULL;
}

// Função que retorna o título da música
char* getMusicTitle(Music* m){
    return m->title ? strdup(m->title) : NULL;
}

// Função que retorna o array de IDs de artistas da música
long int* getMusicArtistIDs(Music* m){
    return m->artist_id;
}

// Função que retorna o número de artistas da música
int getMusicNumArtists(Music* m){
    return m->num_artists;
}

// Função que retorna a duração da música
char* getMusicDuration(Music* m){
    return m->duration ? strdup(m->duration) : NULL;
}

// Função que retorna o gênero da música
char* getMusicGenre(Music* m){
    return m->genre ? strdup(m->genre) : NULL;
}

// Função que retorna o ano da música
int getMusicYear(Music* m){
    return m->year;
}

// Função que retorna a letra da música
char* getMusicLyrics(Music* m){
    return m->lyrics ? strdup(m->lyrics) : NULL;
}

// SETTERS

// Função que altera o ID da música
void setMusicID(Music* m, int newID){
    m->id = newID;
}

// Função que altera o título da música
void setMusicTitle(Music* m, char* newTitle){
    if(m->title){
        free(m->title);
        m->title = NULL;
    }        
    m->title = strdup(newTitle);
    if(m->title == NULL){
        perror("Erro ao alocar memoria para o novo titulo da musica");
        exit(EXIT_FAILURE);
    }
}

// Função que altera o array de ID's de artistas da música
void setMusicArtistIDs(Music* m, long int* newArtistID, int newNumArtists){
    if(m->artist_id){
        free(m->artist_id);
        m->artist_id = NULL;
    }        
    m->artist_id = (long int*)malloc(newNumArtists * sizeof(long int));
    if (m->artist_id == NULL){
        perror("Erro ao alocar memoria para o novo array de artistas da musica");
        exit(EXIT_FAILURE); 
    }
    memcpy(m->artist_id, newArtistID, newNumArtists * sizeof(long int));
    m->num_artists = newNumArtists;
}

// Função que altera a duração da música
void setMusicDuration(Music* m, char* newDuration){
    if(m->duration){
        free(m->duration);
        m->duration = NULL;
    }        
    m->duration = strdup(newDuration);
    if(m->duration == NULL){
        perror("Erro ao alocar memoria para a nova duracao da musica");
        exit(EXIT_FAILURE);
    }
}

// Função que altera o género da música
void setMusicGenre(Music* m, char* newGenre){
    if(m->genre){
        free(m->genre);
        m->genre = NULL;
    }        
    m->genre = strdup(newGenre);
    if(m->genre == NULL){
        perror("Erro ao alocar memoria para o novo genero da musica");
        exit(EXIT_FAILURE);
    }
}

// Função que altera o ano da música
void setMusicYear(Music* m, int newYear){
    m->year = newYear;
}

// Função que altera a letra da música
void setMusicLyrics(Music* m, char* newLyrics){
    if(m->lyrics){
        free(m->lyrics);
        m->lyrics = NULL;
    }        
    m->lyrics = strdup(newLyrics);
    if(m->lyrics == NULL){
        perror("Erro ao alocar memoria para a nova letra da musica");
        exit(EXIT_FAILURE);
    }
}

// Função para libertar a memória de uma entidade do tipo música.
void freeMusic(Music* music){
    free(music -> title);
    free(music -> artist_id);
    free(music -> duration);
    free(music -> genre);
    free(music -> lyrics);
    free(music);
}