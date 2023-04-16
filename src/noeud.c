#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "noeud.h"

// cree un nouveau noeud et initialise ses champs
noeud* create_node(bool est_dossier, char nom[100], noeud* pere, liste_noeud* fils) {
    // alloue de la memoire pour le nouveau noeud
    noeud* node = (noeud*)malloc(sizeof(noeud));
    if (node == NULL) {
        assert("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    // Initialise les champs du noeud
    node->est_dossier = est_dossier;
    strncpy(node->nom, nom, sizeof(node->nom));
    // si le noeud a un parent, on definit son noeud racine comme etant le noeud 
    // racine du parent, sinon on definit son noeud racine comme etant lui meme
    if (pere != NULL) {
        node->pere = pere->pere;
    } else {
        node->pere = node;
    }
    if (fils != NULL) {
        node->fils = fils;
    } else {
        node->fils = NULL;
    }
    return node;
}

// cree un noeud racine qui pointe sur lui meme
noeud* create_root_node() {
    noeud* root = create_node(true, "", NULL, NULL);
    return root;
}


// ajoute un noeud enfant a un noeud parent
void add_child(noeud* parent, noeud* child) {
    //: alloue de la memoire pour le nouveau noeud enfant
    liste_noeud* new_child_list = (liste_noeud*)malloc(sizeof(liste_noeud));
    if (new_child_list == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    // initialise les champs du nouveau noeud enfant
    new_child_list->no = child;
    new_child_list->succ = NULL;
    // ajoute le nouveau noeud enfant a la liste des noeuds enfants du noeud parent
    if (parent->fils == NULL) {
        parent->fils = new_child_list;
    } else {
        liste_noeud* curr = parent->fils;
        while (curr->succ != NULL) {
            curr = curr->succ;
        }
        curr->succ = new_child_list;
    }
}

// supprime un noeud enfant d'un noeud parent
void remove_child(noeud* parent, noeud* child) {
    // Find the child node in the parent's list of children
    liste_noeud* prev = NULL;
    liste_noeud* curr = parent->fils;
    while (curr != NULL) {
        if (curr->no == child) {
            break;
        }
        prev = curr;
        curr = curr->succ;
    }
    // si le noeud enfant n'est pas trouve, on ne fait rien
    if (curr == NULL) {
        return;
    }
    // supprime le noeud enfant de la liste des noeuds enfants du noeud parent
    if (prev == NULL) {
        parent->fils = curr->succ;
    } else {
        prev->succ = curr->succ;
    }
    free(curr);
}

int nb_children(noeud* node) {
    int num_children = 0;
    liste_noeud* child = node->fils;
    while (child != NULL) {
        num_children++;
        child = child->succ;
    }
    return num_children;
}

void print_noeud(noeud* node) {
    // Print nom
    printf("%s ", node->nom);

    // Print nb de fils
    int num_children = nb_children(node);
    printf("(%d): ", num_children);

    // Print nom et type de chaque fils
    liste_noeud* child = node->fils;
    while (child != NULL) {
        printf("%s", child->no->nom);
        if (child->no->est_dossier) {
            printf("(D) ");
        } else {
            printf(" ");
        }
        child = child->succ;
    }
    printf("\n");

    // print les fils recursivement
    child = node->fils;
    while (child != NULL) {
        if (child->no->est_dossier) {
            print_noeud(child->no);
        }
        child = child->succ;
    }
}

void print_children(noeud* node) {
    // Print nom et type de chaque fils
    liste_noeud* child = node->fils;
    while (child != NULL) {
        printf("%s", child->no->nom);
        if (child->no->est_dossier) {
            printf("(D) ");
        } else {
            printf(" ");
        }
        child = child->succ;
    }
    printf("\n");
}

bool have_child(noeud* parent, noeud* child) {
    liste_noeud* curr = parent->fils;
    while (curr != NULL) {
        if (curr->no == child) {
            return true;
        }
        curr = curr->succ;
    }
    return false;
}

noeud* find_child(noeud* parent, char nom[100]) {
    liste_noeud* curr = parent->fils;
    while (curr != NULL) {
        if (strcmp(curr->no->nom, nom) == 0) {
            return curr->no;
        }
        curr = curr->succ;
    }
    return NULL;
}

noeud* find_node(noeud* root, char nom[100]) {
    // si le noeud courant est le noeud recherche, on retourne le noeud courant
    if (strcmp(root->nom, nom) == 0) {
        return root;
    }
    // sinon on cherche le noeud recherche dans les noeuds enfants du noeud courant
    liste_noeud* curr = root->fils;
    while (curr != NULL) {
        noeud* found = find_node(curr->no, nom);
        if (found != NULL) {
            return found;
        }
        curr = curr->succ;
    }
    return NULL;
}

// libere la memoire allouee pour un noeud et ses enfants recursivement
void free_node(noeud* node) {
    // libere la memoire allouee pour les noeuds enfants du noeud courant et ses enfants recursivement
    liste_noeud* curr = node->fils;
    while (curr != NULL) {
        free_node(curr->no);
        liste_noeud* temp = curr;
        curr = curr->succ;
        free(temp);
    }
    // libere la memoire allouee pour le noeud courant
    free(node);
}
