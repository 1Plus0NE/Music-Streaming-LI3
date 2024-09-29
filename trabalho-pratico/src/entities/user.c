#include <stdio.h>
#include <string.h>
#include "user.h"

typedef struct user {
    char* username;
    char* email;
    char* first_name;
    char* last_name;
    char birth_date[11];
    char* country;
    char* subscription_type;
    int* liked_musics_id;
    int num_liked_musics;
}

// Função para criar uma estrutura da entidade utilizador parametrizada.
User* createUser(char* username, char* email, char* first_name, char* last_name, char* birth_date , char* genre, char* country, char* subscription_type, int* liked_musics_id, int num_liked_musics){
    User* user = (User*)malloc(sizeof(User));
    if (!user) {
        perror("erro ao alocar memória para o utilizador.\n");
        exit(EXIT_FAILURE);
    }

    user -> username = malloc(strlen(username) + 1);
    if (!user -> username) {
        perror("erro ao alocar memória para o username.\n");
        free(user);
        exit(EXIT_FAILURE);
    }
    strcpy(user -> username, username);

    user -> email = malloc(strlen(email) + 1);
    if (!user -> email) {
        perror("Erro ao alocar memória para o email.\n");
        free(user -> username);
        free(user);
        exit(EXIT_FAILURE);
    }
    strcpy(user -> email, email);

    user -> first_name = malloc(strlen(first_name) + 1);
    if (!user -> first_name) {
        perror("Erro ao alocar memória para o primeiro nome.\n");
        free(user -> email);
        free(user -> username);
        free(user);
        exit(EXIT_FAILURE);
    }
    strcpy(user -> first_name, first_name);

    user -> last_name = malloc(strlen(last_name) + 1);
    if (!user -> last_name) {
        perror("Erro ao alocar memória para o último nome.\n");
        free(user -> first_name);
        free(user -> email);
        free(user -> username);
        free(user);
        exit(EXIT_FAILURE);
    }
    strcpy(user -> last_name, last_name);

    strncpy(user -> birth_date, birth_date, 10);
    user -> birth_date[10] = '\0';

    user -> country = malloc(strlen(country) + 1);
    if (!user -> country) {
        perror("Erro ao alocar memória para o país.\n");
        free(user -> last_name);
        free(user -> first_name);
        free(user -> email);
        free(user -> username);
        free(user);
        exit(EXIT_FAILURE);
    }
    strcpy(user -> country, country);

    user -> subscription_type = malloc(strlen(subscription_type) + 1);
    if (!user -> subscription_type) {
        perror("Erro ao alocar memória para o tipo de subscricao.\n");
        free(user -> country);
        free(user -> last_name);
        free(user -> first_name);
        free(user -> email);
        free(user -> username);
        free(user);
        exit(EXIT_FAILURE);
    }
    strcpy(user -> subscription_type, subscription_type);

    user -> liked_musics_id = malloc(num_liked_musics * sizeof(int));
    if (!user -> liked_musics_id) {
        perror("Erro ao alocar memória para a lista de músicas com gosto.\n");
        free(user -> subscription_type);
        free(user -> country);
        free(user -> last_name);
        free(user -> first_name);
        free(user -> email);
        free(user -> username);
        free(user);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num_liked_musics; i++) {
        user -> liked_musics_id[i] = liked_musics_id[i];
    }
    user -> num_liked_musics = num_liked_musics;

    return user;
}

// Função para libertar a memória de uma entidade do tipo utilizador.
void freeUser(User* user){
    free(user -> subscription_type);
    free(user -> country);
    free(user -> last_name);
    free(user -> first_name);
    free(user -> email);
    free(user -> username);
    free(user);
}