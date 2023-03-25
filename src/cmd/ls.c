#include <stdio.h>
#include "../noeud.h"

void ls(noeud *dir) {
    if (dir->fils == NULL) {
        printf("This directory is empty\n");
    } else {
        liste_noeud *current_file = dir->fils;
        while (current_file != NULL) {
            printf("%s\n", current_file->no->nom);
            current_file = current_file->succ;
        }
    }
}
