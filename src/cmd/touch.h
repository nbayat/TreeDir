#ifndef TOUCH_H
#define TOUCH_H

#include "../noeud.h"

/*
La fonction "touch" crée un nouveau nœud avec un nom de fichier donné, l'associe au nœud parent dans une structure d'arborescence, et l'ajoute comme enfant.
*/

void touch(noeud *parent, char *filename);

#endif
