#ifndef PARSER_H
#define PARSER_H
#include "../entidades/artist.h"
#include "../entidades/music.h"
#include "../entidades/user.h"

// Função que cria uma diretoria com os ficheiros de erros, com os headers
void errosDir();

// Função que faz a validação de um artista.
int verify_artist(Artist* artist);

// Função para ler e fazer parse de um arquivo CSV de artistas.
int parse_artist_csv(const char* filename);

// Função para ler e fazer parse de um arquivo CSV de músicas.
int parse_music_csv(const char* filename);

// Função para ler e fazer parse de um arquivo CSV de utilizadores.
int parse_user_csv(const char* filename);

#endif