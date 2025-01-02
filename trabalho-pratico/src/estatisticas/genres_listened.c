#include "../../include/estatisticas/genres_listened.h"

// Estrutura para organizar as musicas ouvidas de cada user
struct genres_listened{
    char* username;
    char** genres;
    int* listened;
    int size; // tamanho dos arrays
    int similarity; // parametro que irá ser calculado na query5 para a similaridade
};

// Função para criar uma estrutura de musicas ouvidas de um user
GenresListened* createGenresListened(char* username, char** genres, int* listened, int size){
    GenresListened* genresListened = (GenresListened*)malloc(sizeof(GenresListened));

    genresListened -> username = malloc(strlen(username) + 1);
    strcpy(genresListened -> username, username);

    genresListened->genres = (char**)malloc(size * sizeof(char*));
    for(int i = 0; i < size; i++) genresListened -> genres[i] = strdup(genres[i]);

    genresListened->listened = (int*)malloc(size * sizeof(int));
    memcpy(genresListened->listened, listened, size * sizeof(int));

    genresListened -> size = size;
    genresListened -> similarity = -1;

    return genresListened;
}

// Função que retorna uma cópia do username da estrutura de musicas ouvidas
char* getGenresListenedUsername(const GenresListened* genresListened){
    return genresListened -> username ? strdup(genresListened -> username) : NULL;
}

// Função que retorna uma cópia do array de generos da estrutura de musicas ouvidas
char** getGenresListenedArrayGenres(GenresListened* genresListened){
    if(!genresListened || !genresListened->genres) return NULL;

    if(genresListened->size <= 0) return NULL;

    char** genres_copy = malloc(genresListened->size * sizeof(char*));
    if(!genres_copy) return NULL; 

    // Copia de cada genero para o array
    for(int i = 0; i < genresListened->size; i++){
        genres_copy[i] = strdup(genresListened->genres[i]);
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

// Função que retorna uma cópia do array que representa quantas vezes foi ouvido X genero
int* getGenresListenedArrayListened(GenresListened* genresListened){
    if(genresListened -> size > 0){
        int* cpy = malloc(genresListened -> size * sizeof(int));
        memcpy(cpy, genresListened -> listened, genresListened -> size * sizeof(int));
        return cpy;
    }
    return NULL;
}

// Função que retorna o tamanho dos arrays da estrutura de musicas ouvidas
int getGenresListenedArraysSize(const GenresListened* genresListened){
    return genresListened -> size;
}

// Função que retorna a similaridade do utilizador da estrutura de musicas ouvidas
int getGenresListenedSimilarity(const GenresListened* genresListened){
    return genresListened -> similarity;
}

// Função que altera o array de generos da estrutura de musicas ouvidas
void setGenresListenedArrayGenres(GenresListened* genresListened, char** newGenres, int newSize){
    if(!genresListened) return;

    // Libertar a memoria do array existente na estrutura
    if(genresListened->genres){
        for(int i = 0; i < genresListened->size; i++){
            free(genresListened->genres[i]);
        }
        free(genresListened->genres);
    }

    if(newSize > 0 && newGenres){
        genresListened->genres = malloc(newSize * sizeof(char*));
        if(!genresListened->genres){
            fprintf(stderr, "Erro de alocação de memória para gêneros\n");
            genresListened->size = 0;
            return;
        }
        for(int i = 0; i < newSize; i++){
            genresListened->genres[i] = strdup(newGenres[i]);
            if(!genresListened->genres[i]){
                fprintf(stderr, "Erro de alocação de memória para gênero\n");
                for(int j = 0; j < i; j++){
                    free(genresListened->genres[j]);
                }
                free(genresListened->genres);
                genresListened->genres = NULL;
                genresListened->size = 0;
                return;
            }
        }
        genresListened->size = newSize;
    }else{
        // Caso o tamanho ou array seja inválido
        genresListened->genres = NULL;
        genresListened->size = 0;
    }
}

// Função que altera o array de musicas ouvidas 
void setGenresListenedArrayListened(GenresListened* genresListened, int* newListened, int newSize){
    if(!genresListened) return;

    // Libertar memória existente
    if(genresListened->listened){
        free(genresListened->listened);
    }

    if(newSize > 0 && newListened){
        genresListened->listened = malloc(newSize * sizeof(int));
        if(!genresListened->listened){
            fprintf(stderr, "Erro de alocação de memória para listened\n");
            genresListened->size = 0;
            return;
        }
        memcpy(genresListened->listened, newListened, newSize * sizeof(int));
        genresListened->size = newSize;
    } else {
        // Caso o tamanho ou array seja inválido
        genresListened->listened = NULL;
        genresListened->size = 0;
    }
}

// Função que altera a similaridade
void setSimilarityScore(GenresListened* genresListened, int newSimilarityScore){
    genresListened -> similarity = newSimilarityScore;
}

// Função auxiliar para fazer free da estrutura de musicas ouvidas
void freeGenresListened(GenresListened* genresListened){
    if(!genresListened) return;

    free(genresListened -> username);
    for(int i = 0; i < genresListened -> size; i++)
        free(genresListened -> genres[i]); // Free a cada genero dentro do array

    free(genresListened -> genres);   // Free do array de generos
    free(genresListened -> listened); // Free do array de musicas ouvidas
    free(genresListened);             // Free da propria estrutura
}

