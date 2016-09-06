#include <usart.h>

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
void init_node(node *n) {   
    n->next = NULL;
    n->parent = NULL;    
    n->f = -1;
    n->g = -1;
    n->h = -1;     
}

void get_cell(int x, int y){
    
}

/**
 * Insere um nó na lista.
 * @param list - lista onde o nó será inserido.
 * @param n - o nó que será inserido.
 */
void insert_node(node **list, node *n) {
    if (*list == NULL) {
        *list = n;
    } else {
        node *current = *list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = n;
    }

}

/**
 * Remove um nó da lista.
 * @param list - lista de onde o nó será removido.
 * @param n - o nó que será removido.
 */
void remove_node(node **list, node *n) {
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

/**
 * Imprime uma lista.
 * @param list a lista a ser impressa.
 */
void print_list(node *list) {
    if (list == NULL) {
        putsUSART("Empty list\r");
        return;
    }

    node *current = list;
    do {
       // printf("(%d, %d) - ", current->x, current->y);
        current = current->next;
    } while (current != NULL);

    printf("\n");


}
