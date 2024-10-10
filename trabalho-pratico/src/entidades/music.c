#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include "music.h"
#include "utils.h"

typedef struct music {
    int id;
    char* title;
    int* artist_id;
    int num_artists;
    int duration;
    char* genre;
    int year;
    char* lyrics;
};

// Função para criar uma estrutura da entidade música parametrizada.
Music* createMusic(int id, char* title, int* artist_id, int num_artists, int duration, char* genre, int year, char* lyrics){
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
    music -> duration = duration;
    
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
                    // genero nao pode ser uma string empty
                    if(!remove_aspas(&info)) return 1;
                    info = strtok(NULL, ";");
                    break;
                case 3:
                    // duracao tem que ser sintaticamente valida
                    if(!verify_music(atoi(&info))) return 1;
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

// Função para libertar a memória de uma entidade do tipo música.
void freeMusic(Music* music){
    free(music -> title);
    free(music -> artist_id);
    free(music -> genre);
    free(music -> lyrics);
    free(music);
}