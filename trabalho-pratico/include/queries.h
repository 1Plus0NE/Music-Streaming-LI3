#ifndef QUERIES_H
#define QUERIES_H
#include <stdio.h>
#include <glib.h>
#include "gestores/gestor_user.h"
#include "gestores/gestor_music.h"
#include "gestores/gestor_artist.h"
#include "entidades/artist.h"
#include "entidades/music.h"
#include <string.h>

// Lista ligada para a Query 2 
typedef struct discography Discography;

// função que calcula a idade através de uma data de nascimento dada como argumento.
int calculaIdade(char* birthdate);

// função que responde á query1.
void query1(char* user_username, GHashTable* user_table, FILE* output_file);

// Função para a 2ª query sem especificação de informações
void query2(int nArtists, Discography* disco, FILE* output);

// Função para a 2ª query, com especificação de país
void query2b(int nArtists, char* country, Discography* disco, FILE* output);

// Função para a 3ª query
void query3(int ageMin, int ageMax, GHashTable* userTable, GHashTable* musicTable,FILE* output);

//--------------- Discografia-------------

Discography* artistInsert(Discography* disco, long int id, const char* name, const char* country, ArtistType type);

void durationAdd(Discography* disco, const char* duration, long int id);

void freeDiscography(Discography* disco);

Discography* fillWithArtists(GHashTable* table, Discography* disco);

void artistFromTableToLL(gpointer artistId, gpointer artistData, gpointer discoPtr);

Discography* updateArtistsDurationFromMusic(GHashTable* musicTable, Discography* disco);

void artistDurationAdd(gpointer musicId, gpointer musicData, gpointer discoPtr);
#endif