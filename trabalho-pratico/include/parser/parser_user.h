#ifndef PARSER_USER_H
#define PARSER_USER_H

#include "../gestores/gestor_user.h"
#include "../gestores/gestor_music.h"
#include "../entidades/user.h"
#include "../entidades/music.h"
#include "../utils.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função de verificação da validade de um user
int userLineVerify(char *line, GestorMusic* gestorMusic);

// Função que dá parse ao ficheiro de utilizadores.
void parse_user(char* path, GestorUser* gestorUser, GestorMusic* gestorMusic);

// função que processa a linha de um utilizador.
void process_user_line(char* line, void* gestor, void* aux_dataX, void* aux_dataY);

#endif