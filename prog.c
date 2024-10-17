#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pile.h"
#include <string.h>

// Structure declaration
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
    for (int i = 0; i < NB_TYPES_PARENTHESES; i++) {
        if (TYPES_PARENTHESES[i].ouvrante == ouvrante) {
            return TYPES_PARENTHESES[i].fermante;
        }
    }
    return '\0';
}

void generer_parentheses_correctes(int taille_min, char *resultat) {
    int position = 0;
    Pile *pile = creer_pile(taille_min);
    int nb_parentheses = taille_min / 3; // Un tiers de la taille sera des parenthèses
    
    // Première phase : générer le contenu
    while (position < taille_min) {
        // Décider si on met une parenthèse ou un caractère
        if (nb_parentheses > 0 && (position < taille_min - nb_parentheses)) {
            // Ajouter une parenthèse ouvrante
            int type = rand() % NB_TYPES_PARENTHESES;
            resultat[position++] = TYPES_PARENTHESES[type].ouvrante;
            empiler(pile, TYPES_PARENTHESES[type].ouvrante);
            nb_parentheses--;
            
            // Ajouter un caractère aléatoire après la parenthèse ouvrante
            if (position < taille_min) {
                resultat[position++] = generer_caractere_aleatoire();
            }
        } else if (!est_vide(pile)) {
            // Fermer une parenthèse
            char ouvrante = depiler(pile);
            resultat[position++] = get_parenthese_fermante(ouvrante);
        } else {
            // Ajouter un caractère aléatoire
            resultat[position++] = generer_caractere_aleatoire();
        }
    }
    
    // S'assurer que toutes les parenthèses sont fermées
    while (!est_vide(pile)) {
        // Remplacer le dernier caractère non-parenthèse par une parenthèse fermante
        char ouvrante = depiler(pile);
        char fermante = get_parenthese_fermante(ouvrante);
        
        // Chercher le dernier caractère non-parenthèse à remplacer
        for (int i = position - 1; i >= 0; i--) {
            if (!est_parenthese(resultat[i])) {
                resultat[i] = fermante;
                break;
            }
        }
    }
    
    resultat[taille_min] = '\0';
    detruire_pile(pile);
}

void generer_parentheses_avec_imbrication(int taille_min, int niveau_imbrication, char *resultat) {
    int position = 0;
    Pile *pile = creer_pile(taille_min);

    // Garantir une taille minimale suffisante pour l'imbrication
    if (taille_min < niveau_imbrication * 3) {
        taille_min = niveau_imbrication * 3;
    }

    // Générer l'imbrication requise
    for (int i = 0; i < niveau_imbrication && position < taille_min - niveau_imbrication; i++) {
        // Parenthèse ouvrante
        int type = i % NB_TYPES_PARENTHESES;
        resultat[position++] = TYPES_PARENTHESES[type].ouvrante;
        empiler(pile, TYPES_PARENTHESES[type].ouvrante);

        // Caractère aléatoire
        if (position < taille_min) {
            resultat[position++] = generer_caractere_aleatoire();
        }
    }

    // Remplir le reste avec des caractères aléatoires
    while (position < taille_min - niveau_imbrication) {
        resultat[position++] = generer_caractere_aleatoire();
    }

    // Fermer toutes les parenthèses
    while (!est_vide(pile)) {
        char ouvrante = depiler(pile);
        resultat[position++] = get_parenthese_fermante(ouvrante);
    }

    resultat[taille_min] = '\0';
    detruire_pile(pile);
}


void generer_parentheses_incorrectes(int taille_min, char *resultat) {
    // Générer une chaîne correcte
    generer_parentheses_correctes(taille_min, resultat);
    
    // Trouver une position aléatoire contenant un caractère
    int position;
    do {
        position = rand() % taille_min;
    } while (est_parenthese(resultat[position]));
    
    // Remplacer par une parenthèse fermante aléatoire
    int type = rand() % NB_TYPES_PARENTHESES;
    resultat[position] = TYPES_PARENTHESES[type].fermante;
}

int verifier_parentheses(const char *chaine) {
    Pile *pile = creer_pile(strlen(chaine));
    int est_valide = 1;
    
    for (int i = 0; chaine[i] != '\0' && est_valide; i++) {
        if (est_parenthese_ouvrante(chaine[i])) {
            empiler(pile, chaine[i]);
        } else if (est_parenthese(chaine[i])) {
            if (est_vide(pile)) {
                est_valide = 0;
            } else {
                char derniere_ouvrante = depiler(pile);
                if (get_parenthese_fermante(derniere_ouvrante) != chaine[i]) {
                    est_valide = 0;
                }
            }
        }
    }
    
    if (!est_vide(pile)) {
        est_valide = 0;
    }
    
    detruire_pile(pile);
    return est_valide;
}

void afficher_menu() {
    printf("=== Menu de test ===\n");
    printf("1. Générer une chaîne bien parenthésée avec caractères aléatoires\n");
    printf("2. Générer une chaîne bien parenthésée avec imbrication minimale et caractères\n");
    printf("3. Générer une chaîne mal parenthésée avec caractères\n");
    printf("4. Vérifier une chaîne de parenthèses\n");
}
int main() {
    srand(time(NULL));
    int choix;
    char resultat[101];

    do {
        afficher_menu();
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                int taille_min;
                printf("Entrez la taille minimale de la chaîne : ");
                scanf("%d", &taille_min);
                generer_parentheses_correctes(taille_min, resultat);
                printf("Chaîne générée : %s\n", resultat);
                printf("Vérification : %s\n", verifier_parentheses(resultat) ? "Valide" : "Invalide");
                break;
            }
            case 2: {
                int taille_min, niveau_imbrication;
                printf("Entrez la taille minimale de la chaîne : ");
                scanf("%d", &taille_min);
                printf("Entrez le niveau d'imbrication minimum : ");
                scanf("%d", &niveau_imbrication);
                generer_parentheses_avec_imbrication(taille_min, niveau_imbrication, resultat);
                printf("Chaîne générée : %s\n", resultat);
                printf("Vérification : %s\n", verifier_parentheses(resultat) ? "Valide" : "Invalide");
                break;
            }
            case 3: {
                int taille_min;
                printf("Entrez la taille minimale de la chaîne : ");
                scanf("%d", &taille_min);
                generer_parentheses_incorrectes(taille_min, resultat);
                printf("Chaîne générée : %s\n", resultat);
                printf("Vérification : %s\n", verifier_parentheses(resultat) ? "Valide" : "Invalide");
                break;
            }
            case 4: {
                printf("Entrez une chaîne à vérifier : ");
                scanf(" %100[^\n]", resultat);
                printf("La chaîne est %s\n", verifier_parentheses(resultat) ? "valide" : "invalide");
                break;
            }
            default:
                printf("Choix non valide. Veuillez réessayer.\n");
        }
    } while (choix > 4 || choix < 1);

    return 0;
}
