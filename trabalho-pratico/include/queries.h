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
void query1(char* user_username, GestorUser* gestorUser, FILE* output_file);

// Função para a 2ª query sem especificação de informações
void query2(int nArtists, Discography* disco, FILE* output);

// Função para a 2ª query, com especificação de país
void query2b(int nArtists, char* country, Discography* disco, FILE* output);

// Funções de auxilio para a query 3 (depois passo para outro file)
int isUserInRange(User *user, int minAge, int maxAge);

int getGenreIndex(char *genre, char **genre_array, int genre_count);

void countUserLikedMusics(User* user, GestorMusic* gestorMusic, char* genres[], long int genre_likes[], int* genre_count);

void sortGenresByLikes(char* genres[], long int genre_likes[], int genre_count);

// Função para a 3ª query
void query3(int ageMin, int ageMax, GestorUser* gestorUser, GestorMusic* gestorMusic,FILE* output);

#endif