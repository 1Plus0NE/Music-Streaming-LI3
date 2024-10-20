# Nome do exec
PRINCIPAL = programa-principal
INTERATIVO = programa-interativo
TESTES = programa-testes

CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -g `pkg-config --cflags glib-2.0`

# Diretorias
SRC_DIR = src
ENTIDADES_DIR = $(SRC_DIR)/entidades
GESTORES_DIR = $(SRC_DIR)/gestores
OTHER_DIR = $(SRC_DIR)

# Diretorias dos headers
ENTIDADES_INCLUDE_DIR = $(INCLUDE_DIR)/entidades
GESTORES_INCLUDE_DIR = $(INCLUDE_DIR)/gestores
OTHER_DIR = $(INCLUDE_DIR)

ENTIDADES_SRC = $(ENTIDADES_DIR)/artist.c $(ENTIDADES_DIR)/music.c $(ENTIDADES_DIR)/user.c
GESTORES_SRC = $(GESTORES_DIR)/gestor_artist.c $(GESTORES_DIR)/gestor_music.c $(GESTORES_DIR)/gestor_user.c
PARSER = $(SRC_DIR)/parser.c
QUERIES = $(SRC_DIR)/queries.c
UTILS = $(SRC_DIR)/utils.c
MAIN = $(SRC_DIR)/main.c

SRC_PRINCIPAL = $(ENTIDADES_SRC) $(GESTORES_SRC) $(PARSER) $(QUERIES) $(UTILS) $(MAIN)

OBJ_PRINCIPAL = $(SRC_PRINCIPAL:.c=.o)

INCLUDE_DIR = $(SRC_DIR)

# Compilar todos os execs
all: $(PRINCIPAL)

# Criação do exec principal
$(PRINCIPAL): $(OBJ_PRINCIPAL)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(ENTIDADES_INCLUDE_DIR) -I$(GESTORES_INCLUDE_DIR) -o $(PRINCIPAL) $(OBJ_PRINCIPAL) `pkg-config --libs glib-2.0`

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(ENTIDADES_INCLUDE_DIR) -I$(GESTORES_INCLUDE_DIR) -c $< -o $@

# Limpar os objetos e os execs
clean:
	rm -f $(OBJ_PRINCIPAL) $(PRINCIPAL)