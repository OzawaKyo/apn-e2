#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pile.h"
typedef struct {
    char ouvrante;
    char fermante;
} PaireParentheses;
const PaireParentheses TYPES_PARENTHESES[] = {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};
const int NB_TYPES_PARENTHESES = 3;

char generer_caractere_aleatoire() {
    const char caracteres[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    return caracteres[rand() % (sizeof(caracteres) - 1)];
}


int est_parenthese_ouvrante(char c) {
    return c == '(' || c == '[' || c == '{';
}

int est_parenthese(char c) {
    return c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}';
}

char get_parenthese_fermante(char ouvrante) {
    const PaireParentheses TYPES_PARENTHESES[] = {
        {'(', ')'},
        {'[', ']'},
        {'{', '}'}
    };
    const int NB_TYPES_PARENTHESES = 3;

    for (int i = 0; i < NB_TYPES_PARENTHESES; i++) {
        if (TYPES_PARENTHESES[i].ouvrante == ouvrante) {
            return TYPES_PARENTHESES[i].fermante;
        }
    }
    return '\0';
}

int OracleParenthesage(FILE *input, int reponse) {
    Pile *pile = creer_pile(100); // Taille arbitraire, ajustez selon vos besoins
    int est_valide = 1;
    char c;

    while ((c = fgetc(input)) != EOF && est_valide) {
        if (est_parenthese_ouvrante(c)) {
            empiler(pile, c);
        } else if (est_parenthese(c)) {
            if (est_vide(pile)) {
                est_valide = 0;
            } else {
                char derniere_ouvrante = depiler(pile);
                if (get_parenthese_fermante(derniere_ouvrante) != c) {
                    est_valide = 0;
                }
            }
        }
    }

    if (!est_vide(pile)) {
        est_valide = 0;
    }

    detruire_pile(pile);
    return est_valide == reponse;
}

int main(int argc, char *argv[]) {
    FILE *input;
    FILE *output;
    char output_string[25];
    char *s;
    int output_value;

    if (argc < 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    input = fopen(argv[1], "r");
    if (input == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", argv[1]);
        return 1;
    }

    output = fopen(argv[2], "r");
    if (output == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", argv[2]);
        fclose(input);
        return 1;
    }

    s = fgets(output_string, 25, output);
    if (s == NULL) {
        fprintf(stderr, "Erreur lors de la lecture dans le fichier %s\n", argv[2]);
        fclose(input);
        fclose(output);
        return 1;
    }

    if (strcmp(output_string, "Bon parenthesage\n") == 0) {
        output_value = 1;
    } else if (strcmp(output_string, "Mauvais parenthesage\n") == 0) {
        output_value = 0;
    } else {
        printf("ERREUR\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    if (OracleParenthesage(input, output_value)) {
        printf("OK\n");
        fclose(input);
        fclose(output);
        return 0;
    } else {
        printf("ERREUR\n");
        fclose(input);
        fclose(output);
        return 1;
    }
}
