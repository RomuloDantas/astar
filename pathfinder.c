#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "astar.h"
#include "file_utils.h"

#define LINE 5
#define COLUMN 5

#define LINE_TEST_1 5
#define COLUMN_TEST1 5

#define LINE_TEST_2 5
#define COLUMN_TEST_2 5

#define LINE_BREAK 10

#define SPACE 32

void map_pathfinder();

void test1_pathfinder();

void test2_pathfinder();

int main(int argc, char *argv[]) {

    int arg = 0;
    if (argc == 1) {
        printf("Deve-se entrar com um argumento");
    } else if (argc >= 2) {
        arg = atoi(argv[1]);
    }


    switch (arg) {
        case 1:
            map_pathfinder();
            break;
        case 2:
            test1_pathfinder();
            break;
        case 3:
            test2_pathfinder();
            break;
        default:
            //print_help();
            break;
    }

    exit(0);
}

void map_pathfinder() {
    FILE * f = read_map("/home/lds/semb/astar/map.txt");
    node grid[LINE][COLUMN];

    int c, line=0, column=0;
    do
    {
        c = fgetc(f);
        if( feof(f) )
        {
            break ;
        }

        if(c != LINE_BREAK){
            if(c != SPACE){
                grid[line][column] = init_node(line, column, (c - 48));
                column++;
            }
        }else{
            column=0;
            line++;
        }

    }while(1);


    node *start_node = &(grid[0][0]);
    start_node->g = 0;
    start_node->h = 0;
    start_node->f = start_node->g + start_node->h;

    node end_node = grid[3][3];

    find_path(start_node, end_node, LINE, COLUMN, grid);


    // test();

}


void test1_pathfinder() {

}

void test2_pathfinder() {

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

