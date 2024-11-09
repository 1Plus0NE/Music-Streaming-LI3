#ifndef PARSER_USER_H
#define PARSER_USER_H

#include "../gestores/gestor_user.h"
#include "../gestores/gestor_music.h"
#include "../entidades/user.h"
#include "../entidades/music.h"
#include "../utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função de verificação da validade de um user
int userLineVerify(char *line, GestorMusic* gestorMusic);

// função para ler e fazer parse de um ficheiro CSV de artistas.
void parse_user(char* path, GestorUser* gestorUser, GestorMusic* gestorMusic);

#endif