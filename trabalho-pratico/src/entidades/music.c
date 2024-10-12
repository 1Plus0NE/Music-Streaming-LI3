#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include "music.h"
#include "../utils.h"

typedef struct music {
    int id;
    char* title;
    int* artist_id;
    int num_artists;
    char* duration;
    char* genre;
    int year;
    char* lyrics;
};

// Função para criar uma estrutura da entidade música parametrizada.
Music* createMusic(int id, char* title, int* artist_id, int num_artists, char* duration, char* genre, int year, char* lyrics){
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

    music -> artist_id = malloc(num_artists * sizeof(int));
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
        free(title);
        free(artist_id);
        free(music);
        exit(EXIT_FAILURE);
    }
    
    music -> genre = malloc(strlen(genre) + 1);
    if(!music -> genre){
        perror("erro ao alocar memória para o género da música.\n");
        free(music -> artist_id);
        free(music -> title);
        free(music);
        exit(EXIT_FAILURE);
    }
    strcpy(music -> genre, genre);

    music -> year = year;

    music->lyrics = malloc(strlen(lyrics) + 1);
    if(!music -> lyrics){
        perror("erro ao alocar memória para a letra da música.\n");
        free(music -> genre);
        free(music -> artist_id);
        free(music -> title);
        free(music);
        exit(EXIT_FAILURE);
    }
    strcpy(music -> lyrics, lyrics);

    return music;
}

// Função de verificação da validade de uma musica
int musicLineVerify(char *line){

    char *info = strtok(&line, ";");
    
    for(int i = 0; i <= 6; i++){

        if(info){
            switch(i){
                case 0:
                    // id nao pode ser < 0
                    if(atoi(&info)<0) return 1;
                    info = strtok(NULL, ";");
                    break;
                case 1:
                    // title da musica nao pode ser uma string empty
                    if(!remove_aspas(&info)) return 1;
                    info = strtok(NULL, ";");
                    break;
                case 2:
                    // array de artistas nao pode ser empty
                    if(!remove_aspas(&info)) return 1;
                    info = strtok(NULL, ";");
                    break;
                case 3:
                    // duracao tem que ser sintaticamente valida
                    if(!verify_music(&info)) return 1;
                    info = strtok(NULL, ";");
                    break;
                case 4:
                    // genero nao pode ser uma string empty
                    if(!remove_aspas(&info)) return 1;
                    info = strtok(NULL, ";");
                    break;
                case 5:
                    // ano nao pode ser maior que o ano atual
                    if(!verify_year(atoi(&info))) return 1;
                    info = strtok(NULL, ";");
                    break;
                case 6:
                    // as lyrics nao podem ser uma string empty
                    if(!remove_aspas(&info)) return 1;
                    info = strtok(NULL, ";");
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}

// GETTERS

// Função que retorna o ID da música
int getID(Music* m){
    return m->id;
}

// Função que retorna o título da música
char* getTitle(Music* m){
    return m->title ? strdup(m->title) : NULL;
}

// Função que retorna o array de IDs de artistas da música
int* getArtistID(Music* m){
    return m->artist_id;
}

// Função que retorna o número de artistas da música
int getNumArtists(Music* m){
    return m->num_artists;
}

// Função que retorna a duração da música
char* getDuration(Music* m){
    return m->duration ? strdup(m->duration) : NULL;
}

// Função que retorna o gênero da música
char* getGenre(Music* m){
    return m->genre ? strdup(m->genre) : NULL;
}

// Função que retorna o ano da música
int getYear(Music* m){
    return m->year;
}

// Função que retorna a letra da música
char getLyrics(Music* m){
    return m->lyrics ? strdup(m->lyrics) : NULL;
}

// SETTERS

// Função que altera o ID da música
void setID(Music* m, int newID){
    m->id = newID;
}

// Função que altera o título da música
void setTitle(Music* m, const char* newTitle){
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
void setArtistID(Music* m, int* newArtistID, int newNumArtists){
    if(m->artist_id){
        free(m->artist_id);
        m->artist_id = NULL;
    }        
    m->artist_id = (int*)malloc(newNumArtists * sizeof(int));
    if (m->artist_id == NULL){
        perror("Erro ao alocar memoria para o novo array de artistas da musica");
        exit(EXIT_FAILURE); 
    }
    memcpy(m->artist_id, newArtistID, newNumArtists * sizeof(int));
    m->num_artists = newNumArtists;
}

// Função que altera a duração da música
void setDuration(Music* m, const char* newDuration){
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
void setGenre(Music* m, const char* newGenre){
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
void setYear(Music* m, int newYear){
    m->year = newYear;
}

// Função que altera a letra da música
void setLyrics(Music* m, const char* newLyrics){
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