#include <stdio.h>
#include <string.h>

#include "../noeud.h"
#include "../debug.h"

// regardez le header pour la commentaire

void ls(noeud *dir)
{
    if (dir->fils == NULL)
    {
        if (DEBUG)
        {
            printf("ce répertoire est vide\n");
        }
        return;
    }
    if (DEBUG)
    {
        printf("! DEBUG ! -> ls");
        if (strcmp(dir->nom, "") != 0)
        {
            printf(" dans %s\n", dir->nom);
        }
        else
        {
            printf(" dans root\n");
        }
    }
    printf("[ls]: ");
    print_children(dir);
}
