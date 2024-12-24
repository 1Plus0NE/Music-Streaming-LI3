#include "../../include/gestores/gestor_artist.h"

//estrutura do gestor de artistas.
struct gestor_artist {
    GHashTable* table;
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
    if(gestorArtist -> table == NULL){
        perror("Falha ao criar a tabela de hashing de artistas.\n");
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
        free(gestorArtist);
    }
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

// Função que retorna um GPtrArray com os coletivos de um artista
GPtrArray* getArtistCollectives(GestorArtist* gestorArtist, long int artist_id){
    GPtrArray* collectives = g_ptr_array_new_with_free_func(free);

    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, gestorArtist -> table);
    while(g_hash_table_iter_next(&iter, &key, &value)){
        Artist* artist = (Artist*)value;
        int* artist_id_constituent = getArtistIdConstituent(artist);
        int num_constituents = getArtistNumConstituent(artist);
        // Verifica se é um coletivo (GRUPO)
        if(getArtistType(artist) == GRUPO){
            for(int i = 0; i < num_constituents; i++){
                if(artist_id_constituent[i] == artist_id){
                    // Adiciona o ID do coletivo ao GPtrArray
                    long int* collective_id = malloc(sizeof(long int));
                    if(!collective_id){
                        fprintf(stderr, "Erro ao alocar memória para o ID do coletivo\n");
                        g_ptr_array_free(collectives, TRUE);
                        exit(EXIT_FAILURE);
                    }
                    *collective_id = getArtistId(artist);
                    g_ptr_array_add(collectives, collective_id);
                    break;
                }
            }
        }
    }

    return collectives;
}

// Função que retorna o número de constituintes de um coletivo
int getNumConstituents(GestorArtist* gestorArtist, long int artist_id){
    Artist* artist = (Artist*)g_hash_table_lookup(gestorArtist->table, &artist_id);
    if(!artist){
        fprintf(stderr, "Artista com ID %ld não encontrado\n", artist_id);
        return 0;
    }

    if(getArtistType(artist) != GRUPO){
        fprintf(stderr, "Artista com ID %ld não é um coletivo\n", artist_id);
        return 0;
    }
    
    return getArtistNumConstituent(artist);
}