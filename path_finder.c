 /**********************************************************************
 *     Copyright (c) 2016 Romulo Dantas, All Rights Reserved.
 *
 *     This program is free software; you can redistribute it and/or
 *     modify it under the terms of the GNU General Public License as
 *     published by the Free Software Foundation; either version 2 of
 *     the License, or (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 ********************************************************************/

/*********************************************************************
 *                      Visão Geral
 * 
 * Implementação do algoritmo A* (A-estrela) para a plataforma PIC, 
 * especificamente para o PIC18F4550.
 * Esta implementação do algoritmo A* utiliza a heurística de Manhattan para 
 * buscar o caminho em um mapa alocado na memória ROM do PIC. 
 * 
 * A documentação deste projeto basea-se na documentação feita nos drivers do 
 * kernel Linux.
 * 
 * Version:       1.0 - Mapa alocado na ROM. 
 * Author(s):     Romulo Dantas <romulocicero@gmail.com>
 *                David Sanford <dsanfordseu@gmail.com>
 * Created at:    Fri Aug 26 13:38:52 2016 -0300
 * Repository:    https://github.com/RomuloDantas/astar.git
 * 
 **********************************************************************/ 

/*********************************************************************
 *
 * Filename:      path_finder.c
 * Version:       1.0
 * Description:   Arquivo que contém a função main e que inicializa as 
 *                estruturas utilizadas pelo A*.
 * Author:        Romulo Dantas <romulocicero@gmail.com>
 *                David Sanford <dsanfordseu@gmail.com>
 *
 *  ********************************************************************/

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

static node grid[LINHAS][COLUNAS];
static const point positions[LINHAS*COLUNAS] = {
    {0,0,2}, {0,1,255}, {0,2,2},{0,3,2}, {0,4,2}, {0,5,2}, {0,6,2}, {0,7,2}, {0,8,2}, {0,9,2}, {0,10,2}, {0, 11,40}
,{1,0,2}, {1,1,255}, {1,2,2},{1,3,2}, {1,4,2}, {1,5,2}, {1,6,2}, {1,7,2}, {1,8,2}, {1,9,2}, {1,10,2}, {1, 11,40}
,{2,0,2}, {2,1,255}, {2,2,2},{2,3,2}, {2,4,2}, {2,5,2}, {2,6,2}, {2,7,2}, {2,8,2}, {2,9,2}, {2,10,2}, {2, 11,40}
,{3,0,2}, {3,1,255}, {3,2,2},{3,3,2}, {3,4,2}, {3,5,2}, {3,6,2}, {3,7,2}, {3,8,2}, {3,9,2}, {3,10,2}, {3, 11,40}
,{4,0,2}, {4,1,255}, {4,2,2},{4,3,2}, {4,4,2}, {4,5,2}, {4,6,2}, {4,7,2}, {4,8,2}, {4,9,2}, {4,10,2}, {4, 11,40}
,{5,0,2}, {5,1,255}, {5,2,2},{5,3,2}, {5,4,2}, {5,5,80}, {5,6,80}, {5,7,2}, {5,8,2}, {5,9,2}, {5,10,2}, {5, 11,40}
,{6,0,2}, {6,1,255}, {6,2,255},{6,3,2}, {6,4,255}, {6,5,80}, {6,6,80}, {6,7,2}, {6,8,2}, {6,9,2}, {6,10,2}, {6, 11,40}
,{7,0,2}, {7,1,2}, {7,2,255},{7,3,2}, {7,4,255}, {7,5,2}, {7,6,2}, {7,7,2}, {7,8,2}, {7,9,2}, {7,10,2}, {7, 11,40}
,{8,0,255}, {8,1,2}, {8,2,2},{8,3,2}, {8,4,255}, {8,5,2}, {8,6,2}, {8,7,2}, {8,8,2}, {8,9,2}, {8,10,2}, {8, 11,40}
,{9,0,2}, {9,1,2}, {9,2,2},{9,3,2}, {9,4,255}, {9,5,2}, {9,6,2}, {9,7,2}, {9,8,2}, {9,9,2}, {9,10,2}, {9, 11,40}
,{10,0,2}, {10,1,2}, {10,2,2},{10,3,2}, {10,4,255}, {10,5,2}, {10,6,2}, {10,7,2}, {10,8,2}, {10,9,2}, {10, 10, 2}, {10, 11,40}
,{11,0,2}, {11,1,2}, {11,2,2},{11,3,2}, {11,4,255}, {11,5,2}, {11,6,2}, {11,7,2}, {11,8,2}, {11,9,2}, {11, 10, 2}, {11, 11,40}
,{12,0,2}, {12,1,2}, {12,2,2},{12,3,2}, {12,4,255}, {12,5,2}, {12,6,2}, {12,7,2}, {12,8,2}, {12,9,2}, {12, 10, 2}, {12, 11,40}
};

void map_pathfinder();

main() {
    
     OpenUSART(USART_TX_INT_OFF &
            USART_RX_INT_ON &
            USART_ASYNCH_MODE &
            USART_EIGHT_BIT &
            USART_CONT_RX &
            USART_BRGH_HIGH, 50);
     
    map_pathfinder();
        
    putsUSART("Fim\n\r");
    SLEEP();
}

/**
 * Realiza a busca do caminho no mapa contido na ROM.
 */
void map_pathfinder() {
    putsUSART("Teste do Mapa\n\r");
       
    //Inicializa os ponteiros 'point' de cada node pertecente à matriz grid
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            init_node(&grid[i][j]);
            grid[i][j].point = &(positions[(i*COLUNAS)+j]);
        }
    }
    
    //Seta o ponto de partida
    node *start_node = &(grid[0][0]);
    start_node->g = 0;
    start_node->h = 0; 

    //Seta o ponto de chegada
    node end_node = grid[LINHAS - 1][COLUNAS - 1];

    find_path(start_node, end_node, grid);
}
