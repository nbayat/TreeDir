#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "cd.h"
#include "../noeud.h"
#include "../debug.h"
#include "path.h"
#include "pwd.h"

// regardez le header pour la commentaire

void rm(char *path, noeud *curr_dir)
{
    if (DEBUG)
    {
        printf("! DEBUG ! -> rm %s", path);
        if (strcmp(curr_dir->nom, "") != 0)
        {
            printf(" depuis %s\n", curr_dir->nom);
        }
        else
        {
            printf(" depuis root\n");
        }
    }

    if (!isValidPath(path, curr_dir))
    {
        printf("Le chemin n'est pas valide\n");
        exit(EXIT_FAILURE);
    }

    if (!isRelative(path) && !isRelative(pwd(curr_dir)) && isSubPath(pwd(curr_dir), path))
    {
        printf("Vous ne pouvez pas supprimer un répertoire dans lequel vous êtes\n");
        exit(EXIT_FAILURE);
    }

    curr_dir = cd(path, curr_dir);
    if (curr_dir == NULL)
    {
        printf("Aucun fichier ou répertoire de ce nom \n");
        exit(EXIT_FAILURE);
    }
    remove_child_by_name(curr_dir->pere, curr_dir->nom);
    free(curr_dir);
}
