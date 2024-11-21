#include "../../include/entidades/album.h"

struct history {
    long int id;
    long int user_id;
    long int music_id;
    char* timestamp;
    int duration;
    Platform platform;
};