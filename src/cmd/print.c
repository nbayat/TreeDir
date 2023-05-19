#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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
            printf(" dans %s\n", n->nom);
        }
        else
        {
            printf(" dans root\n");
        }
    }

    if (n == NULL)
    {
        assert("erreur lors de la fonction print, le noeud est null (référence_de_l'erreur_PRINT01)\n");
        exit(EXIT_FAILURE);
    }
    printf("[print]:\n");
    print_noeud(n);
}
