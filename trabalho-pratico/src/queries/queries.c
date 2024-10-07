#include "queries.h"
#include "gestor_artist.h"
#include "gestor_user.h"
#include "gestor_music.h"
#include <stdio.h>

// função que calcula a idade através de uma data de nascimento dada como argumento.
int calculaIdade(char* birthdate){
    char* currentDate = "2024/09/09";
    int birthYear, birthMonth, birthDay, currentYear, currentMonth, currentDay;

    sscanf(birthdate, "%d/%d/%d", &birthYear, &birthMonth, &birthDay);
    sscanf(currentDate, "%d/%d/%d", &currentYear, &currentMonth, &currentDay);

    int age = currentYear - birthYear;

    if(currentMonth < birthMonth || (currentMonth == birthMonth && currentDay < birthDay)){
        age--;
    }

    return age;
}

// função que responde á query1.
void query1(int user_id, FILE* output_file){
    User* user = searchUser(user_table, user_id);

    if(!user){
        fprintf(output_file, "\n");
        return 0;
    }

    int age = calculaIdade(user -> birthdate, "2024-09-09");

    fprintf(output_file, "%s;%s;%s;%d;%s\n", user -> email, user -> first_name, user -> last_name, age, user -> country);
}