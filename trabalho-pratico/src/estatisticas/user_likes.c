#include "../../include/estatisticas/user_likes.h"

// Estrutura para organizar os likes de cada user
struct user_likes{
    char** genres;
    long int* likes;
    int size; // tamanho dos arrays
    int age;
};

// Função para criar uma estrutura de likes 
UserLikes* createUserLikes(char** genres, long int* likes, int size, int age){
    UserLikes* userLikes = (UserLikes*)malloc(sizeof(UserLikes));

    userLikes->genres = (char**)malloc(size * sizeof(char*));
    for(int i = 0; i < size; i++) userLikes -> genres[i] = strdup(genres[i]);

    userLikes->likes = (long int*)malloc(size * sizeof(long int));
    memcpy(userLikes->likes, likes, size * sizeof(long int));

    userLikes -> size = size;
    userLikes -> age = age;

    return userLikes;
}

// Função que retorna uma cópia do array de generos da estrutura de likes
char** getUserLikesArrayGenres(UserLikes* userLikes){
    if(!userLikes || !userLikes->genres) return NULL;

    if(userLikes->size <= 0) return NULL;

    char** genres_copy = malloc(userLikes->size * sizeof(char*));
    if(!genres_copy) return NULL; 

    // Copia de cada genero para o array
    for(int i = 0; i < userLikes->size; i++){
        genres_copy[i] = strdup(userLikes->genres[i]);
        if(!genres_copy[i]){
            // No caso de falhar a alocacao de memoria
            for (int j = 0; j < i; j++){
                free(genres_copy[j]);
            }
            free(genres_copy);
            return NULL;
        }
    }

    return genres_copy;
}

// Função que retorna uma cópia do array de likes da estrutura de likes
long int* getUserLikesArrayLikes(UserLikes* userLikes){
    if(userLikes -> size > 0){
        long int* cpy = malloc(userLikes -> size * sizeof(long int));
        memcpy(cpy, userLikes -> likes, userLikes -> size * sizeof(long int));
        return cpy;
    }
    return NULL;
}

// Função que retorna o tamanho dos arrays da estrutura de likes
int getUserLikesSizeArray(UserLikes* userLikes){
    return userLikes -> size;
}

// Função que retorna o apontador da idade da estrutura de likes
int* getUserLikesAge(UserLikes* userLikes){
    return userLikes->age ? &(userLikes -> age) : NULL;
}

// Função que retorna a idade da estrutura de likes
int getUserLikesAgeInt(UserLikes* userLikes){
    return userLikes->age;
}

// Função que altera o array de generos da estrutura de likes
void setUserLikesArrayGenres(UserLikes* userLikes, char** newGenres, int newSize){
    if(!userLikes) return;

    // Libertar a memoria do array existente na estrutura
    if(userLikes->genres){
        for(int i = 0; i < userLikes->size; i++){
            free(userLikes->genres[i]);
        }
        free(userLikes->genres);
    }

    if(newSize > 0 && newGenres){
        userLikes->genres = malloc(newSize * sizeof(char*));
        if(!userLikes->genres){
            fprintf(stderr, "Erro de alocação de memória para gêneros\n");
            userLikes->size = 0;
            return;
        }
        for(int i = 0; i < newSize; i++){
            userLikes->genres[i] = strdup(newGenres[i]);
            if(!userLikes->genres[i]){
                fprintf(stderr, "Erro de alocação de memória para gênero\n");
                for (int j = 0; j < i; j++){
                    free(userLikes->genres[j]);
                }
                free(userLikes->genres);
                userLikes->genres = NULL;
                userLikes->size = 0;
                return;
            }
        }
        userLikes->size = newSize;
    }else{
        // Caso o tamanho ou array seja inválido
        userLikes->genres = NULL;
        userLikes->size = 0;
    }
}

// Função que altera o array de likes da estrutura de likes
void setUserLikesArrayLikes(UserLikes* userLikes, long int* newLikes, int newSize){
    if(!userLikes) return;

    // Liberar memória existente
    if(userLikes->likes){
        free(userLikes->likes);
    }

    if(newSize > 0 && newLikes){
        userLikes->likes = malloc(newSize * sizeof(long int));
        if(!userLikes->likes){
            fprintf(stderr, "Erro de alocação de memória para likes\n");
            userLikes->size = 0;
            return;
        }
        memcpy(userLikes->likes, newLikes, newSize * sizeof(long int));
        userLikes->size = newSize;
    } else {
        // Caso o tamanho ou array seja inválido
        userLikes->likes = NULL;
        userLikes->size = 0;
    }
}

// Função auxiliar para fazer free da estrutura de likes 
void freeUserLikes(UserLikes* userLikes){
    if(!userLikes) return;

    for(int i = 0; i < userLikes -> size; i++)
        free(userLikes -> genres[i]); // Free a cada genero dentro do array

    free(userLikes -> genres);   // Free do array de generos
    free(userLikes -> likes);    // Free do array de likes
    free(userLikes);             // Free da propria estrutura
}