#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "path.h"
#include "../noeud.h"
#include "cd.h"
#include "cp.h"
#include "../debug.h"

// regardez le header pour la commentaire

void mv(char *source, char *dest, noeud *dir)
{
    if (DEBUG)
    {
        printf("! DEBUG ! -> mv %s %s", source, dest);
        if (strcmp(dir->nom, "") != 0)
        {
            printf(" depuis %s\n", dir->nom);
        }
        else
        {
            printf(" depuis root\n");
        }
    }
    if (!isValidPath(source, dir))
    {
        printf("Chemin invalide \n");
        exit(EXIT_FAILURE);
    }
    dir = cd(source, dir);
    if (dir == NULL)
    {
        printf("Le chemin n'est pas valide\n");
        exit(EXIT_FAILURE);
    }
    noeud *tmp = malloc(sizeof(noeud));
    tmp = remove_child_from_parent(dir->pere, dir);
    if (tmp == NULL)
    {
        printf("Le chemin n'est pas valide\n");
        exit(EXIT_FAILURE);
    }
    dir = cd(dest, dir);
    if (dir == NULL)
    {
        printf("Le chemin n'est pas valide\n");
        exit(EXIT_FAILURE);
    }
    tmp->pere = dir;
    add_child(dir->pere, tmp);
}