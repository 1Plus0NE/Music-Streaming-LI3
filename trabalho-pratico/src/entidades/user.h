#ifndef USER_H
#define USER_H
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

// Forma de enunciar a entidade utilizador.
typedef struct user User;

// Função para criar uma estrutura da entidade utilizador parametrizada.
User* createUser(char* username, char* email, char* first_name, char* last_name, char* birth_date , char* country, char* subscription_type, int* liked_musics_id, int num_liked_musics);

// Função para libertar a memória de uma entidade do tipo utilizador.
void freeUser(User* user);

// Função de verificação da validade de um utilizador.
int userLineVerify(char *line);

//getters de utilizador
char* getUserUsername(User* u);

char* getUserEmail(User* u);

char* getUserFirstName(User* u);

char* getUserLastName(User* u);

char* getUserBirthDate(User* u);

char* getUserCountry(User* u);

char* getUserSubscriptionType(User* u);

int* getUserLikedMusics(User* u);

int getUserNumLikedMusics(User* u);

//setters de utilizador
void setUserUsername(User* u, char* username);

void setUserEmail(User* u, char* email);

void setUserFirstName(User* u, char* first_name);

void setUserLastName(User* u, char* last_name);

void setUserBirthDate(User* u, char* birth_date);

void setUserCountry(User* u, char* country);

void setUserSubscriptionType(User* u, char* subscription_type);

void setUserLikedMusics(User* u, int* liked_musics_id, int num_liked_musics);

void setUserNumLikedMusics(User* u, int num_liked_musics);

#endif