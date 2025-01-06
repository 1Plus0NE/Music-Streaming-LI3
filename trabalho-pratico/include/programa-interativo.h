/**
 * @file programa-interativo.h
 * @brief Arquivo com as funções auxiliares para o programa interativo
 */
#ifndef PROGRAMA_INTERATIVO_H
#define PROGRAMA_INTERATIVO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parser/parser.h"
#include "../include/queries.h"
#include "../include/gestores/gestor_user.h"
#include "../include/gestores/gestor_music.h"
#include "../include/gestores/gestor_artist.h"
#include "../include/gestores/gestor_album.h"
#include "../include/gestores/gestor_history.h"
#include "../include/writer.h"
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"

/**
 * @brief Função que imprime o menu do programa interativo.
 * @details Função que imprime o menu do programa interativo.
 * 
 */
void printMenu();

#endif