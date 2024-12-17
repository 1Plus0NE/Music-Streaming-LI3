#include "../../include/entidades/history.h"

struct history {
    long int id;
    long int user_id;
    long int music_id;
    char* timestamp;
    int duration;
    Platform platform;
};

//função para criar uma estrutura da entidade histórico parametrizada.
History* createHistory(long int id, long int user_id, long int music_id, char* timestamp, int duration, Platform platform){
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

    history -> duration = duration;
    history -> platform = platform;

    return history;
}

//função para libertar a memória de uma entidade do tipo histórico.
void freeHistory(History* history){
    if(!history) return;
    free(history -> timestamp);
    free(history);
}

//função para libertar a memória de uma entidade do tipo histórico contida numa hash table.
gboolean freeHistoryInTable(gpointer key, gpointer value, gpointer user_data){
    (void)key;
    (void)user_data;
    History* history = (History*)value;
    free(history -> timestamp);
    free(history);

    return TRUE;
}

//função para converter uma string de plataforma para a forma de enum.
Platform stringToPlatform(char* platform_str){
    if(strcmp(platform_str, "desktop") == 0){
        return DESKTOP;
    }else if(strcmp(platform_str, "mobile") == 0){
        return MOBILE;
    }else{
        fprintf(stderr, "Plataforma desconhecida: %s.\n", platform_str);
        exit(EXIT_FAILURE);
    }
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

//getters e setters de histórico.
long int getHistoryId(History* h){
    return h ? h -> id : -1;
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

int getHistoryDuration(History* h){
    return h ? h -> duration : -1;
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

void setHistoryDuration(History* h, int duration){
    h -> duration = duration;
}

void setHistoryPlatform(History* h, Platform platform){
    h -> platform = platform;
}