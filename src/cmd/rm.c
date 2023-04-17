#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "cd.h"
#include "../noeud.h"

// regardez le header pour la commentaire

void rm(char *path, noeud *curr_dir)
{
    curr_dir = cd(path, curr_dir);
    if (curr_dir == NULL)
    {
        assert("Aucun fichier ou répertoire de ce nom (référence_de_l'erreur_RM01)\n");
        exit(EXIT_FAILURE);
    }
    remove_child_by_name(curr_dir->pere, curr_dir->nom);
    free(curr_dir);
}
