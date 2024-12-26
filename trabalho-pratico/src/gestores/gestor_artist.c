#include "../../include/gestores/gestor_artist.h"

//estrutura do gestor de artistas.
struct gestor_artist {
    GHashTable* table;
    GHashTable* recipe_table;
};

// função para criar uma tabela de artistas.
GestorArtist* createGestorArtist(){
    GestorArtist* gestorArtist = malloc(sizeof(GestorArtist));
    if (gestorArtist == NULL) {
        perror("Falha ao criar a struct GestorArtist.\n");
        free(gestorArtist);
        return NULL;
    }

    gestorArtist -> table = g_hash_table_new(g_int_hash, g_int_equal);
    gestorArtist -> recipe_table = g_hash_table_new(g_int_hash, g_int_equal);
    if(!gestorArtist -> table || !gestorArtist -> recipe_table){
        perror("Falha ao criar tabelas de hashing de artistas.\n");
        if(gestorArtist -> table){
            g_hash_table_destroy(gestorArtist -> table);
        }
        if(gestorArtist -> recipe_table){
            g_hash_table_destroy(gestorArtist -> recipe_table);
        }
        free(gestorArtist);
        return NULL;
    }
    return gestorArtist;
}

// função que adiciona um artista á tabela de artistas.
void addArtist(GestorArtist* gestorArtist, Artist* artist){
    if(gestorArtist && gestorArtist -> table){
        g_hash_table_insert(gestorArtist -> table, getArtistId(artist), artist);
    }
}

// função que remove um artista da tabela de artistas.
void removeArtist(GestorArtist* gestorArtist, long int id){
    if(gestorArtist && gestorArtist -> table){
        g_hash_table_remove(gestorArtist -> table, &id);
    }
}

// função que encontra um artista pelo id na tabela.
Artist* searchArtist(GestorArtist* gestorArtist, long int id){
    if(gestorArtist && gestorArtist -> table){
        return (Artist*) g_hash_table_lookup(gestorArtist -> table, &id);
    }
    return NULL;
}

// função que aplica uma função callback em cada item da tabela de artistas.
void foreachArtist(GestorArtist* gestorArtist, GHFunc func, gpointer user_data) {
    if (gestorArtist && gestorArtist->table && func){
        g_hash_table_foreach(gestorArtist->table, func, user_data);
    }
}

// função que libera a memória alocada para a tabela de artistas.
void freeGestorArtist(GestorArtist* gestorArtist){
    if(gestorArtist){
        if(gestorArtist -> table){
            g_hash_table_foreach_remove(gestorArtist -> table,freeArtistInTable,NULL);
            g_hash_table_destroy(gestorArtist -> table);
        }
        if(gestorArtist -> recipe_table){
            g_hash_table_foreach_remove(gestorArtist -> recipe_table,freeArtistRecipeInTable,NULL);
            g_hash_table_destroy(gestorArtist -> recipe_table);
        }
        free(gestorArtist);
    }
}

// função que adiciona um artista e a sua receita à tabela de receitas.
void addArtistRecipe(GestorArtist* gestorArtist, long int artist_id, float recipe){
    if(gestorArtist && gestorArtist -> recipe_table){
        float* recipe_ptr = malloc(sizeof(float));
        if(!recipe_ptr){
            perror("Erro ao alocar memória para a receita do artista.\n");
            return;
        }
        *recipe_ptr = recipe;
        g_hash_table_insert(gestorArtist -> recipe_table, GINT_TO_POINTER(artist_id), recipe_ptr);
    }
}

// função que atualiza a receita de um artista na tabela de receitas.
void updateArtistRecipe(GestorArtist* gestorArtist, long int artist_id, float recipe){
    if(gestorArtist && gestorArtist -> recipe_table){
        float* recipe_ptr = (float*)g_hash_table_lookup(gestorArtist->recipe_table, GINT_TO_POINTER(artist_id));
        if(recipe_ptr){
            *recipe_ptr = recipe;
        }else{
            addArtistRecipe(gestorArtist, artist_id, recipe);
        }
    }
}

// função que retorna a receita de um artista na tabela de receitas.
float getArtistRecipe(GestorArtist* gestorArtist, long int artist_id){
    if(gestorArtist && gestorArtist -> recipe_table){
        float* recipe_ptr = (float*)g_hash_table_lookup(gestorArtist->recipe_table, GINT_TO_POINTER(artist_id));
        if(recipe_ptr){
            return *recipe_ptr;
        }
    }
    return 0.0f;
}

// função que remove um artista da tabela de receitas.
void removeArtistRecipe(GestorArtist* gestorArtist, long int artist_id){
    if(gestorArtist && gestorArtist -> recipe_table){
        g_hash_table_remove(gestorArtist -> recipe_table, GINT_TO_POINTER(artist_id));
    }
}

// Função para liberar a memória alocada para os artistas na tabela.
void freeArtistRecipeInTable(gpointer key, gpointer value, gpointer user_data){
    free(value);
}

// Função que verifica se a chave existe na tabela de artistas.
bool containsArtistID(GestorArtist* gestorArtist, long int id){
    if(gestorArtist && gestorArtist -> table){
        return g_hash_table_contains(gestorArtist -> table, &id);
    }
    return false;
}

// Função que verifica se todos a lista de ids existe na tabela de artistas.
bool validateArtistIDs(GestorArtist* gestorArtist, long int *idList, int N){
    if(gestorArtist && gestorArtist -> table){
        for(int i = 0; i < N; i++){
            if(!containsArtistID(gestorArtist, idList[i])){
                return false;
            }
        }
        return true;
    }
    return false;
}

// Função que percorre a Hash Table e insere cada artista na lista Discography
Discography* fillWithArtists(GestorArtist* gestorArtist, Discography* disco){
    if(gestorArtist && gestorArtist -> table){
        foreachArtist(gestorArtist, artistFromTableToLL, &disco);
    }
    return disco;
}

// Função  para cada item da Hash Table
void artistFromTableToLL(G_GNUC_UNUSED gpointer artistId, gpointer artistData, gpointer discoPtr){
    
    Artist* artist = (Artist*)artistData;
    Discography** disco = (Discography**)discoPtr;
    long int* idPtr = getArtistId(artist);
    long int id;
    if (idPtr) {
        id = *idPtr; // Transforma o ponteiro em long int
    } else {
        id = 0;  //  Não deve acontecer
    }
    //long int id = (idPtr != NULL) ? *idPtr : -1; //Transformar o ponteiro em long int
    char* name = getArtistName(artist);
    char* country = getArtistCountry(artist);
    ArtistType type = getArtistType(artist);
    
    //*disco = artistInsert(*disco, id, name, country, type);
    artistInsert(disco, id, name, country, type);
    free(name);
    free(country);
}