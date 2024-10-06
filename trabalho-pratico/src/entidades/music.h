#ifndef MUSIC_H
#define MUSIC_H
#include <stdio.h>

// Forma de enunciar a entidade música.
typedef struct music Music;

// Função para criar uma estrutura da entidade música parametrizada.
Music* createMusic(int id, char* title, int* artist_id, int num_artists, int duration, char* genre, int year, char* lyrics);

// Função que faz a validação sintática da duração de uma música
int verify_music(char* duration);

// Função que verifica se um dado ano é válido
int verify_year(int year);

// Função para libertar a memória de uma entidade do tipo música.
void freeMusic(Music* music);

#endif