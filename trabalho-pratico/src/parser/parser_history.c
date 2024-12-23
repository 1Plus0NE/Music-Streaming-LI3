#include "../../include/parser/parser_history.h"
#define MAX_FILENAME 1024
#define MAX_LINE 2048

//função que dá parse ao ficheiro de histórico.
void parse_history(char* path, GestorHistory* gestorHistory) {
    parse_csv(path, "history.csv", gestorHistory, NULL, process_history_line, 1);
}

//função que processa uma linha do hsitórico.
void process_history_line(char* line, void* gestor, void* aux_data) {
    (void)aux_data;
    GestorHistory* gestorHistory = (GestorHistory*)gestor;
    char* tmp_line = line;
    char *id_str, *user_id_str, *music_id_str, *timestamp, *duration_str, *platform_str;
    long int id, user_id, music_id;
    int duration;
    Platform platform;

    id_str = remove_aspas(strsep(&tmp_line, ";"));
    if (!id_str || strlen(id_str) == 0) {
        writeErrors(line, 1);
        return;
    }
    id = strtol(id_str, NULL, 10);

    user_id_str = remove_aspas(strsep(&tmp_line, ";"));
    music_id_str = remove_aspas(strsep(&tmp_line, ";"));
    timestamp = remove_aspas(strsep(&tmp_line, ";"));
    duration_str = remove_aspas(strsep(&tmp_line, ";"));
    platform_str = remove_aspas(strsep(&tmp_line, "\n"));

    //validações.
    if(!user_id_str || !music_id_str || !timestamp || !duration_str || !platform_str || isValidPlatform(platform_str) == 0){
        writeErrors(line, 1);
        free(id_str);
        free(user_id_str);
        free(music_id_str);
        free(timestamp);
        free(duration_str);
        free(platform_str);
        return;
    }

    //conversões.
    user_id = strtol(user_id_str, NULL, 10);
    music_id = strtol(music_id_str, NULL, 10);
    duration = atoi(duration_str);
    platform = stringToPlatform(platform_str);

    History* h = createHistory(id, user_id, music_id, timestamp, duration, platform);
    addHistory(gestorHistory, h);

    free(id_str);
    free(user_id_str);
    free(music_id_str);
    free(timestamp);
    free(duration_str);
    free(platform_str);
}