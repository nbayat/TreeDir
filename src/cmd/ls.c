#include <stdio.h>
#include "../noeud.h"

void ls(noeud *dir) {
    if (dir->fils == NULL) {
        printf("This directory is empty\n");
        return;
    }
    print_children(dir);
}
