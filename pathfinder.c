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
        printf("Deve-se entrar com um argumento\n ");
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
        case 6:
            test_sem_caminho();
            break;
        default:
            print_help();
            break;
    }

    exit(0);
}

/**
 * Mostra as informações de help no terminal.
 */
void print_help() {

    printf("Para usar o programa você precisa passar um dos argumentos: \n");
    printf("1 - Map \n2 - Teste vertical \n3 - Teste horizontal \n4 - Teste diagonal \n5 - Teste com barreira\n ");
}


/**
 * Realiza o teste com um mapa com 3025 elementos.
 */
void map_pathfinder() {
    printf("Teste do mapa \n");

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

/**
 * Realiza os testes do algoritimo de acordo com
 * os parâmetros.
 * @param lines - o número de linhas da matriz.
 * @param columns - o número de colunas da matriz.
 * @param xi - o x da posição inicial.
 * @param yi - o y da posição inicial.
 * @param xf - o x da posição final.
 * @param yf - o y da posição final.
 */
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

/**
 * Realiza o teste que mostra o algoritmo andando
 * na vertical.
 */
void test_vertical() {
    printf("Teste verical \n");
    test(LINE_TEST, COLUMN_TEST, 0, 0, LINE_TEST - 1, 1);
}

/**
 * Realiza o teste que mostra o algoritmo andando
 * na horizontal.
 */
void test_horizontal() {
    printf("Teste horizontal\n ");
    test(LINE_TEST, COLUMN_TEST, 0, 0, 1, COLUMN_TEST - 1);
}

/**
 * Realiza o teste que mostra o algoritmo andando
 * na diagonal.
 */
void test_diagonal() {
    printf("Teste diagonal\n");
    test(LINE_TEST, COLUMN_TEST, 0, 0, LINE_TEST - 1, COLUMN_TEST - 1);
}

/**
 * Realiza o teste que mostra o algoritmo andando
 * com barreira.
 */
void test_com_barreira() {
    printf("Teste com barreira\n");
    test(LINE_TEST, COLUMN_TEST, 1, 1, 1, COLUMN_TEST - 1);
}

/**
 * Realiza o teste onde não existe caminho.
 */
void test_sem_caminho() {
    printf("Teste sem caminho\n");
    test(LINE_TEST, COLUMN_TEST, 1, 1, 1, COLUMN_TEST - 1);
}


