#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "noeud.h"
#include "cmd/ls.h"

#define MAX_CMD_LEN 100


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <command_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // ouvrir le fichier de commandes
    FILE *cmd_file = fopen(argv[1], "r");
    if (cmd_file == NULL) {
        printf("Error: could not open command file: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // créer le noeud racine du système de fichiers
    noeud *root = (noeud*)malloc(sizeof(noeud));
    root->est_dossier = true;
    strcpy(root->nom, "/");
    root->pere = NULL;
    root->racine = root;
    root->fils = NULL;

    // mettre le répertoire courant à la racine
    noeud *current_dir = root;

    // boucle sur le fichier de commandes et exécute chaque commande
    char cmd[MAX_CMD_LEN];
    while (fgets(cmd, MAX_CMD_LEN, cmd_file) != NULL) {
        // supprimer le caractère de fin de ligne du string de commande
        cmd[strcspn(cmd, "\n")] = '\0';

        // découper la chaîne de caractères en arguments
        char *arg = strtok(cmd, " ");

        if (strcmp(arg, "ls") == 0) {
            ls(current_dir);
        } else {
            printf("Unknown command: %s\n", arg);
        }
    }

    // libérer la mémoire et fermer le fichier de commandes
    free(root);
    fclose(cmd_file);

    return EXIT_SUCCESS;
}
