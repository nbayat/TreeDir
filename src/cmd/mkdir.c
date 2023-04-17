#include <stdio.h>
#include <ctype.h>
#include "../noeud.h"
#include <string.h>

void mkdir(char nom[100], noeud *parent)
{
    // check if name is less than 100 characters
    if (strlen(nom) > 100)
    {
        printf("mkdir: %s: Nom de fichier trop long", nom);
        return;
    }

    for (int i = 0; nom[i]; i++)
    {
        if (!isalnum(nom[i]))
        {
            printf("La chaîne de caractères contient un caractère non alphanumérique.\n");
            return;
        }
    }

    if (have_child_by_name(parent, nom))
    {
        printf("mkdir: %s: Le fichier existe déjà", nom);
        return;
    }

    noeud *new_node = create_node(true, nom, parent, NULL);
    add_child(parent, new_node);
}