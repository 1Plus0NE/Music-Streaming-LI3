#include "../include/programa-testes.h"

#define MAX_LINE_LENGTH 1024

//função principal para executar testes
int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Uso: %s <dataDir> <queriesFile> <expectedDir>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *dataDir = argv[1];
    char *queriesFile = argv[2];
    char *expectedDir = argv[3];

    // Inicializar os gestores necessários
    GestorArtist* gestorArtist = createGestorArtist();
    GestorMusic* gestorMusic = createGestorMusic();
    GestorUser* gestorUser = createGestorUser();
    GestorAlbum* gestorAlbum = createGestorAlbum();
    GestorHistory* gestorHistory = createGestorHistory();

    // Carregar dados iniciais com parse_all
    parse_all(dataDir, gestorArtist, gestorMusic, gestorUser, gestorAlbum, gestorHistory);
    printf("Parsing inicial completo.\n");

    // Medir tempo inicial do programa completo
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_REALTIME, &start_time);

    // Execução das queries e comparação dos resultados com os esperados
    parse_queries(queriesFile, gestorUser, gestorMusic, gestorArtist, 1);

    // Caminho do arquivo de saída para comparar
    FILE *query_file = fopen(queriesFile, "r");
    if (!query_file) {
        fprintf(stderr, "Erro ao abrir o arquivo de queries: %s\n", queriesFile);
        return EXIT_FAILURE;
    }

    // Variáveis de contagem e análise de resultados
    int correct_count = 0;
    char query_line[MAX_LINE_LENGTH];
    int query_number = 1;

    // Para cada query no arquivo de queries
    while (fgets(query_line, sizeof(query_line), query_file)) {
        char result_file_path[256];
        snprintf(result_file_path, sizeof(result_file_path), "resultados/command%d_output.txt", query_number);

        char expected_file_path[256];
        snprintf(expected_file_path, sizeof(expected_file_path), "%s/command%d_output.txt", expectedDir, query_number);

        // Abrir arquivos de resultados e esperados
        FILE *result_file = fopen(result_file_path, "r");
        FILE *expected_file = fopen(expected_file_path, "r");

        if (result_file && expected_file) {
            int line_diff = 0;
            compare_outputs(result_file, expected_file, &correct_count, &line_diff);

            if (line_diff == 0) {
                printf("Query %d correta.\n", query_number);
                correct_count++;
            } else {
                printf("Query %d com discrepâncias na linha %d.\n", query_number, line_diff);
            }

            fclose(result_file);
            fclose(expected_file);
        } else {
            printf("Erro ao abrir arquivos para Query %d.\n", query_number);
        }

        query_number++;
    }
    fclose(query_file);

    // Tempo total do programa
    clock_gettime(CLOCK_REALTIME, &end_time);
    double program_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    // Relatório final
    printf("Tempo total do programa: %.4f segundos\n", program_time);

    // Uso de memória
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memória utilizada: %ld MB\n", (r_usage.ru_maxrss/1024));

    // Libera memória dos gestores
    freeGestorArtist(gestorArtist);
    freeGestorMusic(gestorMusic);
    freeGestorUser(gestorUser);
    freeGestorAlbum(gestorAlbum);
    freeGestorHistory(gestorHistory);

    return 0;
}

//função auxiliar para comparar as saídas obtidas e esperadas
void compare_outputs(FILE *result_file, FILE *expected_file, int *correct_count, int *line_diff) {
    char result_line[256];
    char expected_line[256];
    int line_num = 1;

    while (fgets(result_line, sizeof(result_line), result_file) && 
           fgets(expected_line, sizeof(expected_line), expected_file)) {

        // Remove quebra de linha no final das linhas
        result_line[strcspn(result_line, "\r\n")] = 0; // Remove '\n' ou '\r\n'
        expected_line[strcspn(expected_line, "\r\n")] = 0;

        // Compara as linhas limpas
        if (strcmp(result_line, expected_line) != 0) {
            *line_diff = line_num;
            return;
        }

        (*correct_count)++;
        line_num++;
    }

    // Verificar se algum arquivo ainda tem linhas após o fim do outro
    if ((fgets(result_line, sizeof(result_line), result_file) != NULL) || 
        (fgets(expected_line, sizeof(expected_line), expected_file) != NULL)) {
        *line_diff = line_num;
    }
}