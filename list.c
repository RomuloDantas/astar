#include <stdio.h>
#include "list.h"

/**
 * Cria um novo nó na posição (x,y) e com o pesso
 * weight.
 * O nó criado é inicializado com valores padões para
 * next, parent, f, g e h.
 * @param x - a posição x do nó.
 * @param y - a posição y do nó.
 * @param weight  - o peso do nó.
 * @return  - o nó criado.
 */
node init_node(int x, int y, unsigned char weight) {
    node n;
    n.next = NULL;
    n.parent = NULL;
    n.x = x;
    n.y = y;
    n.f = -1;
    n.g = -1;
    n.h = -1;
    n.weight = weight;
    return n;
}

/**
 * Insere um nó na lista.
 * @param list - lista onde o nó será inserido.
 * @param n - o nó que será inserido.
 */
void inline insert_node(node **list, node *n) {
    if (*list == NULL) {
        *list = n;
    } else {
        n->next = *list;
        *list = n;
    }

}

/**
 * Remove um nó da lista.
 * @param list - lista de onde o nó será removido.
 * @param n - o nó que será removido.
 */
void inline remove_node(node **list, node *n) {
    if (*list != NULL) {
        //lista vazia
        if ((*list)->next == NULL) {
            //lista com 1 elemento
            *list = NULL;
        } else {
            node *current = *list;
            if (current == n) { 
                node *aux = (*list)->next;
                (*list)->next = NULL;
                *list = aux;
            } else {
                while (n != current->next) {
                    current = current->next;
                }
                current->next = current->next->next;
                n->next = NULL;
            }


        }

    }
}

/**
 * Verifica se dado nó esta contido na lista.
 * @param list - a lista que será consultada.
 * @param n  - o nó para a consulta.
 * @return  1 se a lista contém o nó, caso contrário, 0.
 */
int contains_node(node **list, node *n) {
    if (*list == NULL) {
        return 0;
    }

    node *current = *list;
    do {
        if (current == n) {
            return 1;
        }
        current = current->next;
    } while (current != NULL);


    return 0;
}
