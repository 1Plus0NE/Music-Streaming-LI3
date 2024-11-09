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

// função para ler e fazer parse de um ficheiro CSV de artistas.
void parse_user(char* path, GestorUser* gestorUser, GestorMusic* gestorMusic){
    //variáveis para o parse
    FILE* users;
    char filename[MAX_FILENAME];
    char line[MAX_LINE];
    char original_line[MAX_LINE];
    char *tmp_oriLine=NULL;

    //argumentos para a struct de artistas
    char* username;
    char* email;
    char* first_name;
    char* last_name;
    char* birth_date;
    char* country;
    SubscriptionType subscription;
    char* liked_musics_id; // Para depois converter para long int
    long int* liked_musics_id_converted;
    int num_liked_musics=0;

    int parsed = 0;
    int erros = 0;

    snprintf(filename,MAX_FILENAME,"%s/users.csv", path);

    users = fopen(filename, "r");
    if(!users){
        perror("Erro ao abrir o ficheiro csv dos utilizadores.\n");
        exit(EXIT_FAILURE);
    }

    fgets(line, sizeof(line), users);

    while((fgets(line, sizeof(line), users) != NULL)){
        strcpy(original_line, line);
        //Apontadores para o strsep
        tmp_oriLine = original_line;

        // Antes da função atribuir valor as variaveis, verifica a sua validação
        if(userLineVerify(line, gestorMusic) == 0){
            // Trocar tmp_oriLine para original_line?
            username = remove_aspas(strsep(&tmp_oriLine, ";"));
            email = remove_aspas(strsep(&tmp_oriLine, ";"));
            first_name = remove_aspas(strsep(&tmp_oriLine,";"));
            last_name = remove_aspas(strsep(&tmp_oriLine,";"));
            birth_date = remove_aspas(strsep(&tmp_oriLine,";"));
            country = remove_aspas(strsep(&tmp_oriLine,";"));
            char* tmpSub = remove_aspas(strsep(&tmp_oriLine,";"));
            subscription = stringToSubscriptionType(tmpSub);
            //liked_musics_id_converted = convertID(remove_aspas(strsep(&tmp_oriLine,"\n")), &num_liked_musics);
            liked_musics_id = remove_aspas(strsep(&tmp_oriLine,"\n"));
            liked_musics_id_converted = convertID(liked_musics_id,&num_liked_musics);
            User* u = createUser(username, email, first_name, last_name, birth_date, country, subscription, liked_musics_id_converted, num_liked_musics);
            addUser(gestorUser, u);

            free(liked_musics_id_converted);
            free(liked_musics_id);
            free(username);
            free(email);
            free(first_name);
            free(last_name);
            free(birth_date);
            free(country);
            free(tmpSub);
            parsed++;
        }
        else{
            erros++;
            writeErrors(original_line, 3);
        } 

    }
    printf("Foram lidos %d dados e foram encontrados %d erros.\n", parsed, erros);

    fclose(users);
}