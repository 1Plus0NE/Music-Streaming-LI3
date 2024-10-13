#include "queries.h"
#include "../gestores/gestor_user.h"
#include "../gestores/gestor_music.h"
#include "../gestores/gestor_artist.h"
#include <stdio.h>
#include <glib.h>

// função que responde á query1.
void query1(int user_id, GHashTable* user_table, FILE* output_file){
    User* user = searchUser(user_table, user_id);

    if(!user){
        fprintf(output_file, "\n");
        return 0;
    }

    int age = calculaIdade(getUserBirthDate(user));

    fprintf(output_file, "%s;%s;%s;%d;%s\n", getUserEmail(user), getUserFirstName(user), getUserLastName(user), age, getUserCountry(user));
}