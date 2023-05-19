// les bibliothèques standards
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// structure de données
#include "noeud.h"

// les commandes
#include "cmd/ls.h"
#include "cmd/touch.h"
#include "cmd/print.h"
#include "cmd/cd.h"
#include "cmd/pwd.h"
#include "cmd/mkdir.h"
#include "cmd/rm.h"
#include "cmd/cp.h"
#include "cmd/mv.h"
// debug mode
#include "debug.h"

#define MAX_CMD_LEN 100

int main(int argc, char *argv[])
{
    if (DEBUG)
    {
        printf("! Attention: debug mode !\n");
    }
    else
    {
        printf("! Attention: running non debug ... !\n");
    }

    if (argc != 2)
    {
        printf("Usage: %s <command_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // ouvrir le fichier de commandes
    FILE *cmd_file = fopen(argv[1], "r");
    if (cmd_file == NULL)
    {
        printf("Erreur: impossible d'ouvrir le fichier de commandes (référence_de_l'erreur_MAIN02) \n");
        fclose(cmd_file);
        exit(EXIT_FAILURE);
    }

    noeud *root = create_root_node();

    // mettre le répertoire courant à la racine
    noeud *current_dir = root;

    // boucle sur le fichier de commandes et exécute chaque commande
    char cmd[MAX_CMD_LEN];
    while (fgets(cmd, MAX_CMD_LEN, cmd_file) != NULL)
    {
        // supprimer le caractère de fin de ligne du string de commande
        cmd[strcspn(cmd, "\n")] = '\0';

        // découper la chaîne de caractères en arguments
        char *arg = strtok(cmd, " ");

        if (strcmp(arg, "ls") == 0)
        {
            ls(current_dir);
        }
        else if (strcmp(arg, "touch") == 0)
        {
            arg = strtok(NULL, " ");
            touch(current_dir, arg);
        }
        else if (strcmp(arg, "print") == 0)
        {
            // print_noeud(current_dir);
            printNo(current_dir->racine);
        }
        else if (strcmp(arg, "cd") == 0)
        {
            arg = strtok(NULL, " ");
            current_dir = cd(arg, current_dir);
        }
        else if (strcmp(arg, "pwd") == 0)
        {
            char *pwd_output = pwd(current_dir);
            printf("[pwd]: \n%s\n\n", pwd_output);
            free(pwd_output);
        }
        else if (strcmp(arg, "mkdir") == 0)
        {
            arg = strtok(NULL, " ");
            mkdir(arg, current_dir);
        }
        else if (strcmp(arg, "rm") == 0)
        {
            arg = strtok(NULL, " ");
            rm(arg, current_dir);
        }
        else if (strcmp(arg, "cp") == 0)
        {
            char *arg1 = strtok(NULL, " ");
            char *arg2 = strtok(NULL, " ");
            // printf("cp %s %s\n", arg1, arg2);
            cp(arg1, arg2, current_dir);
        }
        else if (strcmp(arg, "mv") == 0)
        {
            char *arg1 = strtok(NULL, " ");
            char *arg2 = strtok(NULL, " ");
            // printf("mv %s %s\n", arg1, arg2);
            mv(arg1, arg2, current_dir);
        }
        else
        {
            printf("Error: unknown command: %s\n", arg);
        }
    }

    // libérer la mémoire et fermer le fichier de commandes
    free(root);
    fclose(cmd_file);

    return EXIT_SUCCESS;
}
