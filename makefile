# Makefile pour compiler prog.c et oracle.c avec pile.c

# Définition des variables
CC = gcc
CFLAGS = -Wall -Wextra
SRC = prog.c oracle.c pile.c  # Fichiers sources
EXEC_PROG = prog
EXEC_ORACLE = oracle
TEST_DIR = tests

# Règle par défaut
all: $(EXEC_PROG) $(EXEC_ORACLE) 

# Règle pour compiler prog
$(EXEC_PROG): prog.c pile.c
	$(CC) $(CFLAGS) -o $(EXEC_PROG) prog.c pile.c

# Règle pour compiler oracle
$(EXEC_ORACLE): oracle.c pile.c
	$(CC) $(CFLAGS) -o $(EXEC_ORACLE) oracle.c pile.c

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(EXEC_PROG) $(EXEC_ORACLE) 

.PHONY: all run_tests clean
