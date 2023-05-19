#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../noeud.h"
#include "path.h"
#include "../debug.h"

// regardez le header pour la commentaire

noeud *cd(char *path, noeud *dir)
{
    // debug mode
    if (DEBUG)
    {
        printf("! DEBUG ! -> cd %s", path);
        if (strcmp(dir->nom, "") != 0)
        {
            printf(" depuis %s\n", dir->nom);
        }
        else
        {
            printf(" depuis root\n");
        }
    }
    if (isReturnToRoot(path))
    {
        return dir->racine;
    }
    if (isCurrent(path))
    {
        // on esy déjà depuis le bon répertoire ex: cd .
        return dir;
    }
    if (isLevelUp(path))
    {
        if (dir->racine == dir)
        {
            return dir;
        }
        return dir->pere;
    }
    if (dir->fils == NULL && isRelative(path) && !isReturnToRoot(path) && !isCurrent(path) && !isLevelUp(path))
    {
        printf("Erreur: ce répertoire est vide et le path relative n'est pas valide\n");
        exit(EXIT_FAILURE);
    }

    if (isRelative(path))
    {
        char *newPath = malloc(strlen(path) + 1);
        if (newPath == NULL)
        {
            printf("Erreur: Erreur malloc dans la commande cd\n");
            exit(EXIT_FAILURE);
        }
        strcpy(newPath, path);
        char *token = strtok(newPath, "/");
        while (token != NULL)
        {
            if (isRelative(token))
            {
                dir = find_child(dir, token);
                if (dir == NULL)
                {
                    printf("Erreur: Aucun fichier ou répertoire de ce nom\n");
                    exit(EXIT_FAILURE);
                }
                else if (!dir->est_dossier)
                {
                    printf("Erreur: ce n'est pas un répertoire\n");
                    exit(EXIT_FAILURE);
                }
            }
            token = strtok(NULL, "/");
        }
    }
    else if (!isRelative(path))
    {
        char *newPath = malloc(strlen(path) + 1);
        if (newPath == NULL)
        {
            printf("Erreur: malloc dans la commande cd\n");
            exit(EXIT_FAILURE);
        }
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
                    printf("Erreur: Aucun fichier ou répertoire de ce nom \n");
                    exit(EXIT_FAILURE);
                }
                else if (!dir->est_dossier)
                {
                    printf("Erreur: ce n'est pas un répertoire\n");
                    exit(EXIT_FAILURE);
                }
            }
            token = strtok(NULL, "/");
        }
    }
    return dir;
}
