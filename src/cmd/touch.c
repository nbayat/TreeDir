#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../noeud.h"
#include "../debug.h"

// regardez le header pour la commentaire

void touch(noeud *parent, char *filename)
{
    if (DEBUG)
    {
        printf("! DEBUG ! -> touch %s", filename);
        if (strcmp(parent->nom, "") != 0)
        {
            printf(" depuis %s\n", parent->nom);
        }
        else
        {
            printf(" dans root\n");
        }
    }

    if (strlen(filename) > 100)
    {
        printf("mkdir: Nom de fichier trop long \n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; filename[i]; i++)
    {
        if (!isalnum(filename[i]))
        {
            printf("Erreur: mkdir: La chaîne de caractères contient un caractère non alphanumérique. \n");
            exit(EXIT_FAILURE);
        }
    }

    if (have_child_by_name(parent, filename))
    {
        printf("Erreur: mkdir: Le fichier existe déjà ");
        return;
    }

    noeud *new_file = (noeud *)malloc(sizeof(noeud));
    if (new_file == NULL)
    {
        printf("Error: le mémoire n'est pas alloué \n");
        exit(EXIT_FAILURE);
    }

    new_file = create_node(false, filename, parent, NULL);
    add_child(parent, new_file);
}
