#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "astar.h"

int main() {



    node grid[10][10];
    int i;
    for (i = 0; i < 10; i++) {
        int j;
        for (j = 0; j < 10; j++) {
            grid[i][j] = init_node(i, j, 0);
        }
    }

    grid[2][2].weight=255;
    grid[7][6].weight=255;
    grid[2][3].weight=255;

    node start_node = grid[1][1];
    start_node.g = 0;
    start_node.h = 0;
    start_node.f = start_node.g + start_node.h;

    node end_node = grid[5][5];


    find_path(start_node, end_node, 10, 10, grid);


    // test();


}

void test() {
    node *head_open = NULL;


    node *n = (struct node *) malloc(sizeof(struct node));
    n->g = 10;
    node *n2 = (struct node *) malloc(sizeof(struct node));
    n2->g = 20;
    node *n3 = (struct node *) malloc(sizeof(struct node));
    n3->g = 30;
    insert_node(&head_open, n);
    insert_node(&head_open, n2);
    insert_node(&head_open, n3);

    node *aux = head_open;
    while (aux != NULL) {
        printf("%d\n", aux->g);
        aux = aux->next;
    }
}

