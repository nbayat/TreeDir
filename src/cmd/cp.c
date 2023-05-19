#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../noeud.h"
#include "path.h"
#include "cd.h"
#include "../debug.h"

// regardez le header pour la commentaire

void cp(char *source, char *dest, noeud *dir)
{
    if (DEBUG)
    {
        printf("! DEBUG ! -> cp %s %s", source, dest);
        if (strcmp(dir->nom, "") != 0)
        {
            printf(" depuis %s\n", dir->nom);
        }
        else
        {
            printf(" depuis root\n");
        }
    }

    noeud *currentPath = dir;

    if (!isValidPath(source, dir))
    {
        printf("Le chemin source n'est pas valide\n");
        exit(EXIT_FAILURE);
    }

    char *sourcePere = malloc(strlen(source) + 1);
    sourcePere = exclude_last_word_from_path(source);
    char *sourceNom = malloc(strlen(source) + 1);
    sourceNom = extract_last_word_from_path(source);

    if (is_one_word(source) == false)
    {
        dir = cd(sourcePere, dir);
    }

    noeud *sourceNoeud = find_child(dir, sourceNom);
    // noeud *copy = duplicate_node(sourceNoeud);

    char *destPere = malloc(strlen(dest) + 1);
    destPere = exclude_last_word_from_path(dest);
    char *destNom = malloc(strlen(dest) + 1);
    destNom = extract_last_word_from_path(dest);

    if (strcmp(destPere, "/") == 0)
    {
        dir = dir->racine;
    }
    else if (is_one_word(dest) && isRelative(dest))
    {
        dir = currentPath;
    }
    else
    {
        dir = cd(destPere, currentPath);
    }

    if (dir == NULL)
    {
        printf("Chemin invalide \n");
        exit(EXIT_FAILURE);
    }

    if (have_child_by_name(dir, destNom) == true)
    {
        printf("Un fichier ou répertoire de ce nom existe déjà\n");
        exit(EXIT_FAILURE);
    }

    noeud *copy = duplicate_node(sourceNoeud, dir);
    strcpy(copy->nom, destNom);
    copy->pere = dir;
    updateParentNameForChild(copy, destNom);
    add_child(dir, copy);
}
