#include "../include/queries.h"
#define MAX_GENRES 10

// função que responde á query1.
void query1(char* user_username, GestorUser* gestorUser, FILE* output_file){
    User* user = searchUser(gestorUser, user_username);

    if(!user){
        fprintf(output_file, "\n");
        return;
    }
    char* email = getUserEmail(user);
    char* first_name = getUserFirstName(user);
    char* last_name = getUserLastName(user);
    char* age_str = getUserBirthDate(user);
    int age = calculaIdade(age_str);
    char* country = getUserCountry(user);

    fprintf(output_file, "%s;%s;%s;%d;%s\n", email, first_name, last_name, age, country);
    free(email);
    free(first_name);
    free(last_name);
    free(age_str);
    free(country);
}

/* void query1_new(char* user_username, GestorUser* gestorUser, FILE* output_file){
    User* user = searchUser(gestorUser, user_username);

    if(user){
        char* email = getUserEmail(user);
        char* first_name = getUserFirstName(user);
        char* last_name = getUserLastName(user);
        char* birth_date = getUserBirthDate(user);
        int age = calculaIdade(birth_date);
        char* country = getUserCountry(user);

        fprintf(output_file, "%s;%s;%s;%d;%s\n", email, first_name, last_name, age, country);

        free(email);
        free(first_name);
        free(last_name);
        free(birth_date);
        free(country);
    }

    Artist* artist = searchArtist(gestorUser, user_username);
    if(artist){
        char* name = getArtistName(artist);
        ArtistType type = getArtistType(artist);
        char* type_str = typeToString(type);
        char* country = getArtistCountry(artist);
        double recipe_per_stream = getArtistRecipePerStream(artist);


        fprintf(output_file, "%s;%s;%s;%s;%s\n", name, country, start_date, end_date, typeInChar);

        free(name);
        free(country);
        free(start_date);
        free(end_date);
        free(typeInChar);
    }
    fprintf(output_file, "\n");
} */

// Results é necessário para escrever pela ordem pedida
// Função para a query 2
void query2(int nArtists, Discography* disco, FILE* output){
    Discography* head = disco;

    if(nArtists == 0) fprintf(output, "\n"); // Caso de ficheiro "vazio"
    for(int i=0; i<nArtists && head!=NULL; i++){
        int duration = getDiscographyDuration(head);
        ArtistType type = getDiscographyType(head);
        char* name = getDiscographyName(head);
        char* country = getDiscographyCountry(head);
        char* time = secondsToString(duration); // Transformação em formato char*
        char* typeInChar = typeToString(type); // Transformação em formato char*

        fprintf(output, "%s;%s;%s;%s\n", name, typeInChar, time, country);  
        
        free(time);
        free(typeInChar);
        free(name);
        free(country);

        head = getDiscographyNext(head);
    }
}

// Função para a query 2 com especificação do pais
void query2b(int nArtists, char* country, Discography* disco, FILE* output){
    Discography* head = disco;

    if(nArtists == 0) fprintf(output, "\n"); // Caso de ficheiro "vazio"
    for(int i=0; i<nArtists && head!=NULL; i++){
        char* countryD = getDiscographyCountry(head);
        ArtistType type = getDiscographyType(head);
        if(strcmp(countryD, country) == 0){ // Verificação do país do artista
            int duration = getDiscographyDuration(head);
            char* time = secondsToString(duration); // Transformação em formato char*
            char* typeInChar = typeToString(type); // Transformação em formato char*
            char* name = getDiscographyName(head);
        
            fprintf(output, "%s;%s;%s;%s\n", name, typeInChar, time, countryD);  
        
            free(time);
            free(typeInChar);
            free(name);

            head = getDiscographyNext(head); 
        }
        else if(getDiscographyNext(head) == NULL && i==0){ // Caso de ficheiro "vazio"
            fprintf(output, "\n");
            head = getDiscographyNext(head);
            i--; // Mantém o contador para processar o próximo artista
        }
        else{
            head = getDiscographyNext(head);
            i--; // Mantém o contador para processar o próximo artista
        }
        free(countryD);
    }
}

// Função responsável da query 3
void query3(int ageMin, int ageMax, GestorUser* gestorUser, FILE* output){
    
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
    // Escrever no ficheiro o resultado final
    for(int i = 0; i < size; i++){
        fprintf(output, "%s;%ld\n", genres[i], likes[i]);  
        if(genres[i])free(genres[i]);
    }
    free(genres);
    free(likes);
}