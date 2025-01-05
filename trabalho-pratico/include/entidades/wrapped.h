#ifndef WRAPPED_H
#define WRAPPED_H
#include <stdio.h>
#include <glib.h>
#include <string.h>
#include "../gestores/gestor_music.h"
#include "../gestores/gestor_history.h"
#include "../utils.h"
#include "music.h"
#include "history.h"

struct artistsTimes{
    long int* artistId;
    int listTime;
    long int* listMus;
    struct artistsTimes* next;    
};
typedef struct artistsTimes ArtistsTimes;

// Estrutura com o wrapped
struct wrapped{
    char* ano; 
    long int userId; // Formato sem 0s
    int** albuns;
    int* horas; //horas[24]
    int* generos; // generos[10]
    int** dias;
    ArtistsTimes* artistsTimes;
};


typedef struct wrapped Wrapped;
// Estrutura com os dados para resolver a Query 6
// Possui a estrutura com a resposta da Query 6 (wrap)
// Possui a Hash de musicas necessária para passar como argumento para o foreachHistory
struct query6Data{
    Wrapped* wrap;
    GestorMusic* gestorMusic;
};

typedef struct query6Data Query6Data;

// ----------------------------------------------------------------INITS E FREES----------------------------------------------------------------
Query6Data* query6DataInit();
Wrapped* wrappedInit();
void freeQuery6Data(Query6Data* query6Data);
void freeWrapped(Wrapped* wrap);

// ----------------------------------------------------------------FUNÇÕES----------------------------------------------------------------
ArtistsTimes* newArtistTime(long int* idArtist, int numArtists, long int idMusic, int segundos);
void yearResumed(G_GNUC_UNUSED gpointer gestor_history, gpointer linhaHistory, gpointer q6data);
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