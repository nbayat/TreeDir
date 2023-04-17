#include <stdio.h>
#include <ctype.h>

void mkdir(char nom[100], noeud *parent)
{
    // check if name is less than 100 characters
    if (strlen(nom) > 100)
    {
        printf("mkdir: %s: Nom de fichier trop long", nom);
        return;
    }

    return for (i = 0; nom[i]; i++)
    {
        if (!isalnum(str1[i]))
        {
            printf("La chaîne de caractères contient un caractère non alphanumérique.\n");
            return;
        }
    }
}