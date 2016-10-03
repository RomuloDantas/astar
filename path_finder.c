#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "list.h"
#include "astar.h"

#define LINE 55
#define COLUMN  55

#define LINE_TEST 10
#define COLUMN_TEST 10

#define LINE_BREAK 10
#define SPACE 32

void map_pathfinder();

void test_vertical();

void test_horizontal();

void test_diagonal();

void test_com_barreira();

void test_sem_caminho();

void print_help();

void all_tests();

void map_pathfinder_file();

int main(int argc, char *argv[]) {

    int arg = -1;
    if (argc == 1) {
        printf("Faltando argumento!\n");
    } else if (argc >= 2) {
        arg = atoi(argv[1]);
    }


    switch (arg) {
        case 0:
            all_tests();
            break;
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
        case 7:
            map_pathfinder_file();
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
    printf("0 - Realiza todos os testes \n1 - Map \n2 - Teste vertical \n3 - Teste horizontal \n4 - Teste diagonal \n5 - Teste com barreira\n6 - Teste sem caminho \n7 - Map from file \n");
}

int inline pow10(int a){

    return  a*a*a*a*a*a*a*a*a*a;
}
/**
 * Lê um grid de uma arquivo.
 * @param f - o arquivo para ler o grid.
 * @param grid - o grid onde as informações
 *        serão colocadas.
 */
void read_grid(FILE *f, node grid[LINE][COLUMN]) {
    int c, line = 0, column = 0;
    unsigned char currentWeight = 0;
    int currWeightAux[3] = {0, 0, 0};
    int countWeightAux = 0;
    int i = 0;
    int j = 0;

    do {
        c = fgetc(f);
        if (feof(f)) {
            break;

        }

        if (c != LINE_BREAK) {
            if (c != SPACE) {
                currWeightAux[countWeightAux] = c - 48;
                column++;
                countWeightAux++;
            } else {
                currentWeight = 100 * currWeightAux[0] + 10 * currWeightAux[1] + currWeightAux[2];
                if (countWeightAux < 3 && countWeightAux > 0) {
                    currentWeight = currentWeight / pow10(3 - countWeightAux);
                }
                if (countWeightAux != 0) {
                    grid[i][j] = init_node(i, j, currentWeight);
                    j++;
                    countWeightAux = 0;
                    currWeightAux[0] = 0;
                    currWeightAux[1] = 0;
                    currWeightAux[2] = 0;
                }
            }
        } else {
            column = 0;
            line++;
            currentWeight = 100 * currWeightAux[0] + 10 * currWeightAux[1] + currWeightAux[2];
            if (countWeightAux < 3 && countWeightAux > 0) {
                currentWeight = currentWeight / pow10(3 - countWeightAux);
            }
            if (countWeightAux != 0) {
                grid[i][j] = init_node(i, j, currentWeight);
                i++;
                j = 0;
                countWeightAux = 0;
                currWeightAux[0] = 0;
                currWeightAux[1] = 0;
                currWeightAux[2] = 0;
            }
        }

    } while (1);

}


/**
 * Realiza o teste com um mapa com 3025 elementos e com
 * pesos inicializados a partir de um arquivo.
 */
void map_pathfinder_file() {
    FILE *f = fopen("map.txt", "r");
    node grid[LINE][COLUMN];
    read_grid(f, grid);

    node *start_node = &(grid[0][0]);
    start_node->g = 0;
    start_node->h = 0;
    start_node->f = start_node->g + start_node->h;

    node end_node = grid[LINE - 1][COLUMN - 1];

    find_path(start_node, end_node, LINE, COLUMN, grid);
}


/**
 * Realiza o teste com um mapa com 3025 elementos.
 */
void map_pathfinder() {
    printf("Teste do Mapa");
    node grid[LINE][COLUMN];
    int w = 0;
    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j < COLUMN; j++) {
            if (j <= 5) {
                w = 5;
            } else if (j > 5 && j <= 11) {
                if (i < 11) {
                    w = 80;
                } else {
                    w = 10;
                }
            } else if (j > 11 && j <= 22) {
                if (i > 25 && i < 30) {
                    w = 50;
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
                if (i < 10) {
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

    clock_t start = clock();
    find_path(start_node, end_node, LINE, COLUMN, grid);
    clock_t end = clock();

    float seconds = (float) (end - start) / CLOCKS_PER_SEC;
    printf("\n\n%.16f", seconds);

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
    printf("Teste Vertical\n");
    test(LINE_TEST, COLUMN_TEST, 0, 0, LINE_TEST - 1, 0);

}

/**
 * Realiza o teste que mostra o algoritmo andando
 * na horizontal.
 */
void test_horizontal() {
    printf("Teste Horizontal\n");
    test(LINE_TEST, COLUMN_TEST, 0, 0, 0, COLUMN_TEST - 1);
}

/**
 * Realiza o teste que mostra o algoritmo andando
 * na diagonal.
 */
void test_diagonal() {
    printf("Teste Diagonal\n");
    test(LINE_TEST, COLUMN_TEST, 0, 0, LINE_TEST - 1, COLUMN_TEST - 1);
}

/**
 * Realiza o teste que mostra o algoritmo andando
 * com barreira.
 */
void test_com_barreira() {
    printf("Teste com barreira");
    node grid[LINE_TEST][COLUMN_TEST];
    for (int i = 0; i < LINE_TEST; i++) {
        for (int j = 0; j < COLUMN_TEST; j++) {
            if (i < LINE_TEST - 1 && j == 5) {
                grid[i][j] = init_node(i, j, 255);
            } else {
                grid[i][j] = init_node(i, j, 0);
            }
        }
    }

    node *start_node = &(grid[0][0]);
    start_node->g = 0;
    start_node->h = 0;
    start_node->f = start_node->g + start_node->h;

    node end_node = grid[0][COLUMN_TEST - 1];

    find_path(start_node, end_node, LINE_TEST, COLUMN_TEST, grid);
}

/**
 * Realiza o teste onde não existe caminho.
 */
void test_sem_caminho() {
    printf("Teste sem caminho\n");
    node grid[LINE_TEST][COLUMN_TEST];
    for (int i = 0; i < LINE_TEST; i++) {
        for (int j = 0; j < COLUMN_TEST; j++) {

            if (i < LINE_TEST && j == 5) {
                grid[i][j] = init_node(i, j, 255);
            } else {
                grid[i][j] = init_node(i, j, 0);
            }
        }
    }

    node *start_node = &(grid[0][0]);
    start_node->g = 0;
    start_node->h = 0;
    start_node->f = start_node->g + start_node->h;

    node end_node = grid[0][COLUMN_TEST - 1];

    find_path(start_node, end_node, LINE_TEST, COLUMN_TEST, grid);
}

/**
 * Realiza todos os testes.
 */
void all_tests() {
    printf("\n##########################################\n");
    test_vertical();
    clean_up();
    printf("\n##########################################\n");
    test_horizontal();
    clean_up();
    printf("\n##########################################\n");
    test_diagonal();
    clean_up();
    printf("\n##########################################\n");
    test_com_barreira();
    clean_up();
    printf("\n##########################################\n");
    test_sem_caminho();
}


