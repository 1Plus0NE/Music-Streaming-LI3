#ifndef PARSER_H
#define PARSER_H

// Função que cria uma diretoria com os ficheiros de erros, com os headers
void errosDir();

// Função responsável por remover as aspas.
char* remove_aspas(char* str);

// Função para ler e fazer parse de um arquivo CSV de artistas.
int parse_artist_csv(const char* filename);

// Função para ler e fazer parse de um arquivo CSV de músicas.
int parse_music_csv(const char* filename);

// Função para ler e fazer parse de um arquivo CSV de utilizadores.
int parse_user_csv(const char* filename);

#endif