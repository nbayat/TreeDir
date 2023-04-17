#ifndef PWD_H
#define PWD_H

#include "../noeud.h"

/*
La fonction "pwd" prend un nœud en entrée et renvoie le chemin d'accès sous forme de chaîne de caractères en concaténant les noms de tous les nœuds parents jusqu'à la racine. Si le nœud passé en entrée est la racine, la fonction renvoie simplement une chaîne vide.
*/

char *pwd(noeud *n);

#endif