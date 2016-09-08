#ifndef ASTAR_LIST_H
#define ASTAR_LIST_H

#include <stdio.h>

/**
 * Estrutura que reprensenta um nó.
 */
typedef struct node {
    struct node *parent;
    struct node *next;  
    int g;
    int h;
    int f;      
    struct point *point;
} node;

typedef struct point {
    int x, y, weight;
} point;


/**
 * Cria um novo nó na posição (x,y) e com o pesso
 * weight.
 * @param x - a posição x do nó.
 * @param y - a posição y do nó.
 * @param weight  - o peso do nó.
 * @return  - o nó criado.
 */
void init_node(node *n);

/**
 * Insere um nó na lista.
 * @param list - lista onde o nó será inserido.
 * @param n - o nó que será inserido.
 */
void insert_node(node **list, node *n);

/**
 * Remove um n ó da lista.
 * @param list - lista de onde o nó será removido.
 * @param n - o nó que será removido.
 */
void remove_node(struct node **list, struct node *n);

/**
 * Verifica se dado nó esta contido na lista.
 * @param list - a lista que será consultada.
 * @param n  - o nó para a consulta.
 * @return  1 se a lista contém o nó, caso contrário, 0.
 */
int contains_node(struct node **list, struct node *n);

/**
 * Imprime uma lista.
 * @param list a lista a ser impressa.
 */
void print_list(node *list);


#endif //ASTAR_LIST_H
