#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "../noeud.h"
#include "path.h"
#include "cd.h"

// regardez le header pour la commentaire

void cp(char *source, char *dest, noeud *dir)
{
    if (!isValidPath(source, dir))
    {
        assert("Chemin invalide (référence_de_l'erreur_CP01)\n");
        exit(EXIT_FAILURE);
    }
    dir = cd(source, dir);
    if (dir == NULL)
    {
        return;
    }
    noeud *copy = malloc(sizeof(noeud));
    copy = duplicate_node(dir);

    dir = cd(dest, dir);
    if (dir == NULL)
    {
        assert("Chemin invalide (référence_de_l'erreur_CP2)\n");
        exit(EXIT_FAILURE);
    }
    copy->pere = dir;
    add_child(dir->pere, copy);
}
