/*********************************************************************
 *
 * Filename:      list.h
 * Version:       1.0
 * Description:   Cabeçalho das funções que realizam as ações nas listas 
 *                (open_list e close_list) utlizadas pelo algoritmo A*.
 * 
 * Author(s):     Romulo Dantas <romulocicero@gmail.com>
 *                David Sanford <dsanfordseu@gmail.com>
 * 
 ********************************************************************/
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
    struct point *point;   
} node;

/**
 * Estrutura que representa os pontos de 
 * um mapa com seu respectivo peso.
 */
typedef struct point {
    int x, y, weight;
} point;

/**
 * Inicializa um novo nó na posição (x,y) e com o peso
 * 
 * @param *n - um ponteiro para o nó que será inicializado
 */
void init_node(node *n);

/**
 * Insere um nó na lista.
 * @param list - lista onde o nó será inserido.
 * @param n - o ponteiro para o nó que será inserido.
 */
void insert_node(node **list, node *n);

/**
 * Remove um nó da lista.
 * @param list - lista de onde o nó será removido.
 * @param n - o ponteiro para o nó que será removido.
 */
void remove_node(struct node **list, struct node *n);

/**
 * Verifica se dado nó esta contido na lista.
 * @param list - a lista que será consultada.
 * @param n  - o nó para a consulta.
 * @return  1 se a lista contém o nó, caso contrário, 0.
 */
int contains_node(struct node **list, struct node *n);

#endif //ASTAR_LIST_H
