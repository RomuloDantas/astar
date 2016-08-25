#ifndef ASTAR_ASTAR_H
#define ASTAR_ASTAR_H

#include "list.h"

int find_path(node *start_node, node end_point, int i, int j, node grid[i][j]);

node *lowest_f();

int is_finish(node *n, node *end_point);

int heuristic(node *n, node *finish);

void update_params(node current, node *neighbor);

#endif //ASTAR_ASTAR_H
