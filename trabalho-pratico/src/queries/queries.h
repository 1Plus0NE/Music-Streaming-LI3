#ifndef QUERIES_H
#define QUERIES_H

#include <stdio.h>
#include "gestor_user.h"
#include "gestor_artist.h"
#include "gestor_music.h"

// função que calcula a idade através de uma data de nascimento dada como argumento.
int calculaIdade(char* birthdate);

// função que responde á query1.
void query1(int user_id, FILE* output_file);

#endif