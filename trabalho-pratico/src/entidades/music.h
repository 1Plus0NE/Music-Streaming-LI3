#ifndef MUSIC_H
#define MUSIC_H
#include <stdio.h>

// Forma de enunciar a entidade música.
typedef struct music Music;

// Função para criar uma estrutura da entidade música parametrizada.
Music* createMusic(int id, char* title, int* artist_id, int num_artists, char* duration, char* genre, int year, char* lyrics);

// Função que faz a validação sintática da duração de uma música
int verify_music(char* duration);

// GETTERS
int getID(Music* m);
char* getTitle(Music* m);
int* getArtistID(Music* m);
int getNumArtists(Music* m);
char* getDuration(Music* m);
char* getGenre(Music* m);
int getYear(Music* m);
char getLyrics(Music* m);

// SETTERS
void setID(Music* m, int newID);
void setTitle(Music* m, const char* newTitle);
void setArtistID(Music* m, int* newArtistID, int newNumArtists);
void setDuration(Music* m, const char* newDuration);
void setGenre(Music* m, const char* newGenre);
void setYear(Music* m, int newYear);
void setLyrics(Music* m, const char* newLyrics);

// Função para libertar a memória de uma entidade do tipo música.
void freeMusic(Music* music);

#endif