#include "path.h"
#include "../noeud.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "cd.h"
#include "cp.h"

void mv(char *source, char *dest, noeud *dir)
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
    noeud *tmp = malloc(sizeof(noeud));
    tmp = remove_child_from_parent(dir->pere, dir);
    if (tmp == NULL)
    {
        printf("Invalid path\n");
        return;
    }
    dir = cd(dest, dir);
    if (dir == NULL)
    {
        printf("Invalid path\n");
        return;
    }
    tmp->pere = dir;
    add_child(dir->pere, tmp);
}