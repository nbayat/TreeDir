#include <stdio.h>

#include "../noeud.h"

// regardez le header pour la commentaire

void ls(noeud *dir)
{
    if (dir->fils == NULL)
    {
        // printf("ce répertoire est vide\n");
        return;
    }
    print_children(dir);
}
