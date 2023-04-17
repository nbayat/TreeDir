#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "path.h"
#include "../noeud.h"
#include "cd.h"
#include "cp.h"

// regardez le header pour la commentaire

void mv(char *source, char *dest, noeud *dir)
{
    if (!isValidPath(source, dir))
    {
        assert("Chemin invalide (référence_de_l'erreur_MV01)\n");
        exit(EXIT_FAILURE);
    }
    dir = cd(source, dir);
    if (dir == NULL)
    {
        return;
    }
    noeud *tmp = malloc(sizeof(noeud));
    tmp = remove_child_from_parent(dir->pere, dir);
    if (tmp == NULL)
    {
        assert("Chemin invalide (référence_de_l'erreur_MV02)\n");
        exit(EXIT_FAILURE);
    }
    dir = cd(dest, dir);
    if (dir == NULL)
    {
        assert("Chemin invalide (référence_de_l'erreur_MV03)\n");
        exit(EXIT_FAILURE);
    }
    tmp->pere = dir;
    add_child(dir->pere, tmp);
}