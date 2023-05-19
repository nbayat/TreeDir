#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../noeud.h"
#include "path.h"
#include "cd.h"
#include "../debug.h"
#include "pwd.h"

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

    // backup du chemin courant
    noeud *currentPath = dir;

    if (!isValidPath(source, dir))
    {
        printf("Erreur: Le chemin source n'est pas valide\n");
        exit(EXIT_FAILURE);
    }

    char *sourcePere = malloc(strlen(source) + 1);
    sourcePere = exclude_last_word_from_path(source);
    char *sourceNom = malloc(strlen(source) + 1);
    sourceNom = extract_last_word_from_path(source);

    noeud *sourceNoeud = dir; // initialisation pour éviter un warning

    // si le chemin source est un seul mot, on se deplace dans le dossier courant
    // jusqu'à trouver le noeud qui contient le dernier mot du chemin comme un fils
    if (!is_one_word(source))
    {
        sourceNoeud = cd(sourcePere, dir);
    }
    sourceNoeud = find_child(sourceNoeud, sourceNom);

    // extraction du nom et du path du fichier de destination
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
        if (strcmp(destPere, "") == 0)
        {
            dir = currentPath;
        }
    }

    if (dir == NULL)
    {
        printf(" Erreur:Le chemin n'est pas valide \n");
        exit(EXIT_FAILURE);
    }
    // path de dest est un sous-path de source, (invalide)
    if (isSubPath(pwd(dir), pwd(sourceNoeud)))
    {
        printf("Erreur: Vous ne pouvez pas copier un répertoire dans son sous-répertoire.\n");
        exit(EXIT_FAILURE);
    }
    // déjà existant
    if (have_child_by_name(dir, destNom) == true)
    {
        printf("Erreur: Un fichier ou répertoire de ce nom existe déjà\n");
        exit(EXIT_FAILURE);
    }

    noeud *copy = duplicate_node(sourceNoeud, dir);
    strcpy(copy->nom, destNom);
    copy->pere = dir;
    updateParentNameForChild(copy, destNom);
    add_child(dir, copy);
}
