#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

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
            printf(" dans %s\n", parent->nom);
        }
        else
        {
            printf(" dans root\n");
        }
    }

    noeud *new_file = (noeud *)malloc(sizeof(noeud));
    if (new_file == NULL)
    {
        assert("Error: could not allocate memory for new file. (référence_de_l'erreur_TOUCH10)\n");
        exit(EXIT_FAILURE);
    }

    new_file = create_node(false, filename, parent, NULL);
    add_child(parent, new_file);
}
