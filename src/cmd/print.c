#include "../noeud.h"
#include <stdio.h>

void print_noeud(noeud *n) {
    // Print nom
    printf("%s ", n->nom);

    // Print nb de fils
    int num_children = 0;
    liste_noeud *child = n->fils;
    while (child != NULL) {
        num_children++;
        child = child->succ;
    }
    printf("(%d): ", num_children);

    // Print nom et type de chaque fils
    child = n->fils;
    while (child != NULL) {
        printf("%s", child->no->nom);
        if (child->no->est_dossier) {
            printf("(D) ");
        } else {
            printf(" ");
        }
        child = child->succ;
    }
    printf("\n");

    // print les fils recursivement
    child = n->fils;
    while (child != NULL) {
        if (child->no->est_dossier) {
            print_noeud(child->no);
        }
        child = child->succ;
    }
}
