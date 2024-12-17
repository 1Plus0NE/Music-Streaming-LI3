#ifndef PARSER_HISTORY_H
#define PARSER_HISTORY_H

#include "../entidades/history.h"
#include "../gestores/gestor_history.h"
#include "../utils.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função que dá parse ao ficheiro de históricos.
void parse_history(char* path, GestorHistory* gestorHistory);

// Função que processa uma linha de histórico.
void process_history_line(char* line, void* gestor, void* aux_data);

#endif