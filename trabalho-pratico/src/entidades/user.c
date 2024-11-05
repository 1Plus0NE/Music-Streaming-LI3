#include "../../include/entidades/user.h"
#include "../../include/gestores/gestor_user.h"

struct user {
    char* username;
    char* email;
    char* first_name;
    char* last_name;
    char* birth_date; // data base 2024/09/09
    char* country;
    SubscriptionType subscription_type;
    long int* liked_musics_id;
    int num_liked_musics;
};

// Função para criar uma estrutura da entidade utilizador parametrizada.
User* createUser(char* username, char* email, char* first_name, char* last_name, char* birth_date , char* country, SubscriptionType subscription_type, long int* liked_musics_id, int num_liked_musics){
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

    user -> birth_date = malloc(strlen(birth_date) + 1);
    if(!user -> birth_date){
        perror("Erro ao alocar memória para a data de nascimento.\n");
        free(user -> last_name);
        free(user -> first_name);
        free(user -> email);
        free(user -> username);
        free(user);
        exit(EXIT_FAILURE);
    }
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

    user -> subscription_type = subscription_type;

    user -> liked_musics_id = malloc(num_liked_musics * sizeof(long int));
    if (!user -> liked_musics_id) {
        perror("Erro ao alocar memória para a lista de músicas com gosto.\n");
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
    free(user -> liked_musics_id);
    free(user -> country);
    free(user -> last_name);
    free(user -> first_name);
    free(user -> email);
    free(user -> username);
    free(user);
}

// Função de verificação da validade de um user
int userLineVerify(char *line, GHashTable* music_table){
    //char *info = strsep(&line, ";");
    char *info=NULL;
    long int* musicsIds;
    int N;

    for(int i = 0; i <= 7; i++){
        info=strsep(&line, ";");
        if(info){
            switch(i){
                case 1:
                    if(emailVerify(remove_aspas(info))!=0) return 1;
                    break;
                case 4:
                    if(birthDateVerify(remove_aspas(info))!=0) return 1;
                    break;
                case 6:
                    info = remove_aspas(info);
                    if(strcmp("premium",info)!=0 && strcmp("normal",info)!=0) return 1;
                    break;
                case 7:
                    info = remove_aspas(strsep(&info,"\n"));
                    musicsIds=convertID(info,&N);
                    if(!validateMusicId(music_table, musicsIds, N)){
                        free(musicsIds);
                        return 1;
                    }
                    free(musicsIds);
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}

//getters de utilizador
char* getUserUsername(User* u){
    return u -> username ? strdup(u -> username) : NULL;
}

char* getUserEmail(User* u){
    return u->email ? strdup(u->email) : NULL;
}

char* getUserFirstName(User* u){
    return u->first_name ? strdup(u->first_name) : NULL;
}

char* getUserLastName(User* u){
    return u->last_name ? strdup(u->last_name) : NULL;
}

char* getUserBirthDate(User* u){
    return strdup(u->birth_date);
}

char* getUserCountry(User* u){
    return u->country ? strdup(u->country) : NULL;
}

SubscriptionType getUserSubscriptionType(User* u){
    return u->subscription_type;
}

long int* getUserLikedMusics(User* u){
    if (u->num_liked_musics > 0) {
        long int* cpy = malloc(u->num_liked_musics * sizeof(long int));
        memcpy(cpy, u->liked_musics_id, u->num_liked_musics * sizeof(long int));
        return cpy;
    }
    return NULL;
}

int getUserNumLikedMusics(User* u){
    return u->num_liked_musics;
}

//setters de utilizador
void setUserUsername(User* u, char* username){
    if (u->username) {
        free(u->username);
    }
    u->username = strdup(username);
}

void setUserEmail(User* u, char* email){
    if (u->email) {
        free(u->email);
    }
    u->email = strdup(email);
}

void setUserFirstName(User* u, char* first_name){
    if (u->first_name) {
        free(u->first_name);
    }
    u->first_name = strdup(first_name);
}

void setUserLastName(User* u, char* last_name){
    if (u->last_name) {
        free(u->last_name);
    }
    u->last_name = strdup(last_name);
}

void setUserBirthDate(User* u, char* birth_date){
    strncpy(u->birth_date, birth_date, 10);
}

void setUserCountry(User* u, char* country){
    if (u->country) {
        free(u->country);
    }
    u->country = strdup(country);
}

void setUserSubscriptionType(User* u, SubscriptionType subscription_type){
   
    u->subscription_type = subscription_type;
}

void setUserLikedMusics(User* u, long int* liked_musics_id, int num_liked_musics){
    if (u->liked_musics_id) {
        free(u->liked_musics_id);
    }
    u->liked_musics_id = malloc(num_liked_musics * sizeof(long int));
    memcpy(u->liked_musics_id, liked_musics_id, num_liked_musics * sizeof(long int));
    u->num_liked_musics = num_liked_musics;
}

void setUserNumLikedMusics(User* u, int num_liked_musics){
    u->num_liked_musics = num_liked_musics;
}

SubscriptionType stringToSubscriptionType(char* subType){
    if(strcmp(subType, "normal") == 0){
        return NORMAL;
    }else if(strcmp(subType, "premium") == 0){
        return PREMIUM;
    }else{
        fprintf(stderr, "Subscrição inválida %s.\n", subType);
        exit(EXIT_FAILURE);
    }
}