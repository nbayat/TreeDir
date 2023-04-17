#ifndef PRINT_NOEUD_H
#define PRINT_NOEUD_H

#include "../noeud.h"

// ce fonction seulement verifie si le noeud est null ou non
// et si il est null, elle affiche un message d'erreur
// sinon elle appelle la fonction print_noeud de noeud.h
// qui s'occupe de l'affichage recursivement

void print_noeud(noeud *n);

#endif
