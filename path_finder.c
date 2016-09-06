#include <xc.h>

#include <math.h>
#include <plib/usart.h>

#include "list.h"
#include "astar.h"

#pragma config FOSC     = HS     // (8 MHz)
#pragma config IESO     = OFF
#pragma config PWRT     = OFF
#pragma config BORV     = 3
#pragma config WDT      = OFF
#pragma config WDTPS    = 32768
#pragma config MCLRE    = OFF
#pragma config LPT1OSC  = OFF
#pragma config PBADEN   = OFF
#pragma config STVREN   = ON
#pragma config LVP      = OFF

void map_pathfinder();

void test_com_barreira();

 main() {
    
     OpenUSART(USART_TX_INT_OFF &
            USART_RX_INT_ON &
            USART_ASYNCH_MODE &
            USART_EIGHT_BIT &
            USART_CONT_RX &
            USART_BRGH_HIGH, 50);

   
    

   //test_com_barreira();
   map_pathfinder();
    
    putsUSART("indo dormir\r");
    SLEEP();
}

//
///**
// * Realiza o teste com um mapa com 3025 elementos.
// */
void map_pathfinder() {
    putsUSART("Teste do Mapa\r");
    static node grid[LINHAS][COLUNAS];
    static const position positions[LINHAS*COLUNAS] = {
  {0,0,2}, {0,1,255}, {0,2,2},{0,3,2}, {0,4,2}, {0,5,2}, {0,6,2}, {0,7,2}, {0,8,2}, {0,9,2}, {0,10,2}
 ,{1,0,2}, {1,1,255}, {1,2,2},{1,3,2}, {1,4,2}, {1,5,2}, {1,6,2}, {1,7,2}, {1,8,2}, {1,9,2}, {0,10,2}
 ,{2,0,2}, {2,1,255}, {2,2,2},{2,3,2}, {2,4,2}, {2,5,2}, {2,6,2}, {2,7,2}, {2,8,2}, {2,9,2}, {0,10,2}
 ,{3,0,2}, {3,1,255}, {3,2,2},{3,3,2}, {3,4,2}, {3,5,2}, {3,6,2}, {3,7,2}, {3,8,2}, {3,9,2}, {0,10,2}
 ,{4,0,2}, {4,1,255}, {4,2,2},{4,3,2}, {4,4,2}, {4,5,2}, {4,6,2}, {4,7,2}, {4,8,2}, {4,9,2}, {0,10,2}
 ,{5,0,2}, {5,1,255}, {5,2,2},{5,3,2}, {5,4,2}, {5,5,80}, {5,6,80}, {5,7,2}, {5,8,2}, {5,9,2}, {0,10,2}
 ,{6,0,2}, {6,1,255}, {6,2,255},{6,3,2}, {6,4,255}, {6,5,80}, {6,6,80}, {6,7,2}, {6,8,2}, {6,9,2}, {0,10,2}
 ,{7,0,2}, {7,1,2}, {7,2,255},{7,3,2}, {7,4,255}, {7,5,2}, {7,6,2}, {7,7,2}, {7,8,2}, {7,9,2}, {0,10,2}
 ,{8,0,255}, {8,1,2}, {8,2,2},{8,3,2}, {8,4,255}, {8,5,2}, {8,6,2}, {8,7,2}, {8,8,2}, {8,9,2}, {0,10,2}
 ,{9,0,2}, {9,1,2}, {9,2,2},{9,3,2}, {9,4,255}, {9,5,2}, {9,6,2}, {9,7,2}, {9,8,2}, {9,9,2}, {0,10,2}
 ,{10,0,2}, {10,1,2}, {10,2,2},{10,3,2}, {10,4,255}, {10,5,2}, {10,6,2}, {10,7,2}, {10,8,2}, {10,9,2}, {10, 10, 2}};
    
   
   
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            init_node(&grid[i][j]);
            grid[i][j].pos = &(positions[(i*LINHAS)+j]);
        }
    }
    node *start_node = &(grid[0][0]);
    start_node->g = 0;
    start_node->h = 0;
    start_node->f = start_node->g + start_node->h;

    node end_node = grid[LINHAS - 1][COLUNAS - 1];

    find_path(start_node, end_node, grid);
}

/**
 * Realiza o teste que mostra o algoritmo andando
 * com barreira.
 */
void test_com_barreira() {
//    putsUSART("Teste com barreira\r");
//    static node grid[L][C];
//    for (int i = 0; i < L; i++) {
//        for (int j = 0; j < C; j++) {
//            if (i < L - 1 && j == 5) {
//                init_node(&grid[i][j], i, j, 2);
//            } else {
//                init_node(&grid[i][j], i, j, 0);
//            }
//        }
//    }
//
//    node *start_node = &(grid[0][0]);
//    start_node->g = 0;
//    start_node->h = 0;
//    start_node->f = start_node->g + start_node->h;
//
//    node end_node = grid[0][C - 1];
//
//    find_path(start_node, end_node, grid);
}
