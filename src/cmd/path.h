#ifndef PATH_H
#define PATH_H

#include "../noeud.h"

// les commandes sont explicites

bool isCurrent(char *path);
bool isLevelUp(char *path);
bool isRelative(char *path);
bool isReturnToRoot(char *path);
bool isValidPath(char *path, noeud *dir);

#endif