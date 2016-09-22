/*********************************************************************
 *
 * Filename:      astar.c
 * Version:       1.0
 * Description:   Funções que realizam as ações utilizadas pelo algoritmo A*, 
 *                assim como a pŕopria implementação da função principal do
 *                algoritmo.
 * 
 * Author(s):     Romulo Dantas <romulocicero@gmail.com>
 *                David Sanford <dsanfordseu@gmail.com>
 *
 ********************************************************************/
#include "astar.h"

struct node *open_list = NULL;
struct node *close_list = NULL;

/**
 * Recupera o nó com menor f na lista aberta (open list).
 * @return o nó com menor f.
 */
node *lowest_f() {
    node *current = open_list;
    node *lowest_f = current;
    while (current != NULL) {
        if ((current->g + current->h + current->point->weight) < (lowest_f->g+lowest_f->h+lowest_f->point->weight)) {
            lowest_f = current;
        }
        current = current->next;
    }
    return lowest_f;
}

/**
 * Verifica se o nó alcançado é o nó objetivo.
 * @param n - o nó alcançado.
 * @param end_point - o nó objetivo.
 * @return 1 caso o nó seja o objetivo, 0 caso contrário.
 */
bit is_finish(node *n, node *end_point) {
    if (n->point->x == end_point->point->x && n->point->y == end_point->point->y) {
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
    return 10 * (abs(n->point->x - finish->point->x) + abs(n->point->y - finish->point->y));
}

/**
 * Calcula o valor de G entre o ponto atual e o seu vizinho.
 * @param current - o nó atual.
 * @param neighbor - o vizinho.
 * @return o valor de G entre current e neighbor.
 */
int calc_g(node current, node neighbor) {

    int dist = 0;
    if (current.point->x == neighbor.point->x || current.point->y == neighbor.point->y) {
        dist = 10;
    } else {
        dist = 14;
    }
    return current.g + dist;

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
}

/**
 * Envia um ponto pela serial.
 * O ponto será mostrado no formato: (x, y).
 * @param n o nó contendo as informaçes de x e y.
 */
void print_point(node *n) {
    putsUSART("(");
    char bufx[2];
    itoa(bufx, n->point->x, 10);
    putsUSART(bufx);
    putsUSART(", ");

    char bufy[2];
    itoa(bufy, n->point->y, 10);

    putsUSART(bufy);
    putsUSART(") ");
}

/**
 * Mostra o grid com o caminho que o algoritmo encontrou
 * marcado com 'X'.
 * @param linhas - o  núemro de linhas do grid.
 * @param colunas - o númeor de colunas do grid.
 * @param grid - o grid pecorrido.
 */
void show_map_result(node grid[LINHAS][COLUNAS]) {   
    for (int a = 0; a < LINHAS; a++) {      
        for (int b = 0; b < COLUNAS; b++) {  
            int w = grid[a][b].point->weight;
                                           
            if (grid[a][b].g == -2) {
                putsUSART("X    ");
            } else {               
                char buf[5];                      
                utoa(buf, w, 10);              
                putsUSART(buf);  
                if(w < 9){
                     putsUSART("    ");
                } else if (w < 99) {
                    putsUSART("   ");
                } else {
                    putsUSART("  ");  
                }
            }
        }
        putsUSART("\n\r");
    }
}

/**
 * Mostra o resultado do algoritmo.
 * @param n - o ultimo nó alcançado.
 * @param linhas - o número de linhas do grid.
 * @param colunas - o númeor de colunas do grid.
 * @param grid - o grid pecorrido.
 */
void show_result(node *n, node grid[LINHAS][COLUNAS]) {
   // putsUSART("Caminho pecorrido:\n\r"); 
    
    grid[n->point->x][n->point->y].g = -2;
    if (n->parent != NULL) {
        do {           
            grid[n->parent->point->x][n->parent->point->y].g = -2;
            n = n->parent;
        } while (n->parent != NULL);
    }   

    show_map_result(grid);
}

/**
 * Verifica se o nó é intransponível. 
 * U nó é instransponível quando seu valor é 255.
 * @param o nó para ser verificado
 * @return 1 se o nó for intransponível, 0 caso contrário.
 */
bit is_wall(node *n) {
    if (n->point->weight == 255) {
        return 1;
    }
    return 0;
}

/**
 * Busca um caminho do ponto de partida até o ponto de chegada no grid.
 * @param start_node - ponto de partida.
 * @param end_point - ponto de chegada.
 * @param linhas - número de linhas do grid.
 * @param colunas - numero de colunas do grid.
 * @param grid - o grid para ser pecorrido.
 */
void find_path(node *start_node, node end_point, node grid[LINHAS][COLUNAS]) {
    insert_node(&open_list, start_node);

    while (open_list != NULL) {
        node *current = lowest_f();
        if (is_finish(current, &end_point)) {
            putsUSART("Ponto de partida: ");
            print_point(start_node);   
            putsUSART("\n\r");
            putsUSART("Ponto de chegada: ");
            print_point(&end_point);           
            putsUSART("\n\r");
            show_result(current, grid);
            return;
        }

        remove_node(&open_list, current);
        insert_node(&close_list, current);

        for (int x = current->point->x - 1; x <= current->point->x + 1;
             x++) {            
            if (x <= -1 || x >= LINHAS) {
                continue;
            }
            for (int y = current->point->y - 1; y <= current->point->y + 1; y++) {
                if (y <= -1 || y >= COLUNAS) {
                    continue;
                }

                //Evita que o nó atual seja reinserido na lista.
                if (x == current->point->x && y == current->point->y) {
                    continue;
                }

                node *neighbor = &(grid[x][y]);

                if (contains_node(&close_list, neighbor)) {
                //Vizinho já analisado.
                    continue;
                }

                if (is_wall(neighbor)) {
                    continue;
                }

                if (!contains_node(&open_list, neighbor)) {
                    insert_node(&open_list, neighbor);
                }

                update_params(current, neighbor, end_point);
            }
        }
    }
    putsUSART("Sem caminho!\n\r");
    show_map_result(grid);    
}
