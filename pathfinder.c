#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "astar.h"
#include "file_utils.h"

#define LINE 5
#define COLUMN 5


int main() {


    char buf[2*LINE];
    size_t len = 0;
    ssize_t read;
    char * line = NULL;
    FILE * fp = read_map("map.txt");

    node grid[LINE][COLUMN];
    for(int i = 0; i < LINE; i++){
        read = getline(&line, &len, fp);
        for(int j = 0; j < LINE*2; j+=2){

            printf("%c ", line[j]);
            grid[i][j/2]= init_node(i, j/2, line[j]-48);
        }
    }

    fclose(fp);
    if (line)
        free(line);

    printf("\n");

    grid[2][2].weight=255;
    grid[3][3].weight=255;
    //grid[2][3].weight=255;

    node start_node = grid[0][0];
    start_node.g = 0;
    start_node.h = 0;
    start_node.f = start_node.g + start_node.h;

    node end_node = grid[4][4];


    find_path(start_node, end_node, LINE, COLUMN, grid);


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

