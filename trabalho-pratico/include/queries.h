#ifndef QUERIES_H
#define QUERIES_H
#include <stdio.h>
#include <glib.h>
#include "gestores/gestor_user.h"
#include "gestores/gestor_music.h"
#include "gestores/gestor_artist.h"
#include "entidades/artist.h"
#include "entidades/music.h"
#include "entidades/discography.h"
#include <string.h>

// função que responde á query1.
void query1(char* user_username, GestorUser* gestorUser, FILE* output_file);

// Função para a 2ª query sem especificação de informações
void query2(int nArtists, Discography* disco, FILE* output);

// Função para a 2ª query, com especificação de país
void query2b(int nArtists, char* country, Discography* disco, FILE* output);

// Função para a 3ª query
void query3(int ageMin, int ageMax, GestorUser* gestorUser, FILE* output);

#endif