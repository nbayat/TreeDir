#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "../noeud.h"

#include "../debug.h"

// regardez le header pour la commentaire

void mkdir(char nom[100], noeud *parent)
{
    if (DEBUG)
    {
        printf("! DEBUG ! -> mkdir %s", nom);
        if (strcmp(parent->nom, "") != 0)
        {
            printf(" depuis %s\n", parent->nom);
        }
        else
        {
            printf("\n");
        }
    }
    if (strlen(nom) > 100)
    {
        printf("mkdir: Nom de fichier trop long \n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; nom[i]; i++)
    {
        if (!isalnum(nom[i]))
        {
            printf("mkdir: La chaîne de caractères contient un caractère non alphanumérique. \n");
            exit(EXIT_FAILURE);
        }
    }

    if (have_child_by_name(parent, nom))
    {
        printf("mkdir: Le repo existe déjà\n");
        exit(EXIT_FAILURE);
    }

    noeud *new_node = create_node(true, nom, parent, NULL);
    add_child(parent, new_node);
}