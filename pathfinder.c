#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "astar.h"
#include "file_utils.h"

#define LINE 55
#define COLUMN  55

#define LINE_TEST_1 10
#define COLUMN_TEST1 10

#define LINE_TEST_2 5
#define COLUMN_TEST_2 5

#define LINE_BREAK 10

#define SPACE 32

void map_pathfinder();

void test_vertical();

void test_horizontal();

void test_diagonal();

void test_com_barreira();

void print_help();

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
            test_vertical();
            break;
        case 3:
            test_horizontal();
            break;
        case 4:
            test_diagonal();
            break;
        case 5:
            test_com_barreira();
            break;
        default:
            print_help();
            break;
    }

    exit(0);
}

void print_help() {

    printf("Para usar o programa você precisa passar um dos argumentos: \n");
    printf("1 - Map \n2 - Teste vertical \n3 - Teste horizontal \n4 - Teste diagonal \n5 - Teste com barreira");
}

void map_pathfinder() {

    node grid[LINE][COLUMN];
    int w = 0;
    for (int i = 0; i < 55; i++) {
        for (int j = 0; j < 55; j++) {

            /*
            if (j <= 11) {
                w = 50;
            } else if (j > 11 && j <= 22) {
                w = 30;
            } else if (j > 22 && j <= 33) {
                w = 70;
            } else if (j > 33 && j <= 44) {
                w = 20;
            } else if (j > 33 && j <= 44) {
                w = 80;
            }
             */

            grid[i][j] = init_node(i, j, w);

        }
        node *start_node = &(grid[1][1]);
        start_node->g = 0;
        start_node->h = 0;
        start_node->f = start_node->g + start_node->h;

        node end_node = grid[54][54];

        find_path(start_node, end_node, LINE, COLUMN, grid);

    }
}

    void test(int lines, int columns, int xi, int yi, int xf, int yf) {
        node grid[lines][columns];
        for (int i = 0; i < lines; i++) {
            for (int j = 0; j < columns; j++) {

                grid[i][j] = init_node(i, j, 0);

            }
        }

        node *start_node = &(grid[1][1]);
        start_node->g = 0;
        start_node->h = 0;
        start_node->f = start_node->g + start_node->h;

        node end_node = grid[lines - 1][1];

        find_path(start_node, end_node, lines, columns, grid);
    }


    void test_vertical() {
        test(LINE_TEST_1, COLUMN_TEST1, 1, 1, LINE_TEST_1 - 1, 1);
/*node grid[LINE_TEST_1][COLUMN_TEST1];
    for(int i= 0 ; i < LINE_TEST_1; i ++){
        for(int j = 0; j < COLUMN_TEST1; j ++){

            grid[i][j] = init_node(i, j, 0);

        }
    }

    node *start_node = &(grid[1][1]);
    start_node->g = 0;
    start_node->h = 0;
    start_node->f = start_node->g + start_node->h;

    node end_node = grid[LINE_TEST_1-1][1];

    find_path(start_node, end_node, LINE_TEST_1, COLUMN_TEST1, grid);
    */
    }

    void test_horizontal() {
        node grid[LINE_TEST_1][COLUMN_TEST1];
        for (int i = 0; i < LINE_TEST_1; i++) {
            for (int j = 0; j < COLUMN_TEST1; j++) {

                grid[i][j] = init_node(i, j, 0);

            }
        }

        node *start_node = &(grid[1][1]);
        start_node->g = 0;
        start_node->h = 0;
        start_node->f = start_node->g + start_node->h;

        node end_node = grid[1][COLUMN_TEST1 - 1];

        find_path(start_node, end_node, LINE_TEST_1, COLUMN_TEST1, grid);
    }

    void test_diagonal() {
        node grid[LINE_TEST_1][COLUMN_TEST1];
        for (int i = 0; i < LINE_TEST_1; i++) {
            for (int j = 0; j < COLUMN_TEST1; j++) {

                grid[i][j] = init_node(i, j, 0);

            }
        }

        node *start_node = &(grid[1][1]);
        start_node->g = 0;
        start_node->h = 0;
        start_node->f = start_node->g + start_node->h;

        node end_node = grid[LINE_TEST_1 - 1][COLUMN_TEST1 - 1];

        find_path(start_node, end_node, LINE_TEST_1, COLUMN_TEST1, grid);
    }

    void test_com_barreira() {
        node grid[LINE_TEST_1][COLUMN_TEST1];
        for (int i = 0; i < LINE_TEST_1; i++) {
            for (int j = 0; j < COLUMN_TEST1; j++) {

                if (i < LINE_TEST_1 - 1 && j == 5) {
                    grid[i][j] = init_node(i, j, 255);
                    printf("%d ", 255);
                } else {
                    grid[i][j] = init_node(i, j, 0);
                    printf("%d ", 0);
                }

            }
            printf("\n");
        }

        node *start_node = &(grid[1][1]);
        start_node->g = 0;
        start_node->h = 0;
        start_node->f = start_node->g + start_node->h;

        node end_node = grid[1][COLUMN_TEST1 - 1];

        find_path(start_node, end_node, LINE_TEST_1, COLUMN_TEST1, grid);
    }


