#ifndef QUERIES_H
#define QUERIES_H
#include <stdio.h>
#include <glib.h>
#include "../gestores/gestor_user.h"
#include "../gestores/gestor_music.h"
#include "../gestores/gestor_artist.h"
#include "../entidades/artist.h"

// função que calcula a idade através de uma data de nascimento dada como argumento.
int calculaIdade(char* birthdate);

// função que responde á query1.
void query1(char* user_username, GHashTable* user_table, FILE* output_file);

#endif