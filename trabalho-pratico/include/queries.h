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

// função que responde á query1.
void query1(char* id_str, GestorUser* gestorUser, GestorArtist* gestorArtist, GestorAlbum* gestorAlbum, GestorHistory* gestorHistory, char delimiter, FILE* output_file);

// Função para a 2ª query sem especificação de informações
void query2(int nArtists, Discography* disco, char delimiter, FILE* output);

// Função para a 2ª query, com especificação de país
void query2b(int nArtists, char* country, Discography* disco, char delimiter, FILE* output);

// Função para a 3ª query
void query3(int ageMin, int ageMax, GestorUser* gestorUser, char delimiter, FILE* output);

#endif