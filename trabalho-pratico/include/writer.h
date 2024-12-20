#ifndef WRITER_H
#define WRITER_H
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

char getDelimiter(const char* delimiter);
void genericOutputWriter(FILE* output, char delimiter, ...);

#endif