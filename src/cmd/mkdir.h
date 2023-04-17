#ifndef MAKDIR_H
#define MAKDIR_H

#include "../noeud.h"

// mkdir : crée un dossier dans le répertoire parent avec le nom donné après vérification de la validité du nom

void mkdir(char nom[100], noeud *parent);

#endif