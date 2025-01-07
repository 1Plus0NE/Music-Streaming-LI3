#include "../../include/entidades/history.h"

struct history {
    long int id;
    long int user_id;
    long int music_id;
    char* timestamp;
    char* duration;
    Platform platform;
};

//função para criar uma estrutura da entidade histórico parametrizada.
History* createHistory(long int id, long int user_id, long int music_id, char* timestamp, char* duration, Platform platform){
    History* history = malloc(sizeof(History));
    if(!history){
        perror("Erro ao alocar memória para o histórico.\n");
        exit(EXIT_FAILURE);
    }

    history -> id = id;
    history -> user_id = user_id;
    history -> music_id = music_id;

    history -> timestamp = malloc(strlen(timestamp) + 1);
    if(!history -> timestamp){
        perror("Erro ao alocar memória para o timestamp do histórico.\n");
        free(history);
        exit(EXIT_FAILURE);
    }
    strcpy(history -> timestamp, timestamp);

    history -> duration = malloc(strlen(duration) + 1);
    if(!history -> duration){
        perror("Erro ao alocar memória para a duração do histórico.\n");
        free(history -> timestamp);
        free(history);
        exit(EXIT_FAILURE);
    }
    strcpy(history -> duration, duration);

    history -> platform = platform;

    return history;
}

//função para libertar a memória de uma entidade do tipo histórico.
void freeHistory(History* history){
    if(!history) return;
    free(history -> timestamp);
    free(history -> duration);
    free(history);
}

//função para libertar a memória de uma entidade do tipo histórico contida numa hash table.
void freeHistoryInTable(gpointer value){
    History* history = (History*)value;
    free(history -> duration);
    if(history -> timestamp){
        free(history -> timestamp);
    }
    //free(history -> timestamp);
    free(history);
}

//função para converter uma string de plataforma para a forma de enum.
Platform stringToPlatform(char* platform_str) {
    if (!platform_str) {
        fprintf(stderr, "Plataforma inválida: NULL string.\n");
        exit(EXIT_FAILURE);
    }

    // Criar uma cópia da string e convertê-la para minúsculas
    char* normalized_str = strdup(platform_str);
    if (!normalized_str) {
        perror("Erro ao alocar memória para normalização da plataforma.\n");
        exit(EXIT_FAILURE);
    }
    for (char* p = normalized_str; *p; p++) {
        *p = tolower(*p);
    }

    // Comparar com os valores esperados
    Platform platform;
    if (strcmp(normalized_str, "desktop") == 0) {
        platform = DESKTOP;
    } else if (strcmp(normalized_str, "mobile") == 0) {
        platform = MOBILE;
    } else {
        fprintf(stderr, "Plataforma desconhecida: %s.\n", platform_str);
        free(normalized_str);
        exit(EXIT_FAILURE);
    }

    free(normalized_str); // Liberar memória da string normalizada
    return platform;
}

//função para converter uma forma de enum de plataforma para uma string.
char* platformToString(Platform platform){
    switch(platform){
        case DESKTOP:
            return "desktop";
        case MOBILE:
            return "mobile";
        default:
            fprintf(stderr, "Plataforma desconhecida.\n");
            exit(EXIT_FAILURE);
    }
}

//função para verificar se uma string é uma plataforma válida.
int isValidPlatform(char* platform_str){
    if(!platform_str) return 0;

    char* normalized_str = strdup(platform_str);
    if(!normalized_str){
        perror("Erro ao alocar memória para normalização da plataforma.\n");
        exit(EXIT_FAILURE);
    }
    for(char* p = normalized_str; *p; p++){
        *p = tolower(*p);
    }

    int is_valid = (strcmp(normalized_str, "desktop") == 0 || strcmp(normalized_str, "mobile") == 0);

    free(normalized_str);
    return is_valid;
}

//getters e setters de histórico.
long int getHistoryId(History* h){
    return h->id;
}

long int getHistoryUserId(History* h){
    return h ? h -> user_id : -1;
}

long int getHistoryMusicId(History* h){
    return h ? h -> music_id : -1;
}

char* getHistoryTimestamp(History* h){
    return h -> timestamp ? strdup(h -> timestamp) : NULL;
}

char* getHistoryDuration(History* h){
    return h -> duration ? strdup(h -> duration) : NULL;
}

Platform getHistoryPlatform(History* h){
    return h ? h -> platform : (Platform)-1;
}

void setHistoryId(History* h, long int id){
    h -> id = id;
}

void setHistoryUserId(History* h, long int user_id){
    h -> user_id = user_id;
}

void setHistoryMusicId(History* h, long int music_id){
    h -> music_id = music_id;
}

void setHistoryTimestamp(History* h, char* timestamp){
    if(h -> timestamp){
        free(h -> timestamp);
    }
    h -> timestamp = strdup(timestamp);
}

void setHistoryDuration(History* h, char* duration){
    if(h -> duration){
        free(h -> duration);
    }
    h -> duration = strdup(duration);
}

void setHistoryPlatform(History* h, Platform platform){
    h -> platform = platform;
}