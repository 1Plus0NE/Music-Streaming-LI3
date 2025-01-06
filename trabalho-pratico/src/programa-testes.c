#include "../include/programa-testes.h"

#define MAX_LINE_LENGTH 1024
#define INITIAL_CAPACITY 10

//função auxiliar para redimensionar um array
int* resizeArray(int* array, int* capacity) {
    *capacity *= 2; // Dobrar a capacidade
    int* new_array = (int*) realloc(array, (*capacity) * sizeof(int));
    if (!new_array) {
        fprintf(stderr, "Erro ao realocar memória.\n");
        free(array); // Libera a memória antiga em caso de falha
        exit(EXIT_FAILURE);
    }
    return new_array;
}

//função principal para executar testes
int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Uso: %s <dataDir> <queriesFile> <expectedDir>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *dataDir = argv[1];
    char *queriesFile = argv[2];
    char *expectedDir = argv[3];

    int capacity_1 = INITIAL_CAPACITY;
    int capacity_2 = INITIAL_CAPACITY;
    int capacity_3 = INITIAL_CAPACITY;
    int capacity_4 = INITIAL_CAPACITY;
    int capacity_5 = INITIAL_CAPACITY;
    int capacity_6 = INITIAL_CAPACITY;

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
    parse_queries(queriesFile, gestorUser, gestorMusic, gestorArtist, gestorAlbum, gestorHistory, 1);

    // Caminho do arquivo de saída para comparar
    FILE *query_file = fopen(queriesFile, "r");
    if (!query_file) {
        fprintf(stderr, "Erro ao abrir o arquivo de queries: %s\n", queriesFile);
        return EXIT_FAILURE;
    }

    // Variáveis de contagem e análise de resultados
    int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
    int correct_count_1 = 0, correct_count_2 = 0, correct_count_3 = 0, correct_count_4 = 0, correct_count_5 = 0, correct_count_6 = 0;
    int total_count_1 = 0, total_count_2 = 0, total_count_3 = 0, total_count_4 = 0, total_count_5 = 0, total_count_6 = 0;
    char query_line[MAX_LINE_LENGTH];
    int query_number = 1;
    int* desc_1 = (int*) malloc(capacity_1 * sizeof(int));
    int* desc_2 = (int*) malloc(capacity_2 * sizeof(int));
    int* desc_3 = (int*) malloc(capacity_3 * sizeof(int));
    int* desc_4 = (int*) malloc(capacity_4 * sizeof(int));
    int* desc_5 = (int*) malloc(capacity_5 * sizeof(int));
    int* desc_6 = (int*) malloc(capacity_6 * sizeof(int));

    int* desc_1_2 = (int*) malloc(capacity_1 * sizeof(int));
    int* desc_2_2 = (int*) malloc(capacity_2 * sizeof(int));
    int* desc_3_2 = (int*) malloc(capacity_3 * sizeof(int));
    int* desc_4_2 = (int*) malloc(capacity_4 * sizeof(int));
    int* desc_5_2 = (int*) malloc(capacity_5 * sizeof(int));
    int* desc_6_2 = (int*) malloc(capacity_6 * sizeof(int));

    if (!desc_1 || !desc_2 || !desc_3 || !desc_4 || !desc_5 || !desc_6 || !desc_1_2 || !desc_2_2 || !desc_3_2 || !desc_4_2 || !desc_5_2 || !desc_6_2) {
        fprintf(stderr, "Erro ao alocar memória inicial.\n");
        exit(EXIT_FAILURE);
    }

    // Para cada query no arquivo de queries
    while (fgets(query_line, sizeof(query_line), query_file)) {
        if(query_line[0] == '1') {
            total_count_1++;
        } else if(query_line[0] == '2') {
            total_count_2++;
        } else if(query_line[0] == '3') {
            total_count_3++;
        } else if(query_line[0] == '4') {
            total_count_4++;
        } else if(query_line[0] == '5') {
            total_count_5++;
        } else if(query_line[0] == '6') {
            total_count_6++;
        }
        char result_file_path[256];
        snprintf(result_file_path, sizeof(result_file_path), "resultados/command%d_output.txt", query_number);

        char expected_file_path[256];
        snprintf(expected_file_path, sizeof(expected_file_path), "%s/command%d_output.txt", expectedDir, query_number);

        // Abrir arquivos de resultados e esperados
        FILE *result_file = fopen(result_file_path, "r");
        FILE *expected_file = fopen(expected_file_path, "r");

        if (result_file && expected_file) {
            int line_diff = 0;
            compare_outputs(result_file, expected_file, &line_diff);

            if (line_diff == 0) {
                if(query_line[0] == '1') {
                    correct_count_1++;
                } else if(query_line[0] == '2') {
                    correct_count_2++;
                } else if(query_line[0] == '3') {
                    correct_count_3++;
                } else if(query_line[0] == '4') {
                    correct_count_4++;
                } else if(query_line[0] == '5') {
                    correct_count_5++;
                } else if(query_line[0] == '6') {
                    correct_count_6++;
                }
            } else {
                if(query_line[0] == '1') {
                    if(a == capacity_1) {
                        desc_1 = resizeArray(desc_1, &capacity_1);
                        desc_1_2 = resizeArray(desc_1_2, &capacity_1);
                    }
                    desc_1[a] = query_number;
                    desc_1_2[a] = line_diff;
                    a++;
                } else if(query_line[0] == '2') {
                    if(b == capacity_2) {
                        desc_2 = resizeArray(desc_2, &capacity_2);
                        desc_2_2 = resizeArray(desc_2_2, &capacity_2);
                    }
                    desc_2[b] = query_number;
                    desc_2_2[b] = line_diff;
                    b++;
                } else if(query_line[0] == '3') {
                    if(c == capacity_3) {
                        desc_3 = resizeArray(desc_3, &capacity_3);
                        desc_3_2 = resizeArray(desc_3_2, &capacity_3);
                    }
                    desc_3[c] = query_number;
                    desc_3_2[c] = line_diff;
                    c++;
                } else if(query_line[0] == '4') {
                    if(d == capacity_4) {
                        desc_4 = resizeArray(desc_4, &capacity_4);
                        desc_4_2 = resizeArray(desc_4_2, &capacity_4);
                    }
                    desc_4[d] = query_number;
                    desc_4_2[d] = line_diff;
                    d++;
                } else if(query_line[0] == '5') {
                    if(e == capacity_5) {
                        desc_5 = resizeArray(desc_5, &capacity_5);
                        desc_5_2 = resizeArray(desc_5_2, &capacity_5);
                    }
                    desc_5[e] = query_number;
                    desc_5_2[e] = line_diff;
                    e++;
                } else if(query_line[0] == '6') {
                    if(f == capacity_6) {
                        desc_6 = resizeArray(desc_6, &capacity_6);
                        desc_6_2 = resizeArray(desc_6_2, &capacity_6);
                    }
                    desc_6[f] = query_number;
                    desc_6_2[f] = line_diff;
                    f++;
                }
            }

            fclose(result_file);
            fclose(expected_file);
        } else {
            if(query_line[0] == '1') {
                if(a == capacity_1) {
                    desc_1 = resizeArray(desc_1, &capacity_1);
                    desc_1_2 = resizeArray(desc_1_2, &capacity_1);
                }
                desc_1[a] = query_number;
                desc_1_2[a] = -1;
                a++;
            } else if(query_line[0] == '2') {
                if(b == capacity_2) {
                    desc_2 = resizeArray(desc_2, &capacity_2);
                    desc_2_2 = resizeArray(desc_2_2, &capacity_2);
                }
                desc_2[b] = query_number;
                desc_2_2[b] = -1;
                b++;
            } else if(query_line[0] == '3') {
                if(c == capacity_3) {
                    desc_3 = resizeArray(desc_3, &capacity_3);
                    desc_3_2 = resizeArray(desc_3_2, &capacity_3);
                }
                desc_3[c] = query_number;
                desc_3_2[c] = -1;
                c++;
            } else if(query_line[0] == '4') {
                if(d == capacity_4) {
                    desc_4 = resizeArray(desc_4, &capacity_4);
                    desc_4_2 = resizeArray(desc_4_2, &capacity_4);
                }
                desc_4[d] = query_number;
                desc_4_2[d] = -1;
                d++;
            } else if(query_line[0] == '5') {
                if(e == capacity_5) {
                    desc_5 = resizeArray(desc_5, &capacity_5);
                    desc_5_2 = resizeArray(desc_5_2, &capacity_5);
                }
                desc_5[e] = query_number;
                desc_5_2[e] = -1;
                e++;
            } else if(query_line[0] == '6') {
                if(f == capacity_6) {
                    desc_6 = resizeArray(desc_6, &capacity_6);
                    desc_6_2 = resizeArray(desc_6_2, &capacity_6);
                }
                desc_6[f] = query_number;
                desc_6_2[f] = -1;
                f++;
            }
        }
        query_number++;
    }
    fclose(query_file);

    printf("======================== Resultados ========================\n");
    printf("Q1: %d de %d testes ok!\n", correct_count_1, total_count_1);
    if(a > 0) {
        for(int i = 0; i < a; i++) {
            if(desc_1_2[i] == -1) {
                printf("Query %d: Arquivo não encontrado\n", desc_1[i]);
            }else{
                printf("Query %d: %d linhas diferentes\n", desc_1[i], desc_1_2[i]);
            }
        }
    }
    printf("Q2: %d de %d testes ok!\n", correct_count_2, total_count_2);
    if(b > 0) {
        for(int i = 0; i < b; i++) {
            if(desc_2_2[i] == -1) {
                printf("Query %d: Arquivo não encontrado\n", desc_2[i]);
            }else{
                printf("Query %d: %d linhas diferentes\n", desc_2[i], desc_2_2[i]);
            }
        }
    }
    printf("Q3: %d de %d testes ok!\n", correct_count_3, total_count_3);
    if(c > 0) {
        for(int i = 0; i < c; i++) {
            if(desc_3_2[i] == -1) {
                printf("Query %d: Arquivo não encontrado\n", desc_3[i]);
            }else{
                printf("Query %d: %d linhas diferentes\n", desc_3[i], desc_3_2[i]);
            }
        }
    }
    printf("Q4: %d de %d testes ok!\n", correct_count_4, total_count_4);
    if(d > 0) {
        for(int i = 0; i < d; i++) {
            if(desc_4_2[i] == -1) {
                printf("Query %d: Arquivo não encontrado\n", desc_4[i]);
            }else{
                printf("Query %d: %d linhas diferentes\n", desc_4[i], desc_4_2[i]);
            }
        }
    }
    printf("Q5: %d de %d testes ok!\n", correct_count_5, total_count_5);
    if(e > 0) {
        for(int i = 0; i < e; i++) {
            if(desc_5_2[i] == -1) {
                printf("Query %d: Arquivo não encontrado\n", desc_5[i]);
            }else{
                printf("Query %d: %d linhas diferentes\n", desc_5[i], desc_5_2[i]);
            }
        }
    }
    printf("Q6: %d de %d testes ok!\n", correct_count_6, total_count_6);
    if(f > 0) {
        for(int i = 0; i < f; i++) {
            if(desc_6_2[i] == -1) {
                printf("Query %d: Arquivo não encontrado\n", desc_6[i]);
            }else{
                printf("Query %d: %d linhas diferentes\n", desc_6[i], desc_6_2[i]);
            }
        }
    }

    // Tempo total do programa
    clock_gettime(CLOCK_REALTIME, &end_time);
    double program_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    // Relatório final
    printf("===================== Relatório e Mem =====================\n");
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
    
    free(desc_1);
    free(desc_2);
    free(desc_3);
    free(desc_4);
    free(desc_5);
    free(desc_6);
    free(desc_1_2);
    free(desc_2_2);
    free(desc_3_2);
    free(desc_4_2);
    free(desc_5_2);
    free(desc_6_2);

    return 0;
}

//função auxiliar para comparar as saídas obtidas e esperadas
void compare_outputs(FILE *result_file, FILE *expected_file, int *line_diff) {
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

        line_num++;
    }

    // Verificar se algum arquivo ainda tem linhas após o fim do outro
    if ((fgets(result_line, sizeof(result_line), result_file) != NULL) || 
        (fgets(expected_line, sizeof(expected_line), expected_file) != NULL)) {
        *line_diff = line_num;
    }
}