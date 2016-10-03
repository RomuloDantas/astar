#ifndef ASTAR_LIST_H
#define ASTAR_LIST_H

/**
 * Estrutura que reprensenta um nó.
 */
typedef struct node {
    unsigned char weight;
    struct node *next;
    unsigned char close;
    struct node *parent;
    int f;
    int h;
    int g;
    unsigned char x;
    unsigned char y;

} node;

/**
 * Cria um novo nó na posição (x,y) e com o pesso
 * weight.
 * @param x - a posição x do nó.
 * @param y - a posição y do nó.
 * @param weight  - o peso do nó.
 * @return  - o nó criado.
 */
node init_node( unsigned char x,  unsigned char y, unsigned char weight);

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


#endif //ASTAR_LIST_H
