#include "../../include/gestores/gestor_artist.h"

//estrutura do gestor de artistas.
struct gestor_artist{
    GHashTable* table;
    GHashTable* num_albums_table;
    GHashTable* reps_musics_table;
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
    gestorArtist -> num_albums_table = g_hash_table_new(g_direct_hash, g_direct_equal);
    gestorArtist -> reps_musics_table = g_hash_table_new(g_direct_hash, g_direct_equal);
    if(!gestorArtist -> table || !gestorArtist -> num_albums_table || !gestorArtist -> reps_musics_table){
        perror("Falha ao criar tabelas de hashing de artistas.\n");
        if(gestorArtist -> table){
            g_hash_table_destroy(gestorArtist -> table);
        }
        if(gestorArtist -> num_albums_table){
            g_hash_table_destroy(gestorArtist -> num_albums_table);
        }
        if(gestorArtist -> reps_musics_table){
            g_hash_table_destroy(gestorArtist -> reps_musics_table);
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
        if(gestorArtist -> num_albums_table){
            g_hash_table_foreach_remove(gestorArtist -> num_albums_table,freeAlbumCountInTable,NULL);
            g_hash_table_destroy(gestorArtist -> num_albums_table);
        }
        if(gestorArtist -> reps_musics_table){
            g_hash_table_foreach_remove(gestorArtist -> reps_musics_table,freeMusicRepsInTable,NULL);
            g_hash_table_destroy(gestorArtist -> reps_musics_table);
        }
        free(gestorArtist);
    }
}

// função que adiciona um artista e o número de álbuns à tabela de contador de álbuns.
void addIndividualAlbumCount(GestorArtist* gestorArtist, long int artist_id, int count){
    if(gestorArtist && gestorArtist->num_albums_table){
        // Criar um ponteiro para o valor de tipo int
        int* count_ptr = malloc(sizeof(int));
        if(!count_ptr){
            // Falha ao alocar memória
            return;
        }
        *count_ptr = count;

        // Inserir o ponteiro na tabela hash
        g_hash_table_insert(gestorArtist->num_albums_table, GINT_TO_POINTER(artist_id), count_ptr);
    }
}

// Função que atualiza o número de álbuns de um artista na tabela de contador de álbuns.
void updateIndividualAlbumCount(GestorArtist* gestorArtist, long int artist_id, int count){
    if(!gestorArtist || !gestorArtist->num_albums_table){
        fprintf(stderr, "Erro: Tabela de álbuns não inicializada ou gestor inválido.\n");
        return;
    }

    // Busca pelo número de álbuns do artista
    int* count_ptr = (int*)g_hash_table_lookup(gestorArtist->num_albums_table, GINT_TO_POINTER(artist_id));
    if(count_ptr){
        *count_ptr = count; // Atualiza o valor existente
    }else{
        // Caso a chave não exista, aloca memória e adiciona à tabela
        int* value = malloc(sizeof(int));
        if(!value){
            perror("Erro ao alocar memória para o valor.");
            return;
        }
        *value = count;

        // Insere a nova chave e valor na tabela
        g_hash_table_insert(gestorArtist->num_albums_table, GINT_TO_POINTER(artist_id), value);
    }
}

// Função que retorna o número de álbuns de um artista na tabela de contador de álbuns.
int getIndividualAlbumCount(GestorArtist* gestorArtist, long int artist_id){
    if (!gestorArtist || !gestorArtist->num_albums_table){
        printf("Erro: gestorArtist ou num_albums_table não inicializado.\n");
        return 0;
    }

    // Procurar na tabela hash com a chave artist_id
    int* count_ptr = (int*)g_hash_table_lookup(gestorArtist->num_albums_table, GINT_TO_POINTER(artist_id));
    // Verifique se count_ptr não é NULL
    if(count_ptr){
        return *count_ptr;
    }else{
        printf("Chave não encontrada, retornando 0.\n");
        return 0;
    }
}

// Função que remove um artista da tabela de contador de álbuns.
void removeIndividualAlbumCount(GestorArtist* gestorArtist, long int artist_id){
    if(gestorArtist && gestorArtist->num_albums_table){
        g_hash_table_remove(gestorArtist->num_albums_table, GINT_TO_POINTER(artist_id));
    }
}

// Função para liberar a memória alocada para os artistas na tabela de contador de álbuns.
void freeAlbumCountInTable(gpointer key, gpointer value, gpointer user_data){
    free(value);  // Libera a memória alocada para o valor
}

// Função que adiciona um artista e o número de reproduções à tabela de músicas.
void addMusicReps(GestorArtist* gestorArtist, long int artist_id, int reps){
    if(gestorArtist && gestorArtist->reps_musics_table){
        int* reps = malloc(sizeof(int));
        if(!reps){
            perror("Erro ao alocar memória para o número de reproduções da música.\n");
            return;
        }
        *reps = 0;
        g_hash_table_insert(gestorArtist->reps_musics_table, GINT_TO_POINTER(artist_id), reps);
    }
}

// Função que atualiza o número de reproduções de um artista na tabela de músicas.
void updateMusicReps(GestorArtist* gestorArtist, long int artist_id, int reps){
    if(gestorArtist && gestorArtist->reps_musics_table){
        int* reps_ptr = (int*)g_hash_table_lookup(gestorArtist->reps_musics_table, GINT_TO_POINTER(artist_id));
        if(reps_ptr){
            *reps_ptr = reps;
        }else{
            addMusicReps(gestorArtist, artist_id, reps);
        }
    }
}

// Função que retorna o número de reproduções de um artista na tabela de músicas.
int getMusicReps(GestorArtist* gestorArtist, long int artist_id){
    if(gestorArtist && gestorArtist->reps_musics_table){
        int* reps_ptr = (int*)g_hash_table_lookup(gestorArtist->reps_musics_table, GINT_TO_POINTER(artist_id));
        if(reps_ptr){
            return *reps_ptr;
        }
    }
    return 0;
}

// Função que remove um artista da tabela de músicas.
void removeMusicReps(GestorArtist* gestorArtist, long int artist_id){
    if(gestorArtist && gestorArtist->reps_musics_table){
        g_hash_table_remove(gestorArtist->reps_musics_table, GINT_TO_POINTER(artist_id));
    }
}

// Função que libera a memória alocada para os artistas na tabela de músicas.
void freeMusicRepsInTable(gpointer key, gpointer value, gpointer user_data){
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

// Função para obter o coletivo de artistas que contém um artista individual.
GList* getCollectiveArtistsContaining(GestorArtist* gestorArtist, long int individual_artist_id) {
    if(!gestorArtist){
        return NULL;
    }

    GList* collective_ids = NULL; // Lista de IDs dos coletivos que contêm o artista individual

    GHashTableIter iter;
    gpointer key, value;

    // Inicializar o iterador para percorrer os artistas no gestor
    g_hash_table_iter_init(&iter, gestorArtist->table);
    while(g_hash_table_iter_next(&iter, &key, &value)){
        Artist* artist = (Artist*)value;
        ArtistType type = getArtistType(artist);

        // Verificar se o artista é do tipo coletivo
        if(type == GRUPO){
            long int collective_id = *(long int*)key;
            long int* constituents = getArtistIdConstituent(artist); // Lista de membros do coletivo
            int num_constituents = getArtistNumConstituent(artist); // Número de membros do coletivo

            // Verificar se o ID do artista individual está na lista de membros
            for (int i = 0; i < num_constituents; i++) {
                if (constituents[i] == individual_artist_id) {
                    // Adicionar o ID do coletivo à lista de resultados
                    collective_ids = g_list_prepend(collective_ids, (gpointer)(long)collective_id);
                    break; // Não precisamos continuar verificando este coletivo
                }
            }
            free(constituents); // Liberar a memória alocada para os constituintes
        }
    }

    return collective_ids; // Retorna a lista de IDs dos coletivos
}