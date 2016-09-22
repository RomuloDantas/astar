/*********************************************************************
 *
 * Filename:      list.c
 * Version:       1.0
 * Description:   Funções que realizam as ações nas listas (open_list e 
 *                close_list) utlizadas pelo algoritmo A*.
 * 
 * Author(s):     Romulo Dantas <romulocicero@gmail.com>
 *                David Sanford <dsanfordseu@gmail.com>
 *
 ********************************************************************/
#include <usart.h>

#include "list.h"

/**
 * Inicializa um novo nó na posição (x,y) e com o peso
 * 
 * @param *n - um ponteiro para o nó que será inicializado
 */
void init_node(node *n) {   
    n->next = NULL;
    n->parent = NULL;   
    n->g = -1;
    n->h = -1;     
}

/**
 * Insere um nó na lista.
 * @param list - lista onde o nó será inserido.
 * @param n - o ponteiro para o nó que será inserido.
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
 * @param n - o ponteiro para o nó que será removido.
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
