#ifndef USER_H
#define USER_H
#include <stdio.h>

// Forma de enunciar a entidade utilizador.
typedef struct user User;

// Função para criar uma estrutura da entidade utilizador parametrizada.
User* createUser(char* username, char* email, char* first_name, char* last_name, char* birth_date , char* genre, char* country, char* subscription_type, int* liked_musics_id, int num_liked_musics);

// Função para libertar a memória de uma entidade do tipo utilizador.
void freeUser(User* user);

#endif