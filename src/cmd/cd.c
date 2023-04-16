#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../noeud.h"

bool isCurrent (char *path);
bool isLevelUp (char *path);
bool isRelative (char *path);
bool isReturnToRoot (char *path);


noeud* cd (char *path, noeud *dir) {
    if (dir->fils == NULL) {
        printf("This directory is empty\n");
        return dir;
    }
    if (isReturnToRoot(path)) {
        dir = dir->racine;
        return dir;
    }
    if (isCurrent(path)) {
        printf("You are already here\n");
        return dir;
    }
    if(isLevelUp(path)) {
        if (dir->pere == NULL) {
            printf("You are already at the root\n");
            return dir;
        }
        dir = dir->pere;
        return dir;
    }
    // split path into tokens
    if(isRelative(path)){
        char *newPath = malloc(strlen(path) + 1);
        strcpy(newPath, path);
        char *token = strtok(newPath, "/");
        while (token != NULL) {
            if (isRelative(token)) {
                dir = find_child(dir, token);
                if (dir == NULL) {
                    printf("No such file or directory\n");
                    return dir;
                }
            }
            token = strtok(NULL, "/");
        }
    } else if(!isRelative(path)) {
        char *newPath = malloc(strlen(path) + 1);
        // ignore the first character
        newPath = newPath + 1;
        strcpy(newPath, path);
        dir = dir->racine;
        char *token = strtok(newPath, "/");
        while (token != NULL) {
            if (isRelative(token)) {
                dir = find_child(dir, token);
                if (dir == NULL) {
                    printf("No such file or directory\n");
                    return dir;
                }
            }
            token = strtok(NULL, "/");
        }
    }
    return dir;
}

bool isReturnToRoot (char *path) {
    if (path[0] == '/' && path[1] == '\0') {
        return true;
    }
    if (path[0] == '\0') {
        return true;
    }
    return false;
}

bool isCurrent (char *path) {
    if (path[0] == '.' && path[1] == '\0') {
        return true;
    }
    return false;
}

bool isLevelUp (char *path) {
    if (path[0] == '.' && path[1] == '.' && path[2] == '\0') {
        return true;
    }
    return false;
}


bool isRelative (char *path) {
    if (path[0] == '/') {
        return false;
    }
    return true;
}