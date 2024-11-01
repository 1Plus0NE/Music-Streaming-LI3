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

// Função para a 2ª query sem especificação de país
void query2(int nArtists, GHashTable* artistTable, GHashTable* musicTable, FILE* output){
    
}

// Função para a 2ª query, com especificação de país
void query2b(int nArtists, char* country, GHashTable* artistTable, GHashTable* musicTable, FILE* output){

}

void query3(int ageMin, int ageMax, GHashTable* userTable, GHashTable* musicTable,FILE* output){

}