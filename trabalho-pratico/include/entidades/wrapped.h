#ifndef WRAPPED_H
#define WRAPPED_H

#include <stdio.h>
#include <glib.h>
#include <string.h>
//#include "../gestores/gestor_music.h"
#include "../gestores/gestor_history.h"
#include "../utils.h"
#include "music.h"
#include "history.h"


typedef struct artistsTimes ArtistsTimes;

typedef struct wrapped Wrapped;

// ----------------------------------------------------------------INITS E FREES----------------------------------------------------------------
//Query6Data* query6DataInit();
Wrapped* wrappedInit();
//void freeQuery6Data(Query6Data* query6Data);
void freeWrapped(Wrapped* wrap);

// ----------------------------------------------------------------FUNÇÕES----------------------------------------------------------------
ArtistsTimes* newArtistTime(long int* idArtist, int numArtists, long int idMusic, int segundos);
//void yearResumed(G_GNUC_UNUSED gpointer gestor_history, gpointer linhaHistory, gpointer q6data);
void procuraMusica(long int* listMus, long int idMusic);
int listArtistasIguais(long int* artistaHist, int numArtistsHist, long int* artistaWrap);

// ----------------------------------------------------------------GETS E SETS----------------------------------------------------------------
char* getWrapAno(Wrapped* wrap);
long int getWrapUserId(Wrapped* wrap);
int** getWrapAlbuns(Wrapped* wrap);
int* getWrapHoras(Wrapped* wrap);
int* getWrapGeneros(Wrapped* wrap);
int** getWrapDias(Wrapped* wrap);
ArtistsTimes* getWrapArtistsTimes(Wrapped* wrap);
long int* getArtistTimesArtistId(ArtistsTimes* at);
int getArtistTimesListTime(ArtistsTimes* at);
long int* getArtistTimesListMus(ArtistsTimes* at);
ArtistsTimes* getArtistTimesNext(ArtistsTimes* at);
void setWrapAno(Wrapped* wrap, char* ano);
void setWrapUserId(Wrapped* wrap, long int userId);
void setWrapAlbum(Wrapped* wrap, long int albumId, int segundos);
void setWrapHoras(Wrapped* wrap, char* hora, int segundos);
void setWrapGeneros(Wrapped* wrap, char* generos, int segundos);
void setWrapDias(Wrapped* wrap, char* data, int segundos);
void setWrapArtistTime(Wrapped* wrap, long int* idArtist, int numArtists, long int idMusic, int segundos);
char* getWrapTotalListTime(Wrapped* wrap, char** totalGenre);
char* getWrapTotalMusics(Wrapped* wrap);
char* getWrapTotalArtist(Wrapped* wrap);
char* getWrapTotalDay(Wrapped* wrap);
char* getWrapTotalAlbum(Wrapped* wrap);
char* getWrapTotalHour(Wrapped* wrap);

// ----------------------------------------------------------------PRINT E SORT----------------------------------------------------------------
void printWrapped(Wrapped* wrap);

void sortWrap(Wrapped* wrap);

#endif