#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../noeud.h"

// regardez le header pour la commentaire

// declaration des fonctions
bool isCurrent(char *path);
bool isLevelUp(char *path);
bool isRelative(char *path);
bool isReturnToRoot(char *path);
bool is_one_word(char *path);
bool isValidPath(char *path, noeud *dir);
char *extract_last_word_from_path(char *path);
char *exclude_last_word_from_path(char *path);
bool isSubPath(char *path, char *subPath);

bool isReturnToRoot(char *path)
{
    if (path == NULL || strcmp(path, "") == 0 || strcmp(path, " ") == 0 || strcmp(path, "/") == 0)
    {
        return true;
    }
    return false;
}

bool isCurrent(char *path)
{
    if (strcmp(path, ".") == 0)
    {
        return true;
    }
    return false;
}

bool isLevelUp(char *path)
{
    if (strcmp(path, "..") == 0)
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
    if (isCurrent(path) || isReturnToRoot(path) || isLevelUp(path))
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
                    // Aucun fichier ou répertoire de ce nom
                    return false;
                }
            }
            token = strtok(NULL, "/");
        }
    }
    else if (!isRelative(path))
    {
        char *newPath = malloc(strlen(path) + 1);
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
                    // Aucun fichier ou répertoire de ce nom
                    return false;
                }
            }
            token = strtok(NULL, "/");
        }
    }
    return true;
}

char *extract_last_word_from_path(char *path)
{
    if (is_one_word(path))
    {
        return path;
    }

    char *newPath = malloc(strlen(path) + 1);
    strcpy(newPath, path);
    char *token = strtok(newPath, "/");
    char *lastWord = malloc(strlen(token) + 1);
    strcpy(lastWord, token);
    while (token != NULL)
    {
        lastWord = malloc(strlen(token) + 1);
        strcpy(lastWord, token);
        token = strtok(NULL, "/");
    }
    return lastWord;
}

char *exclude_last_word_from_path(char *path)
{
    if (is_one_word(path))
    {
        return path;
    }
    char *newPath = malloc(strlen(path) + 1);
    strcpy(newPath, path);
    char *token = strtok(newPath, "/");
    char *lastWord = malloc(strlen(token) + 1);
    strcpy(lastWord, token);
    while (token != NULL)
    {
        lastWord = malloc(strlen(token) + 1);
        strcpy(lastWord, token);
        token = strtok(NULL, "/");
    }
    int lastWordLength = strlen(lastWord);
    int pathLength = strlen(path);
    int newPathLength = pathLength - lastWordLength - 1;
    char *newPath2 = malloc(newPathLength + 1);
    if (!isRelative(path))
    {
        strcpy(newPath2, "/");
        strncat(newPath2, path, newPathLength);
        // strncpy(newPath2, path, newPathLength);
    }
    else
    {
        strncpy(newPath2, path, newPathLength);
    }
    return newPath2;
}

bool is_one_word(char *path)
{
    if (strchr(path, '/') == NULL)
    {
        return true;
    }
    return false;
}

bool isSubPath(char *path, char *subPath)
{
    if (strlen(path) < strlen(subPath))
    {
        return false;
    }
    if (strcmp(path, subPath) == 0)
    {
        return true;
    }
    if (is_one_word(path))
    {
        return false;
    }
    char *newPath = malloc(strlen(path) + 1);
    strcpy(newPath, path);
    char *token = strtok(newPath, "/");

    char *newSubPath = malloc(strlen(subPath) + 1);
    strcpy(newSubPath, subPath);
    char *token2 = strtok(newSubPath, "/");

    while (token != NULL)
    {
        if (strcmp(token, token2) == 0)
        {
            return true;
        }
        token = strtok(NULL, "/");
        token2 = strtok(NULL, "/");
    }

    return false;
}
