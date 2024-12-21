#include "../../include/parser/parser.h"
#define MAX_FILENAME 1024
#define MAX_LINE 2048
#define MAX_QUERYLINE 150
typedef void (*EntityProcessor)(char* line, void* gestor, void* aux_data);

// Função principal de parse que chama os módulos de parse individualmente.
void parse_all(char* path, GestorArtist* gestorArtist, GestorMusic* gestorMusic, GestorUser* gestorUser){
    //parse de artistas
    parse_artist(path, gestorArtist);

    //parse de músicas
    parse_music(path, gestorMusic, gestorArtist);

    //parse de usuários
    parse_user(path, gestorUser, gestorMusic);
}

// função que faz parse de um csv.
void parse_csv(const char* path, const char* filename, void* gestor, void* aux_data, EntityProcessor process_line, int error_code) {
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
            process_line(original_line, gestor, aux_data);
        }else{
            writeErrors(original_line, error_code);
        }
    }

    fclose(file);
}

// Função dá parse as queries.
void parse_queries(char* path, GestorUser* gestorUser, GestorMusic* gestorMusic, GestorArtist* gestorArtist, int measure_flag){
    char line[MAX_QUERYLINE];
    char* linePtr=NULL;
    FILE* queries;
    FILE* outputQ1;
    FILE* outputQ2;
    FILE* outputQ3;
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
    while(fgets(line, sizeof(line), queries) != NULL){ 

        linePtr = line;
        // Atualização do path para o ficheiro de output da query 
        command++;
        snprintf(outputPath, MAX_FILENAME, "resultados/command%d_output.txt", command);

        char delimiter = getDelimiter(line); // obter o delimitador que irá ser utilizado no writing
        // Identificação da Query
        if(line[0] == '1'){
            // Criação do ficheiro de output da query para argumento do função query1
            outputQ1 = fopen(outputPath, "w");
            if(!outputQ1){
                perror("Erro ao criar o ficheiro de output da query 1.\n");
                exit(EXIT_FAILURE);
            }
            // Tratamento da linha para a 1ª Query
            strsep(&linePtr, " "); // Ignora o id da Query e o espaço 
            user = strsep(&linePtr, "\n");

            if(measure_flag) clock_gettime(CLOCK_REALTIME, &query_start);
            query1(user, gestorUser, delimiter, outputQ1);
            if(measure_flag){
                clock_gettime(CLOCK_REALTIME, &query_end);
                query_elapsed = (query_end.tv_sec - query_start.tv_sec) +
                                (query_end.tv_nsec - query_start.tv_nsec) / 1e9;
                total_time_query1 += query_elapsed;
            }
            // Processo completo, fechar ficheiro
            fclose(outputQ1);
        }
        else if(line[0] == '2'){
            outputQ2 = fopen(outputPath, "w");
            if(!outputQ2){
                perror("Erro ao criar o ficheiro de output da query 2.\n");
                exit(EXIT_FAILURE);
            }

            strsep(&linePtr, " ");
            nArtists = atoi(strsep(&linePtr, " ")); // Numero de artistas
            country = remove_aspas(strsep(&linePtr, "\n")); // País sem aspas
            
            if(measure_flag) clock_gettime(CLOCK_REALTIME, &query_start);
            if(country == NULL){
                query2(nArtists, disco, delimiter ,outputQ2);
            }
             // query 2 sem especificação de país
            else{
                query2b(nArtists, country, disco, delimiter, outputQ2);
            }
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
        }
        else if(line[0] == '3'){
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
        }  
        else continue;
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