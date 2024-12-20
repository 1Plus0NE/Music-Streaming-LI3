#include "../../include/parser/parser_user.h"
#define MAX_FILENAME 1024
#define MAX_LINE 2048

// Função de verificação da validade de um user
int userLineVerify(char *line, GestorMusic* gestorMusic){
    //char *info = strsep(&line, ";");
    char *info=NULL;
    long int* musicsIds;
    int N;

    for(int i = 0; i <= 7; i++){
        info=strsep(&line, ";");
        if(info){
            switch(i){
                case 1:
                    info = remove_aspas(info);
                    if(emailVerify(info)!=0){
                        free(info);
                        return 1;
                    }
                    free(info);
                    break;
                case 4:
                    info = remove_aspas(info);
                    if(birthDateVerify(info)!=0){
                        free(info);
                        return 1;
                    }
                    free(info);
                    break;
                case 6:
                    info = remove_aspas(info);
                    if(strcmp("premium",info)!=0 && strcmp("normal",info)!=0){
                        free(info);
                        return 1;
                    }
                    free(info);
                    break;
                case 7:
                    info = remove_aspas(strsep(&info,"\n"));
                    musicsIds=convertID(info,&N);
                    if(!validateMusicId(gestorMusic, musicsIds, N)){
                        free(musicsIds);
                        free(info);
                        return 1;
                    }
                    free(musicsIds);
                    free(info);
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}

// Função que dá parse ao ficheiro de utilizadores.
void parse_user(char* path, GestorUser* gestorUser, GestorMusic* gestorMusic){
    parse_csv(path, "users.csv", gestorUser, gestorMusic, process_user_line, 3);
}

// função para processar uma linha de utilizador.
void process_user_line(char* line, void* gestor, void* aux_data){
    GestorUser* gestorUser = (GestorUser*)gestor;
    GestorMusic* gestorMusic = (GestorMusic*)aux_data;

    char* tmp_line = strdup(line);
    char* original_line = tmp_line;
    char *username, *email, *first_name, *last_name, *birth_date, *country, *liked_musics_id;
    char* tmp_sub;
    SubscriptionType subscription;
    long int* liked_musics_id_converted = NULL;
    int num_liked_musics = 0;

    // validações.
    if(userLineVerify(line, gestorMusic) != 0){
        writeErrors(line, 3);
        free(tmp_line);
        return;
    }

    username = remove_aspas(strsep(&tmp_line, ";"));
    email = remove_aspas(strsep(&tmp_line, ";"));
    first_name = remove_aspas(strsep(&tmp_line, ";"));
    last_name = remove_aspas(strsep(&tmp_line, ";"));
    birth_date = remove_aspas(strsep(&tmp_line, ";"));
    country = remove_aspas(strsep(&tmp_line, ";"));
    tmp_sub = remove_aspas(strsep(&tmp_line, ";"));
    subscription = stringToSubscriptionType(tmp_sub);
    liked_musics_id = remove_aspas(strsep(&tmp_line, "\n"));
    liked_musics_id_converted = convertID(liked_musics_id, &num_liked_musics);

    User* u = createUser(username, email, first_name, last_name, birth_date, country, subscription, liked_musics_id_converted, num_liked_musics);
    addUser(gestorUser, u);

    // verificar os likes do utilizador.
    char** genres = NULL;
    long int* genre_likes = NULL;
    int genre_count = 0;
    int age = calculaIdade(birth_date);

    countUserLikedMusics(gestorMusic, &genres, &genre_likes, &genre_count, liked_musics_id_converted, num_liked_musics);
    addUserLikes(gestorUser, genres, genre_likes, genre_count, age);

    for (int i = 0; i < genre_count; i++) free(genres[i]);
    free(genres);
    free(genre_likes);
    free(liked_musics_id_converted);
    free(username);
    free(email);
    free(first_name);
    free(last_name);
    free(birth_date);
    free(country);
    free(tmp_sub);
    free(liked_musics_id);
    free(original_line);
}