#include "../noeud.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cd.h"

void rm(char *path, noeud *curr_dir)
{
    curr_dir = cd(path, curr_dir);
    if (curr_dir == NULL)
    {
        printf("No such file or directory\n");
        return;
    }
    remove_child_by_name(curr_dir->pere, curr_dir->nom);
    free(curr_dir);
}
