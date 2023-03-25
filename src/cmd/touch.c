#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "../noeud.h"

// Creates a new file with the specified name and adds it to the specified parent directory.
void touch(noeud* parent, char* filename) {
    // Allocate memory for the new file node.
    noeud* new_file = (noeud*) malloc(sizeof(noeud));
    if (new_file == NULL) {
        assert("Error: could not allocate memory for new file.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the file node.
    new_file = create_node(false, filename, parent);
}
