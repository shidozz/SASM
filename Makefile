
OUTPUT = sasm.exe
CFLAGS = -Wall -Iinclude
SRC = $(wildcard src/*.c)

# Liste des fichiers objets
OBJ = $(SRC:.c=.o)

# Règle par défaut pour créer l'exécutable
all: $(OUTPUT)

# Règle pour créer l'exécutable
$(OUTPUT): main.c $(OBJ) 
	$(CC) $(CFLAGS) -o $(OUTPUT) main.c $(OBJ)

# Règle générique pour compiler les fichiers objets à partir des fichiers source
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(OBJ) $(OUTPUT)

.PHONY: all clean mcc
