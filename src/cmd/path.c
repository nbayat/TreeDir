#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../noeud.h"

bool isCurrent(char *path);
bool isLevelUp(char *path);
bool isRelative(char *path);
bool isReturnToRoot(char *path);

bool isReturnToRoot(char *path)
{
    if (path[0] == '/' && path[1] == '\0')
    {
        return true;
    }
    if (path[0] == '\0')
    {
        return true;
    }
    return false;
}

bool isCurrent(char *path)
{
    if (path[0] == '.' && path[1] == '\0')
    {
        return true;
    }
    return false;
}

bool isLevelUp(char *path)
{
    if (path[0] == '.' && path[1] == '.' && path[2] == '\0')
    {
        return true;
    }
    return false;
}

bool isRelative(char *path)
{
    if (path[0] == '/')
    {
        return false;
    }
    return true;
}

bool isValidPath(char *path, noeud *dir)
{
    if (isCurrent(path))
    {
        return true;
    }
    if (isLevelUp(path))
    {
        return true;
    }
    if (isReturnToRoot(path))
    {
        return true;
    }
    if (isRelative(path))
    {
        char *newPath = malloc(strlen(path) + 1);
        strcpy(newPath, path);
        char *token = strtok(newPath, "/");
        while (token != NULL)
        {
            if (isRelative(token))
            {
                dir = find_child(dir, token);
                if (dir == NULL)
                {
                    printf("No such file or directory\n");
                    return false;
                }
            }
            token = strtok(NULL, "/");
        }
    }
    else if (!isRelative(path))
    {
        char *newPath = malloc(strlen(path) + 1);
        // ignore the first character
        newPath = newPath + 1;
        strcpy(newPath, path);
        dir = dir->racine;
        char *token = strtok(newPath, "/");
        while (token != NULL)
        {
            if (isRelative(token))
            {
                dir = find_child(dir, token);
                if (dir == NULL)
                {
                    printf("No such file or directory\n");
                    return false;
                }
            }
            token = strtok(NULL, "/");
        }
    }
    return true;
}