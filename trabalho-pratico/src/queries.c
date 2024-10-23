#include "../include/queries.h"

// função que responde á query1.
void query1(char* user_username, GHashTable* user_table, FILE* output_file){
    User* user = searchUser(user_table, user_username);

    if(!user){
        fprintf(output_file, "\n");
    }

    int age = calculaIdade(getUserBirthDate(user));

    fprintf(output_file, "%s;%s;%s;%d;%s\n", getUserEmail(user), getUserFirstName(user), getUserLastName(user), age, getUserCountry(user));
    
    freeUser(user);
}

// Query que devolve os N artistas com maior discografia
/*void query2Single(int N, GHashTable* artist_table, FILE* output_file){
    
}

void query2Country(int N, char *country, GHashTable* artist_table, FILE* output_file){
    while(N>0){
        discografia(artista) = somaDuracaoMusicas(id artista)
    }
}*/