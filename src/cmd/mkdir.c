#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "../noeud.h"

// regardez le header pour la commentaire

void mkdir(char nom[100], noeud *parent)
{
    if (strlen(nom) > 100)
    {
        assert("mkdir: Nom de fichier trop long (référence_de_l'erreur_MKDIR01)\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; nom[i]; i++)
    {
        if (!isalnum(nom[i]))
        {
            assert("mkdir: La chaîne de caractères contient un caractère non alphanumérique. (référence_de_l'erreur_MKDIR02)\n");
            exit(EXIT_FAILURE);
        }
    }

    if (have_child_by_name(parent, nom))
    {
        assert("mkdir: Le fichier existe déjà (référence_de_l'erreur_MKDIR03)");
        return;
    }

    noeud *new_node = create_node(true, nom, parent, NULL);
    add_child(parent, new_node);
}