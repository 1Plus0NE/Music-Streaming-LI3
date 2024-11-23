#ifndef HISTORY_H
#define HISTORY_H
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils.h"
#include "glib.h"

//forma de enunciar a entidade histórico.
typedef struct history History;

//enum que representa o atributo plataforma do histórico.
typedef enum {
    COMPUTADOR,
    DISPOSITIVO_MOVEL
} Platform;

#endif