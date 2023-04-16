#include "../noeud.h"
#include <stdio.h>

void print(noeud *n) {
    if(n == NULL) {
        return;
    }
    print_noeud(n);
}
