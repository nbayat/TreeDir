#ifndef RM_H
#define RM_H

#include "../noeud.h"

/*
Cette fonction supprime un nœud dans une structure d'arborescence représentant un système de fichiers. Elle utilise un chemin de fichier et un nœud courant de répertoire en entrée, met à jour le nœud courant et le retire du répertoire parent. Enfin, elle libère la mémoire du nœud courant.
*/

void rm(char *path, noeud *curr_dir);

#endif