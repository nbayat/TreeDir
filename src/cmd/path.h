#ifndef PATH_H
#define PATH_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../noeud.h"

bool isCurrent(char *path);
bool isLevelUp(char *path);
bool isRelative(char *path);
bool isReturnToRoot(char *path);
bool isValidPath(char *path, noeud *dir);

#endif