#include "../../include/parser/parser.h"
#define MAX_FILENAME 1024
#define MAX_LINE 2048
#define MAX_QUERYLINE 150
typedef void (*EntityProcessor)(char* line, void* gestor, void* aux_dataX, void* aux_dataY);

// Função principal de parse que chama os módulos de parse individualmente.
void parse_all(char* path, GestorArtist* gestorArtist, GestorMusic* gestorMusic, GestorUser* gestorUser, GestorAlbum* gestorAlbum, GestorHistory* gestorHistory){
    //parse de artistas
    parse_artist(path, gestorArtist);
    printf("Artists parsed!\n");

    //parse de albúns
    parse_album(path, gestorAlbum, gestorArtist);
    printf("Albums parsed!\n");

    //parse de músicas
    parse_music(path, gestorMusic, gestorArtist, gestorAlbum);
    printf("Musics parsed!\n");

    //parse de utilizadores
    parse_user(path, gestorUser, gestorMusic);
    printf("Users parsed!\n");

    //parse de históricos
    parse_history(path, gestorHistory, gestorMusic, gestorArtist);
    printf("History parsed!\n");

}

// função que faz parse de um csv.
void parse_csv(const char* path, const char* filename, void* gestor, void* aux_dataX, void* aux_dataY, EntityProcessor process_line, int error_code) {
    FILE* file;
    char full_path[MAX_FILENAME];
    char line[MAX_LINE];
    char original_line[MAX_LINE];

    snprintf(full_path, MAX_FILENAME, "%s/%s", path, filename);

    file = fopen(full_path, "r");
    if(!file){
        perror("Erro ao abrir o ficheiro csv.\n");
        exit(EXIT_FAILURE);
    }

    // ignorar a primeira linha(cabeçalho).
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) != NULL){
        strcpy(original_line, line);
        if(process_line){
            process_line(original_line, gestor, aux_dataX, aux_dataY);
        }else{
            writeErrors(original_line, error_code);
        }
    }

    fclose(file);
}

