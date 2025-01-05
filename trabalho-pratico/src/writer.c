#include "../include/writer.h"

char getDelimiter(const char* str){
    return (str[1] == 'S') ? '=' : ';';
}

void genericOutputWriter(FILE* output, char delimiter, ...){
    if(!output || !delimiter) return;

    va_list args;
    va_start(args, delimiter);

    const char* currentArg = va_arg(args, const char*);
    int first = 1;

    while(currentArg){
        if(!first){
            fputc(delimiter, output); // Escreve o delimitador como um char 
        }
        fprintf(output, "%s", currentArg);  
        first = 0;

        currentArg = va_arg(args, const char*); // get do prox argumento
    }

    va_end(args);
    fprintf(output, "\n"); 
}