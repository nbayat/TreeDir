#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "../noeud.h"
#include "path.h"

#include "../debug.h"

// regardez le header pour la commentaire

noeud *cd(char *path, noeud *dir)
{
    if (DEBUG)
    {
        printf("! DEBUG ! -> cd %s", path);
        if (strcmp(dir->nom, "") != 0)
        {
            printf(" dans %s\n", dir->nom);
        }
        else
        {
            printf(" dans root\n");
        }
    }
    if (isReturnToRoot(path))
    {
        // dir = dir->racine;
        return dir->racine;
    }
    if (isCurrent(path))
    {
        // on esy déjà dans le bon répertoire
        return dir;
    }
    if (isLevelUp(path))
    {
        if (dir->racine == dir)
        {
            // dir est déjà le répertoire racine
            return dir;
        }
        return dir->pere;
    }
    if (dir->fils == NULL && isRelative(path) && !isReturnToRoot(path) && !isCurrent(path) && !isLevelUp(path))
    {
        assert("ce répertoire est vide et ne contient pas un pere ou root\n");
        exit(EXIT_FAILURE);
    }

    if (isRelative(path))
    {

        char *newPath = malloc(strlen(path) + 1);
        strcpy(newPath, path);
        char *token = strtok(newPath, "/");
        while (token != NULL)
        {
            if (isRelative(token))
            {
                dir = find_child(dir, token);
                if (dir == NULL)
                {
                    assert("Aucun fichier ou répertoire de ce nom (référence_de_l'erreur_RM01)\n");
                    exit(EXIT_FAILURE);
                    return dir;
                }
                else if (!dir->est_dossier)
                {
                    assert("ce n'est pas un répertoire\n");
                    exit(EXIT_FAILURE);
                }
            }
            token = strtok(NULL, "/");
        }
    }
    else if (!isRelative(path))
    {
        char *newPath = malloc(strlen(path) + 1);
        newPath = newPath + 1;
        strcpy(newPath, path);
        dir = dir->racine;
        char *token = strtok(newPath, "/");
        while (token != NULL)
        {
            if (isRelative(token))
            {
                dir = find_child(dir, token);
                if (dir == NULL)
                {
                }
            }
            token = strtok(NULL, "/");
        }
    }

    return dir;
}
