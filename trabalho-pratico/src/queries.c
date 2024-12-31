#include "../include/queries.h"
#define MAX_GENRES 10

// função que responde á query1.
void query1(char* id_str, GestorUser* gestorUser, GestorArtist* gestorArtist, char delimiter, FILE* output_file){
    if(id_str[0] == 'U'){
        User* user = searchUser(gestorUser, id_str);
        if(user){
            char* email = getUserEmail(user);
            char* first_name = getUserFirstName(user);
            char* last_name = getUserLastName(user);
            char* age_str = getUserBirthDate(user);
            int age = calculaIdade(age_str);
            char* country = getUserCountry(user);
            char* age_buffer = intToString(age);

            genericOutputWriter(output_file, delimiter, email, first_name, last_name, age_buffer, country, NULL);
            free(email);
            free(first_name);
            free(last_name);
            free(age_str);
            free(country);
            free(age_buffer);
            return;
        }
    }else if (id_str[0] == 'A'){
        // Ignora o prefixo 'A' e converte para long
        char* endptr;
        long int id = strtol(id_str + 1, &endptr, 10);
        // Validação do ID convertido
        if(*endptr != '\0'){
            fprintf(stderr, "Erro: ID de artista inválido (%s).\n", id_str);
            fprintf(output_file, "\n");
            return;
        }

        Artist* artist = searchArtist(gestorArtist, id);
        if(artist){
            char* name = getArtistName(artist);
            ArtistType type = getArtistType(artist);
            char* typeInChar = typeToString(type);
            char* country = getArtistCountry(artist);
            int num_albuns = getIndividualAlbumCount(gestorArtist, id);
            int reps = getMusicReps(gestorArtist, id);
            float total_recipe = 0.00;
            if (type == INDIVIDUAL) {
                // Obter os coletivos nos quais o artista individual está envolvido
                GList* collectives = getCollectiveArtistsContaining(gestorArtist, id);
                // Calcular a receita própria do artista individual
                float recipe_per_stream = getArtistRecipePerStream(artist);
                total_recipe += reps * recipe_per_stream;  // Receita do artista individual própria

                for (GList* node = collectives; node != NULL; node = node->next) {
                    long int collective_id = (long int)(node->data); // Evitar truncamento
                    Artist* collective = searchArtist(gestorArtist, collective_id);

                    if (collective) {
                        int collective_reps = getMusicReps(gestorArtist, collective_id);  // Reproduções do coletivo
                        float collective_recipe_per_stream = getArtistRecipePerStream(collective);
                        int num_members = getArtistNumConstituent(collective);  // Número de membros do coletivo
                        if (num_members > 0) { // Garantir que não haja divisão por zero
                            // Calcular a receita proporcional do coletivo para o artista individual
                            float collective_recipe = (collective_reps * collective_recipe_per_stream) / num_members;
                            total_recipe += collective_recipe;
                        }
                    }
                }
                g_list_free(collectives); // Liberar lista de coletivos
            } else if (type == GRUPO) {
                // Para artistas do tipo GRUPO, a receita é calculada normalmente
                float recipe_per_stream = getArtistRecipePerStream(artist);
                total_recipe = reps * recipe_per_stream;
            }

            // Converter número de álbuns para string
            char* num_albums_str = intToString(num_albuns);
            char* recipe_str = floatToString(total_recipe, 2);

            genericOutputWriter(output_file, delimiter, name, typeInChar, country, num_albums_str, recipe_str, NULL);
            free(name);
            free(country);
            free(typeInChar);
            free(num_albums_str);
            return;
        }
    }
    // Caso o ID não seja encontrado
    fprintf(output_file, "\n");
}

// Função para a Query 2
void query2(int nArtists, char* country, Discography* disco, char delimiter, FILE* output){
    Discography* head = disco;

    if(nArtists==0) fprintf(output, "\n"); //Caso de ficheiro "vazio"
    
    for(int i=0; i<nArtists && head!=NULL; i++){
        char* countryD = getDiscographyCountry(head);
        ArtistType type = getDiscographyType(head);
        
        //Quando não há expecificação de país, ou se encontra no país pretendido
        if(country == NULL || strcmp(country, countryD) == 0){
            int duration = getDiscographyDuration(head);
            char* time = secondsToString(duration); // Transformação em formato char*
            char* typeInChar = typeToString(type); // Transformação em formato char*
            char* name = getDiscographyName(head);
        
            genericOutputWriter(output, delimiter, name, typeInChar, time, countryD, NULL);

            free(time);
            free(typeInChar);
            free(name);

            head = getDiscographyNext(head);
        }

        //Caso chegue ao ultimo elemento de discografia
        else if(getDiscographyNext(head) == NULL){
            //fprintf(output, "\n");
            head = getDiscographyNext(head);
        }

        //Caso continue a busca pelo artista do país
        else{
            head = getDiscographyNext(head);
            i--; // Mantém o contador para processar o próximo artista
        }      
        free(countryD);  
    }
}

// Função responsável da query 3
void query3(int ageMin, int ageMax, GestorUser* gestorUser, char delimiter, FILE* output){
    
    if(ageMin == 100 || ageMax == 0){
        fprintf(output, "\n");
        return;
    }

    // Variaveis para dar store aos valores
    char** genres = NULL;
    long int* likes = NULL;
    int size = 0;
    // Flag para caso os intervalos de idades sejam validos mas não haja users compreendidos nessas idades
    int flag = 0;
    GPtrArray* userLikesArr = getUserLikesArray(gestorUser);
    for(guint i = 0; i < userLikesArr->len; i++){
        UserLikes* userLikes = getUserLikeFromArray(gestorUser, i);
        int age = getUserLikesAgeInt(userLikes);
        if(isAgeInRange(age, ageMin, ageMax)){
            flag = 1;
            char** genresUL = getUserLikesArrayGenres(userLikes);
            long int* likesUL = getUserLikesArrayLikes(userLikes);
            int sizeUL = getUserLikesSizeArray(userLikes);
            updateGenresAndLikes(&genres, &likes, &size, genresUL, likesUL, sizeUL);
            for(int i = 0; i < sizeUL; i++) free(genresUL[i]); 
            free(genresUL);
            free(likesUL);
        }
    }
    // No caso de nao termos encontrado um user na range de idades
    if(!flag){
        fprintf(output, "\n");
        return;
    }
    sortGenresByLikes(genres, likes, size);
    char** like_strings = longArrayToStringArray(likes, size);
    // Escrever no ficheiro o resultado final
    for(int i = 0; i < size; i++){
        genericOutputWriter(output, delimiter, genres[i], like_strings[i], NULL);
    }
    free(likes);
    freeStringArray(like_strings, size);
    freeStringArray(genres, size);
}