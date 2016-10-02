#ifndef ASTAR_LIST_H
#define ASTAR_LIST_H

/**
 * Estrutura que reprensenta um nó.
 */
typedef struct node {
    struct node *parent;
    struct node *next;
    int x, y;
    int g;
    int h;
    int f;
    int weight;
    unsigned char close;
} node;

/**
 * Cria um novo nó na posição (x,y) e com o pesso
 * weight.
 * @param x - a posição x do nó.
 * @param y - a posição y do nó.
 * @param weight  - o peso do nó.
 * @return  - o nó criado.
 */
node init_node(int x, int y, int weight);

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
void remove_node(node **list, node *n);

/**
 * Verifica se dado nó esta contido na lista.
 * @param list - a lista que será consultada.
 * @param n  - o nó para a consulta.
 * @return  1 se a lista contém o nó, caso contrário, 0.
 */
int contains_node(node **list, node *n);

/**
 * Imprime uma lista.
 * @param list a lista a ser impressa.
 */
void print_list(node *list);


#endif //ASTAR_LIST_H
