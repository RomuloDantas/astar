#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "astar.h"

#define LINE 55
#define COLUMN  55

#define LINE_TEST 10
#define COLUMN_TEST 10

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
    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j < COLUMN; j++) {
            if (j <= 11) {
                if (i < 11) {
                    w = 80;
                } else {
                    w = 10;
                }
            } else if (j > 11 && j <= 22) {
                if (i > 25 && i < 30) {
                    w = 70;
                } else {
                    w = 255;
                }
            } else if (j > 22 && j <= 33) {
                if (i < 40) {
                    w = 40;
                } else {
                    w = 255;
                }
            } else if (j > 33 && j <= 44) {
                if (i < 33) {
                    w = 90;
                } else {
                    w = 255;
                }
            } else if (j > 44 && j <= 54) {
                if (i < 22) {
                    w = 50;
                } else {
                    w = 10;
                }
            }


            grid[i][j] = init_node(i, j, w);


        }
    }
    node *start_node = &(grid[1][1]);
    start_node->g = 0;
    start_node->h = 0;
    start_node->f = start_node->g + start_node->h;

    node end_node = grid[LINE - 1][COLUMN - 1];

    find_path(start_node, end_node, LINE, COLUMN, grid);


}

void test(int lines, int columns, int xi, int yi, int xf, int yf) {
    node grid[lines][columns];
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {

            grid[i][j] = init_node(i, j, 0);

        }
    }

    node *start_node = &(grid[xi][yi]);
    start_node->g = 0;
    start_node->h = 0;
    start_node->f = start_node->g + start_node->h;

    node end_node = grid[xf][yf];

    find_path(start_node, end_node, lines, columns, grid);
}


void test_vertical() {
    test(LINE_TEST, COLUMN_TEST, 1, 1, LINE_TEST - 1, 1);
}

void test_horizontal() {
    test(LINE_TEST, COLUMN_TEST, 1, 1, 1, COLUMN_TEST - 1);
}

void test_diagonal() {
    test(LINE_TEST, COLUMN_TEST, 1, 1, LINE_TEST - 1, COLUMN_TEST - 1);
}

void test_com_barreira() {
    test(LINE_TEST, COLUMN_TEST, 1, 1, 1, COLUMN_TEST - 1);
}


