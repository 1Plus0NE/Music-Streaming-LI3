#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.h"

typedef struct user {
    char* username;
    char* email;
    char* first_name;
    char* last_name;
    char birth_date[10]; // data base 2024/09/09
    char* country;
    char* subscription_type;
    int* liked_musics_id; // char* liked_musics_id?
    int num_liked_musics;
};

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

// Função de verificação da validade de um user
int userLineVerify(char *line){

    char *info = strtok(&line, ";");
    
    for(int i = 0; i <= 7; i++){

        if(info){
            switch(i){
                case 0:
                    // Possivel erro, pretende verificar string vazia
                    if(!remove_aspas(&info)){
                        return 1;
                    }
                    info = strtok(NULL, ";");
                    break;
                case 1:
                    if(emailVerify(remove_aspas(&info))!=0) return 1;
                    info = strtok(NULL, ";");
                    break;
                case 2:
                    if(nameVerify(remove_aspas(&info))!=0) return 1;
                    info = strtok(NULL, ";");
                    break;
                case 3:
                    if(nameVerify(remove_aspas(&info))!=0) return 1;
                    info = strtok(NULL, ";");
                    break;
                case 4:
                    if(birthDateVerify(remove_aspas(&info))!=0) return 1;
                    info = strtok(NULL, ";");
                    break;
                case 5:
                    // Possivel erro
                    if(!remove_aspas(&info)){
                        return 1;
                    }
                    info = strtok(NULL, ";");
                    break;
                case 6:
                    if( (strcmp("premium",remove_aspas(&info)) || strcmp("normal",remove_aspas(&info)) )!=0) return 1;
                    info = strtok(NULL, ";");
                    break;
                case 7:
                    // verificação se as musicas com gosto estão dentro do ficheiro de musicas
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}

// Função para verificar se o nome é inteiramente carateres
int nameVerify(char *name){
    
    // Caso vazio
    if(!name){
        return 1;
    }

    while(*name){
        if(!isalpha(*name)){
            return 1;
        }
        name++;
    }
    return 0;
}

// Função que valida um endereço de email, dividindo por tokens e verificando se e qual o conteudo desses tokens
int emailVerify(char *email){
    
    if(!email){
        return 1;
    }

    // Testar com  casos práticos a divisao por tokens
    char *user = strtok(email, "@");
    char *lDomain = strtok(NULL, ".");
    char *rDomain = strtok(NULL, "\0");
    if(!user || !lDomain || !rDomain) return 1;

    for(int i=0;user[i]!='\0';i++){
        if(!isdigit(user[i]) || !isalpha(user[i])) return 1;
    }
    if(nameVerify(lDomain) == 1) return 1;
    if(nameVerify(rDomain) == 1 || strlen(rDomain)<=1 || strlen(rDomain)>=4) return 1;    
    
    return 0;
}

int birthDateVerify(char* birth_date){
    // data base 2024/09/09

    if(!birth_date){
        return 1;
    }

    if(birth_date[4] != '/' || birth_date[7] != '/' || birth_date[10] != '\0') return 1;

    char *ano = strtok(birth_date, "/");
    char *mes = strtok(NULL, "/");
    char *dia = strtok(NULL, "\0");

    if((strDigit(ano) || strDigit(mes) || strDigit(dia)) != 0) return 1;
    
    // Data numérica verificada, transformar em int
    int anoInt = atoi(ano);
    int mesInt = atoi(mes);
    int diaInt = atoi(dia);

    // Verificação lógica
    if(anoInt>2024 || (anoInt==2024 && mesInt>9) || (anoInt==2024 && mesInt==9 && diaInt>9)) return 1;
    else if(anoInt<0) return 1;
    else if(mesInt<=0 || mesInt>12) return 1;
    else if(diaInt<=0 || diaInt>31) return 1;
    else return 0;
}

// Função que verifica se toda a string é composta por dígitos
int strDigit(char *str){
    
    if(!str){
        return 1;
    }

    while(*str){
        if(!isdigit(*str)){
            return 1;
        }
        str++;
    }
    return 0;
}