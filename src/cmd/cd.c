#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "../noeud.h"
#include "path.h"

// regardez le header pour la commentaire

noeud *cd(char *path, noeud *dir)
{
    printf("path: %s\n", path);
    if (dir->fils == NULL && isRelative(path) && !isReturnToRoot(path) && !isCurrent(path) && !isLevelUp(path))
    {
        assert("ce répertoire est vide\n");
        exit(EXIT_FAILURE);
    }
    if (isReturnToRoot(path))
    {
        dir = dir->racine;
        return dir;
    }
    if (isCurrent(path))
    {
        // on esy déjà dans le bon répertoire
        return dir;
    }
    if (isLevelUp(path))
    {
        if (dir->pere == NULL)
        {
            // dir est déjà le répertoire racine
            return dir;
        }
        dir = dir->pere;
        return dir;
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
                    assert("Aucun fichier ou répertoire de ce nom (référence_de_l'erreur_RM01)\n");
                    exit(EXIT_FAILURE);
                }
            }
            token = strtok(NULL, "/");
        }
    }
    return dir;
}
