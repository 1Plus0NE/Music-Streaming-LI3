/**
 * @file programa-testes.h
 * @brief Arquivo com as funções auxiliares para testar o programa
 */
#ifndef QUERIES_H
#define QUERIES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>
#include "../include/parser/parser.h"
#include "../include/queries.h"

#define MAX_LINE_LENGTH 1024

/**
 * @brief Função que compara os arquivos de saída.
 * @param result_file Arquivo de saída gerado pelo programa.
 * @param expected_file Arquivo de saída esperado.
 * @param correct_count Ponteiro para a variável que armazena a quantidade de linhas corretas.
 * @param line_diff Ponteiro para a variável que armazena a quantidade de linhas diferentes.
 */
void compare_outputs(FILE *result_file, FILE *expected_file, int *correct_count, int *line_diff);

#endif