// Função dá parse as queries.
void parse_queries(char* path, GestorUser* gestorUser, GestorMusic* gestorMusic, GestorArtist* gestorArtist, GestorAlbum* gestorAlbum, GestorHistory* gestorHistory, int measure_flag){
    char line[MAX_QUERYLINE];
    char* linePtr=NULL;
    FILE* queries;
    FILE* outputQ1;
    FILE* outputQ2;
    FILE* outputQ3;
    FILE* outputQ5;
    FILE* outputQ6;
    int command = 0; // Para escrita individual de ficheiros de output
    char outputPath[MAX_FILENAME]; // Caminho para ficheiros de output individuais

    
    char* user; // Utilizador para a query 1
    int nArtists = 0; // Nº de artistas para a query 2
    char* country; // País para a query 2
    Discography* disco = NULL; // Discografia para a query 2
    int ageMin = 0; // Idade mínima para a query 3
    int ageMax = 0; // Idade máxima para a query 3
    
    // Variaveis utilizadas no calculo do tempo de execução de cada query
    struct timespec query_start, query_end;
    double total_time_query1 = 0;
    double total_time_query2 = 0;
    double total_time_query3 = 0;
    double query_elapsed;

    // Abertura ficheiro de input das queries
    queries = fopen(path, "r");
    if(!queries){
        perror("Erro ao abrir o ficheiro input das queries.\n");
        exit(EXIT_FAILURE);
    }

    // Discografia antes de resolver a Query2 
    disco = fillWithArtists(gestorArtist, disco);
    disco = updateArtistsDurationFromMusic(gestorMusic, disco);
 
    sortByDuration(&disco);
    // discografia pronta para a 2ª query

    // Leitura query a query
    int i=1; //Eliminar antes de submeter
    while(fgets(line, sizeof(line), queries) != NULL){ 

        linePtr = line;
        // Atualização do path para o ficheiro de output da query 
        command++;
        snprintf(outputPath, MAX_FILENAME, "resultados/command%d_output.txt", command);

        char delimiter = getDelimiter(line); // obter o delimitador que irá ser utilizado no writing
        // Identificação da Query
        switch(line[0]){
            case '1':{
                // Criação do ficheiro de output da query para argumento da função query1
                outputQ1 = fopen(outputPath, "w");
                if(!outputQ1){
                    perror("Erro ao criar o ficheiro de output da query 1.\n");
                    exit(EXIT_FAILURE);
                }
                // Tratamento da linha para a 1ª Query
                strsep(&linePtr, " "); // Ignora o id da Query e o espaço
                user = strsep(&linePtr, "\n");

                if(measure_flag) clock_gettime(CLOCK_REALTIME, &query_start);
                query1(user, gestorUser, gestorArtist, delimiter, outputQ1);
                if(measure_flag){
                    clock_gettime(CLOCK_REALTIME, &query_end);
                    query_elapsed = (query_end.tv_sec - query_start.tv_sec) +
                                    (query_end.tv_nsec - query_start.tv_nsec) / 1e9;
                    total_time_query1 += query_elapsed;
                }
                // Processo completo, fechar ficheiro
                fclose(outputQ1);
                break;
            }

            case '2':{
                outputQ2 = fopen(outputPath, "w");
                if(!outputQ2){
                    perror("Erro ao criar o ficheiro de output da query 2.\n");
                    exit(EXIT_FAILURE);
                }

                strsep(&linePtr, " ");
                nArtists = atoi(strsep(&linePtr, " ")); // Numero de artistas
                country = remove_aspas(strsep(&linePtr, "\n")); // País sem aspas || NULL

                if(measure_flag) clock_gettime(CLOCK_REALTIME, &query_start);

                query2(nArtists, country, disco, delimiter, outputQ2); // query 2 sem especificação de país

                if(measure_flag){
                    clock_gettime(CLOCK_REALTIME, &query_end);
                    query_elapsed = (query_end.tv_sec - query_start.tv_sec) +
                                    (query_end.tv_nsec - query_start.tv_nsec) / 1e9;
                    total_time_query2 += query_elapsed;
                }
                if(country != NULL){
                    free(country);
                }
                fclose(outputQ2);
                break;
            }

            case '3':{
                outputQ3 = fopen(outputPath, "w");
                if(!outputQ3){
                    perror("Erro ao criar o ficheiro de output da query 3.\n");
                    exit(EXIT_FAILURE);
                }

                strsep(&linePtr, " ");
                ageMin = atoi(strsep(&linePtr, " "));
                ageMax = atoi(strsep(&linePtr, "\n"));

                if(measure_flag) clock_gettime(CLOCK_REALTIME, &query_start);
                query3(ageMin, ageMax, gestorUser, delimiter, outputQ3);
                if(measure_flag){
                    clock_gettime(CLOCK_REALTIME, &query_end);
                    query_elapsed = (query_end.tv_sec - query_start.tv_sec) +
                                    (query_end.tv_nsec - query_start.tv_nsec) / 1e9;
                    total_time_query3 += query_elapsed;
                }
                fclose(outputQ3);
                break;
            }
        
            case '5':{
                // Tratamento da linha para a 1ª Query
                strsep(&linePtr, " "); // Ignora o id da Query e o espaço
                user = strsep(&linePtr, " ");
                int numRecommendations = atoi(strsep(&linePtr, "\n"));
                outputQ5 = fopen(outputPath, "w");
                if(!outputQ5){
                    perror("Erro ao criar o ficheiro de output da query 3.\n");
                    exit(EXIT_FAILURE);
                }
                query5(gestorHistory, user, numRecommendations, outputQ5);
                fclose(outputQ5);
                break;
            }
            
            case '6':{
                outputQ6 = fopen(outputPath, "w");
                if(!outputQ6){
                    perror("Erro ao criar o ficheiro de output da query 6.\n");
                    exit(EXIT_FAILURE);
                }

                // Tratamento da linha da 2ª Query
                strsep(&linePtr, " ");
                char* userQ6 = strsep(&linePtr, " "); // Id do utilizador
                char* yearQ6 = strsep(&linePtr, " "); // Ano
                char* listQ6 = strsep(&linePtr, "\n"); // argumento opcional
                //char* listQ6 = NULL;
                if(listQ6 == NULL){
                    yearQ6[4]='\0';
                }
            
                if(measure_flag) clock_gettime(CLOCK_REALTIME, &query_start);

                // Execução da 6ª Query
                setMusicWrap(gestorMusic, wrappedInit());
                printf("Começa a %dª linha da 6ª Query\n", i);
                query6(userQ6,yearQ6,listQ6,gestorHistory,gestorMusic,delimiter,outputQ6);
                printf("Termina a %dªlinha da 6ª Query\n", i);
                i++;
                freeMusicWrap(gestorMusic);

                if(measure_flag){
                    clock_gettime(CLOCK_REALTIME, &query_end);
                    query_elapsed = (query_end.tv_sec - query_start.tv_sec) +
                                    (query_end.tv_nsec - query_start.tv_nsec) / 1e9;
                    total_time_query2 += query_elapsed;
                }

                fclose(outputQ6);
            }
            
            default:
                continue;
        }

    }
    freeDiscography(disco);
    fclose(queries);

    // Para o modo de testes
    if(measure_flag){
        printf("Tempo de execucao da Query 1: %.6f segundos\n", total_time_query1);
        printf("Tempo de execucao da Query 2: %.6f segundos\n", total_time_query2);
        printf("Tempo de execucao da Query 3: %.6f segundos\n", total_time_query3);
        double total_time = (total_time_query1 + total_time_query2 + total_time_query3)/3;
        printf("Tempo medio de execucao de cada query: %.6f segundos\n", total_time);
    }
}