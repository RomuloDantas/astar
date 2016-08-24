#include<stdlib.h>
#include <stdio.h>
#include "list.h"

node *open_list = NULL;
node *close_list = NULL;

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

int is_finish(node *n, node *end_point) {
    if (n->x == end_point->x && n->y == end_point->y) {
        return 1;
    }
    return 0;
}

int heuristic(node *n, node *finish) {
    return 10*(abs(n->x - finish->x) + abs(n->y - finish->y));
}

int calc_g(node current, node neighbor) {

    int dist = 0;
    if (current.x == neighbor.x || current.y == neighbor.y) {
        dist = 10;
    } else {
        dist = 14;
    }
    return current.g + dist;

}

void update_f(node *n) {
    n->f = n->g + n->h;
}

void update_params(node *current, node *neighbor, node end_point) {
    int new_g = calc_g(*current, *neighbor);
    if (new_g < neighbor->g || neighbor->g == -1) {
        neighbor->g = new_g;
        neighbor->parent = current;
    }

    neighbor->h = heuristic(neighbor, &end_point);

    update_f(neighbor);
}


int find_path(node start_node, node end_point, int i, int j, node grid[i][j]) {

    //insere o start point na lista de open
    insert_node(&open_list, &start_node);

    while (open_list != NULL) {
        print_list(open_list);
        node *current = lowest_f();
        printf("current (%d, %d) \n", current->x, current->y);
        if (is_finish(current, &end_point)) {


            node *aux = current;
            printf(">>>>(%d, %d) ", current->x, current->y);
           if(current->parent != NULL){
                do{
                    printf("(%d, %d) ", current->parent->x, current->parent->y);
                    current = current->parent;
                }while(current->parent != NULL);
           }


            printf("\nfinish!");
            return 0;
        }

        remove_node(&open_list, current);
        insert_node(&close_list, current);

        //Checando a vizinhança
        //checar em caso de borda

        for (int x = current->x - 1;  x <= current->x + 1;
             x++) {
            if(x <= -1 || x >= i){
                continue;
            }
            for (int y = current->y - 1; y <= current->y + 1; y++) {
                if(y <= -1 || y >= i){
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
                if (neighbor->weight == 255) {
                    continue;
                }

                if (!contains_node(&open_list, neighbor)) {
                    insert_node(&open_list, neighbor);
                }

                update_params(current, neighbor, end_point);

                printf("[%d][%d] - G=%d    H=%d   F=%d\n", x, y, neighbor->g, neighbor->h, neighbor->f);

            }
        }
    }
}



