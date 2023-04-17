#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "noeud.h"
#include "cmd/ls.h"
#include "cmd/touch.h"
#include "cmd/print.h"
#include "cmd/cd.h"
#include "cmd/pwd.h"

#define MAX_CMD_LEN 100

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <command_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // ouvrir le fichier de commandes
    FILE *cmd_file = fopen(argv[1], "r");
    if (cmd_file == NULL)
    {
        printf("Error: could not open command file: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    noeud *root = create_root_node();

    // mettre le répertoire courant à la racine
    noeud *current_dir = root;

    add_child(current_dir, create_node(true, "test", current_dir, NULL));

    noeud *test1 = create_node(true, "test1", current_dir, NULL);
    add_child(current_dir, test1);
    noeud *test2 = create_node(true, "test2", test1, NULL);
    add_child(test1, test2);

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
            print_noeud(current_dir);
        }
        else if (strcmp(arg, "cd") == 0)
        {
            arg = strtok(NULL, " ");
            current_dir = cd(arg, current_dir);
        }
        else if (strcmp(arg, "pwd") == 0)
        {
            char *pwd_output = pwd(current_dir);
            printf("%s\n", pwd_output);
            free(pwd_output);
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
