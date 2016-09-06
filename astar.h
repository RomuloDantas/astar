#ifndef ASTAR_ASTAR_H
#define ASTAR_ASTAR_H

#include <stdlib.h>
#include <stdio.h>
#include <plib/usart.h>

#include "list.h"

#define LINHAS 11
#define COLUNAS 11

/**
 * busca um caminho do ponto de start até o ponto end na grid.
 * @param start_node - ponto de partida.
 * @param end_point - ponto de chegada.
 * @param linhas - número de linhas do grid.
 * @param colunas - numero de colunas do grid.
 * @param grid - o grid para ser pecorrido.
 */
void find_path(node *start_node, node end_point, node grid[LINHAS][COLUNAS]);

/**
 * Recupera o nó com menor f na lista aberta (open list).
 * @return o nó com menor f.
 */
node *lowest_f();

/**
 * Verificar se o nó alcançado é o objetivo.
 * @param n - o nó alcançado.
 * @param end_point - o objetivo.
 * @return 1 caso o nó seja o objetivo, 0 caso contrário.
 */
bit is_finish(node *n, node *end_point);

/**
 * Calcula o heurística
 * @param n - o nó para o cálculo.
 * @param finish - o nó final para o cálculo da heurística.
 * @return o resultado co calculo.
 */
int heuristic(node *n, node *finish);

/**
 * Atualiza os parâmetros (g,f,h, parent) do nó vizinho ao nó atual.
 * @param current - o nó atual.
 * @param neighbor - o nó vizinho para atualizar os parâmetros.
 * @param end_node - o nó final usado nos cálculos.
 */
void update_params(node *current, node *neighbor, node end_node);

/**
 * Clean up the open list and the close list
 */
void clean_up();

#endif //ASTAR_ASTAR_H
