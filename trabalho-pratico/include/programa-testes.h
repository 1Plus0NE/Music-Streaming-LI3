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

//função auxiliar para comparar as saídas obtidas e esperadas
void compare_outputs(FILE *result_file, FILE *expected_file, int *correct_count, int *line_diff);

#endif