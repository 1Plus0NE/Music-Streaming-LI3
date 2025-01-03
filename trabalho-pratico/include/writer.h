/**
 * @file writer.h
 * @brief Funções de escrita.
 */
#ifndef WRITER_H
#define WRITER_H
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

/**
 * @brief Função que devolve o delimitador.
 * @details Função que devolve o delimitador.
 * 
 * @param delimiter Delimitador.
 * @return Retorna o delimitador.
 */
char getDelimiter(const char* delimiter);

/**
 * @brief Função que escreve um output genérico.
 * @details Função que escreve um output genérico.
 * 
 * @param output Ficheiro de output.
 * @param delimiter Delimitador.
 * @param ... Argumentos.
 */
void genericOutputWriter(FILE* output, char delimiter, ...);

#endif