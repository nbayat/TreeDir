#ifndef NOEUD_H
#define NOEUD_H

#include <stdbool.h>

typedef struct noeud noeud;
typedef struct liste_noeud liste_noeud;

struct noeud {
    bool est_dossier;
    char nom[100];
    struct noeud *pere;
    struct noeud *racine;
    struct liste_noeud *fils;
};

struct liste_noeud {
    struct noeud *no;
    struct liste_noeud *succ;
};

noeud* create_node(bool est_dossier, char nom[100], noeud* pere);
void add_child(noeud* parent, noeud* child);
void remove_child(noeud* parent, noeud* child);
void free_node(noeud* node);

#endif
