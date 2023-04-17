#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../noeud.h"

// regardez le header pour la commentaire

void print(noeud *n)
{
    if (n == NULL)
    {
        assert("erreur lors de la fonction print, le noeud est null (référence_de_l'erreur_PRINT01)\n");
        exit(EXIT_FAILURE);
    }
    print_noeud(n);
}
