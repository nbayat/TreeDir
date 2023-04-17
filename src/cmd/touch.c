#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../noeud.h"

// regardez le header pour la commentaire

void touch(noeud *parent, char *filename)
{
    noeud *new_file = (noeud *)malloc(sizeof(noeud));
    if (new_file == NULL)
    {
        assert("Error: could not allocate memory for new file. (référence_de_l'erreur_TOUCH10)\n");
        exit(EXIT_FAILURE);
    }

    new_file = create_node(false, filename, parent, NULL);
    add_child(parent, new_file);
}
