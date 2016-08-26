#include<stdlib.h>
#include <stdio.h>
#include "list.h"

node *open_list = NULL;
node *close_list = NULL;

/**
 * Recupera o nó com menor f na lista aberta (open list).
 * @return o nó com menor f.
 */
node *lowest_f() {
    node *current = open_list;
    node *lowest_f = current;
    while (current != NULL) {
        if (current->f < lowest_f->f) {
            lowest_f = current;
        }
        current = current->next;
    }
    return lowest_f;
}

/**
 * Verificar se o nó alcançado é o objetivo.
 * @param n - o nó alcançado.
 * @param end_point - o objetivo.
 * @return 1 caso o nó seja o objetivo, 0 caso contrário.
 */
int is_finish(node *n, node *end_point) {
    if (n->x == end_point->x && n->y == end_point->y) {
        return 1;
    }
    return 0;
}

/**
 * Calcula o heurística
 * @param n - o nó para o cálculo.
 * @param finish - o nó final para o cálculo da heurística.
 * @return o resultado co calculo.
 */
int heuristic(node *n, node *finish) {
    return 10 * (abs(n->x - finish->x) + abs(n->y - finish->y));
}

/**
 * Calcula o valor de G entre o ponto atual e o seu vizinho.
 * @param current - o nó atual.
 * @param neighbor - o vizinho.
 * @return o valor de G entre current e neighbor.
 */
int calc_g(node current, node neighbor) {

    int dist = 0;
    if (current.x == neighbor.x || current.y == neighbor.y) {
        dist = 10;
    } else {
        dist = 14;
    }
    return current.g + dist;

}

/**
 * Atualzia o valor de F para o no.
 * @param n - o nó para atualziar o valor
 * de F.
 */
void update_f(node *n) {
    n->f = n->g + n->h + n->weight;
}

/**
 * Atualiza os parâmetros (g,f,h, parent) do nó vizinho ao nó atual.
 * @param current - o nó atual.
 * @param neighbor - o nó vizinho para atualizar os parâmetros.
 * @param end_node - o nó final usado nos cálculos.
 */
void update_params(node *current, node *neighbor, node end_point) {
    int new_g = calc_g(*current, *neighbor);
    if (new_g < neighbor->g || neighbor->g == -1) {
        neighbor->g = new_g;
        neighbor->parent = current;
    }

    neighbor->h = heuristic(neighbor, &end_point);

    update_f(neighbor);
}

/**
 * Mostra o grid marcado com 'X' no caminho pecorrido.
 * @param linhas - o  núemro de linhas do grid.
 * @param colunas - o númeor de colunas do grid.
 * @param grid - o grid pecorrido.
 */
void show_map_result(int linhas, int colunas, node grid[linhas][colunas]) {
    for (int x = 0; x < linhas; x++) {
        for (int y = 0; y < colunas; y++) {
            if (grid[x][y].weight == -1) {
                printf("%c   ", 'X');
            } else {
                if (grid[x][y].weight < 9) {
                    printf("%d   ", grid[x][y].weight);
                } else if (grid[x][y].weight < 99) {
                    printf("%d  ", grid[x][y].weight);
                } else {
                    printf("%d ", grid[x][y].weight);
                }
            }
        }
        printf("\n");
    }
}

/**
 * Mostra o resultado do algoritmo.
 * @param n - o ultimo nó alcançado.
 * @param linhas - o número de linhas do grid.
 * @param colunas - o númeor de colunas do grid.
 * @param grid - o grid pecorrido.
 */
void show_result(node *n, int linhas, int colunas, node grid[linhas][colunas]) {
    printf("Caminho pecorrido:\n(%d, %d) ", n->x, n->y);
    grid[n->x][n->y].weight = -1;
    if (n->parent != NULL) {
        do {
            printf("(%d, %d) ", n->parent->x, n->parent->y);
            grid[n->parent->x][n->parent->y].weight = -1;
            n = n->parent;
        } while (n->parent != NULL);
    }
    printf("\n");

    show_map_result(linhas, colunas, grid);
}

/**
 * Verifica se o nó é uma parede.
 * @param o nó para ser verificado
 * @return 1 se o nó for uma barreira, 0 caso contrário.
 */
int isWall(node *n){
    if (n->weight == 255) {
        return 1;
    }
    return 0;
}

/**
 * busca um caminho do ponto de start até o ponto end na grid.
 * @param start_node - ponto de partida.
 * @param end_point - ponto de chegada.
 * @param linhas - número de linhas do grid.
 * @param colunas - numero de colunas do grid.
 * @param grid - o grid para ser pecorrido.
 */
void find_path(node *start_node, node end_point, int linhas, int colunas, node grid[linhas][colunas]) {

    //insere o start point na lista de open
    insert_node(&open_list, start_node);

    while (open_list != NULL) {
        //print_list(open_list);
        node *current = lowest_f();
        //printf("current (%d, %d) \n", current->x, current->y);
        if (is_finish(current, &end_point)) {
            show_result(current, linhas, colunas, grid);
            return;
        }

        remove_node(&open_list, current);
        insert_node(&close_list, current);

        //Checando a vizinhança
        //checar em caso de borda

        for (int x = current->x - 1; x <= current->x + 1;
             x++) {
            if (x <= -1 || x >= linhas) {
                continue;
            }
            for (int y = current->y - 1; y <= current->y + 1; y++) {
                if (y <= -1 || y >= colunas) {
                    continue;
                }

                //avoid reinsert the current node at open list
                if (x == current->x && y == current->y) {
                    continue;
                }


                node *neighbor = &(grid[x][y]);

                //Vizinho ja analisado.
                if (contains_node(&close_list, neighbor)) {
                    continue;
                }

                //Wall
                if (isWall(neighbor)) {
                    continue;
                }

                if (!contains_node(&open_list, neighbor)) {
                    insert_node(&open_list, neighbor);
                }

                update_params(current, neighbor, end_point);

                //printf("[%d][%d] - G=%d   H=%d  W=%d  F=%d\n", x, y, neighbor->g, neighbor->h, neighbor->weight, neighbor->f);

            }
        }
    }
    printf("Sem caminho");
    return;
}



