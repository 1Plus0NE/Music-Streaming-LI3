#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "music.h"

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

// Função que faz a validação sintática da duração de uma música
int verify_music(char* duration) {
    // se cumpre o formato "hh:mm:ss"
    if (strlen(duration) != 8 && duration[2] != ':' && duration[5] != ':') {
        return 0; // invalid format
    }

    // verificar se as horas, minutos e segundos sao digitos entre 0 e 9
    for (int i = 0; i < 8; i++) {
        if (i != 2 && i != 5) { // nao interessa os ':'
            if (!isdigit(duration[i])) {
                return 0; 
            }
        }
    }

    // convertemos as horas, minutos e segundos a inteiros
    int hours = (duration[0] - '0') * 10 + (duration[1] - '0'); 
    int minutes = (duration[3] - '0') * 10 + (duration[4] - '0');
    int seconds = (duration[6] - '0') * 10 + (duration[7] - '0');

    // verificamos se cumprem os intervalos estabelecidos 
    if (hours < 0 || hours > 100 || minutes < 0 || minutes > 60 || seconds < 0 || seconds > 60) {
        return 0;
    }

    return 1; 
}

// Função para libertar a memória de uma entidade do tipo música.
void freeMusic(Music* music){
    free(music -> title);
    free(music -> artist_id);
    free(music -> genre);
    free(music -> lyrics);
    free(music);
}