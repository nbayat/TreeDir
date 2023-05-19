#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../noeud.h"
#include "../debug.h"

// regardez le header pour la commentaire

void printNo(noeud *n)
{
    if (DEBUG)
    {
        printf("! DEBUG ! -> print");
        if (strcmp(n->nom, "") != 0)
        {
            printf(" depuis %s\n", n->nom);
        }
        else
        {
            printf(" depuis root\n");
        }
    }

    if (n == NULL)
    {
        printf("erreur dans la fonction print, le noeud est null \n");
        exit(EXIT_FAILURE);
    }
    printf("\n[print]:\n");
    print_noeud(n);
    printf("\n");
}
