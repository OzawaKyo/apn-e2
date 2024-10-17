#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

// Fonction pour créer une pile
Pile* creer_pile(int capacite) {
    Pile *p = (Pile*) malloc(sizeof(Pile));
    if (!p) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la pile.\n");
        exit(EXIT_FAILURE);
    }
    p->capacite = capacite;
    p->indice_sommet = -1;  // La pile est vide
    p->data = (int*) malloc(capacite * sizeof(int));  // Allouer un tableau
    if (!p->data) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour les données de la pile.\n");
        free(p);
        exit(EXIT_FAILURE);
    }
    return p;
}

// Redimensionner la pile si elle est pleine
void redimensionner(Pile *p) {
    p->capacite *= 2;
    int *temp = (int*) realloc(p->data, p->capacite * sizeof(int));
    if (!temp) {
        fprintf(stderr, "Erreur de redimensionnement de la pile.\n");
        free(p->data);
        free(p);
        exit(EXIT_FAILURE);
    }
    p->data = temp;
}

// Fonction pour empiler (push) un élément dans la pile
void empiler(Pile *p, int valeur) {
    if (p->indice_sommet >= p->capacite - 1) {
        redimensionner(p);
    }
    p->data[++(p->indice_sommet)] = valeur;  // Ajouter au sommet
}

// Fonction pour dépiler (pop) un élément de la pile
int depiler(Pile *p) {
    if (p->indice_sommet >= 0) {
        return p->data[(p->indice_sommet)--];  // Renvoyer l'élément et décrémenter le sommet
    } else {
        fprintf(stderr, "Erreur : la pile est vide.\n");
        return -1;  // Valeur indicative en cas d'erreur
    }
}

// Fonction pour vérifier si la pile est vide
int est_vide(Pile *p) {
    return p->indice_sommet == -1;
}

// Fonction pour détruire la pile et libérer la mémoire
void detruire_pile(Pile *p) {
    free(p->data);
    free(p);
}