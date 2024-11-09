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
void query3(int ageMin, int ageMax, GestorUser* gestorUser, GestorMusic* gestorMusic, FILE* output){
    
    if(ageMin == 100 || ageMax == 0){
        fprintf(output, "\n");
        return;
    }

    // Para iterar os users
    UserIterator* user_iterator = createUserIterator(gestorUser);
    User* user = NULL;
    // Variaveis para dar store aos valores
    char *genres[MAX_GENRES];
    long int genre_likes[MAX_GENRES] = {0};
    int genre_count = 0;
    long int* likedMusics;
    int numLikedMusics = 0;
    char* age_str;
    // Flag para caso os intervalos de idades sejam validos mas não haja users compreendidos nessas idades
    int flag = 0;

    // Iterar pela table de users
    while((user = getNextUser(user_iterator)) != NULL){
        age_str = getUserBirthDate(user);
        if(isAgeInRange(age_str, ageMin, ageMax)){
            flag = 1;
            likedMusics = getUserLikedMusics(user);
            numLikedMusics = getUserNumLikedMusics(user);
            countUserLikedMusics(gestorMusic, genres, genre_likes, &genre_count, likedMusics, numLikedMusics);
        }
    }

    freeUserIterator(user_iterator); // já não precisamos mais do iterator
    // No caso de nao termos encontrado um user na range de idades
    if(!flag){
        fprintf(output, "\n");
        return;
    }

    sortGenresByLikes(genres, genre_likes, genre_count);
    // Escrever no ficheiro o resultado final
    for(int i = 0; i < MAX_GENRES; i++){
        fprintf(output, "%s;%ld\n", genres[i], genre_likes[i]);  
        if(genres[i])free(genres[i]);
    }

}