#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../noeud.h"

char *pwd(noeud *n)
{
    char *path = malloc(100);
    if (n->pere == n)
    {
        return path;
    }
    printf(" %s, ", n->pere->nom);
    path = pwd(n->pere);
    strcat(path, "/");
    strcat(path, n->nom);
    return path;
}