// pile.h

#ifndef PILE_H
#define PILE_H

typedef struct {
    int capacite;
    int indice_sommet;
    int *data;
} Pile;

Pile* creer_pile(int capacite);
void empiler(Pile *p, int valeur);
int depiler(Pile *p);
int est_vide(Pile *p);
void detruire_pile(Pile *p);

#endif
