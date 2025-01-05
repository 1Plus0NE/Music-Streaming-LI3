/**
 * @file queries.h
 * @brief Funções que respondem ás queries.
 */
#ifndef QUERIES_H
#define QUERIES_H
#include <stdio.h>
#include <glib.h>
#include "gestores/gestor_user.h"
#include "gestores/gestor_music.h"
#include "gestores/gestor_artist.h"
#include "gestores/gestor_album.h"
#include "gestores/gestor_history.h"
#include "entidades/artist.h"
#include "entidades/music.h"
#include "entidades/discography.h"
#include "writer.h"
#include <string.h>

/**
 * @brief Função que responde á query 1.
 * 
 * @param id_str String com o ID do artista.
 * @param gestorUser Gestor de utilizadores.
 * @param gestorArtist Gestor de artistas.
 * @param delimiter Delimitador.
 * @param output_file Ficheiro de output.
 */
void query1(char* id_str, GestorUser* gestorUser, GestorArtist* gestorArtist, char delimiter, FILE* output_file);

/**
 * @brief Função que responde á query 2
 * 
 * @param nArtists Número de artistas.
 * @param country País.
 * @param disco Discografia.
 * @param delimiter Delimitador.
 * @param output Ficheiro de output.
 */
void query2(int nArtists, char* country, Discography* disco, char delimiter, FILE* output);

/**
 * @brief Função que responde á query 3
 * 
 * @param ageMin Idade mínima.
 * @param ageMax Idade máxima.
 * @param gestorUser Gestor de utilizadores.
 * @param delimiter Delimitador.
 * @param output Ficheiro de output.
 */
void query3(int ageMin, int ageMax, GestorUser* gestorUser, char delimiter, FILE* output);

/**
 * @brief Função que responde á query 4
 * 
 * @param gestorHistory Gestor de históricos.
 * @param username Nome de utilizador.
 * @param numRecommendations Número de recomendações.
 * @param output Ficheiro de output.
 */
void query5(GestorHistory* gestorHistory, char* username, int numRecommendations, FILE* output);

typedef struct artistsTimes ArtistsTimes;
typedef struct wrapped Wrapped;
typedef struct query6Data Query6Data;

Wrapped* wrappedInit();
void freeWrapped(Wrapped* wrap);
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

int listArtistasIguais(long int* artistaHist, int numArtistsHist, long int* artistaWrap);
ArtistsTimes* newArtistTime(long int* idArtist, int numArtists, long int idMusic, int segundos);
void procuraMusica(long int* listMus, long int idMusic);
Query6Data* query6DataInit();
void yearResumed(G_GNUC_UNUSED gpointer gestor_history, gpointer linhaHistory, gpointer q6data);
void printWrapped(Wrapped* wrap);
char* wrapTotalListTime(Wrapped* wrap, char** totalGenre);
char* wrapTotalMusics(Wrapped* wrap);
char* wrapTotalArtist(Wrapped* wrap);
char* wrapTotalDay(Wrapped* wrap);
char* wrapTotalAlbum(Wrapped* wrap);
char* wrapTotalHour(Wrapped* wrap);
void sortWrap(Wrapped* wrap);
void printWrap(Wrapped* wrap); // Remover
void freeQuery6Data(Query6Data* query6Data);
void query6(char* idUser, char* year, char* n, GestorHistory* gestor_history, GestorMusic* gestorMusic, char delimiter, FILE* output);
#endif