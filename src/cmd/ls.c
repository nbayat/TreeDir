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
            printf("Erreur: ce répertoire est vide\n");
        }
        return;
    }
    if (DEBUG)
    {
        printf("! DEBUG ! -> ls");
        if (strcmp(dir->nom, "") != 0)
        {
            printf(" depuis %s\n", dir->nom);
        }
        else
        {
            printf(" depuis root\n");
        }
    }
    printf("[ls]: \n");
    print_children(dir);
    printf("\n");
}
