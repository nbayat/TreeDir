#include "path.h"
#include "../noeud.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "cd.h"

void cp(char *source, char *dest, noeud *dir)
{
    if (!isValidPath(source, dir))
    {
        printf("Invalid path\n");
        return;
    }
    dir = cd(source, dir);
    if (dir == NULL)
    {
        return;
    }
    noeud *copy = malloc(sizeof(noeud));
    copy = duplicate_node(dir);
    printf("##copy: %s\n", copy->nom);

    dir = cd(dest, dir);
    if (dir == NULL)
    {
        printf("Invalid path\n");
        return;
    }
    copy->pere = dir;
    add_child(dir->pere, copy);
    printf("##dir: %s\n", dir->pere->nom);
}
