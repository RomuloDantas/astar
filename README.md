#  PIC A-Star  #

Implementação do algoritmo para busca de caminhos, A*(A-estrela), para a plataforma PIC.

## Descrição ## 

Implementação do algoritmo A* para o PIC18F4550.
Esta implementação utiliza a heurística de Manhattan para buscar um caminho em mapas de tamanho 13X12.

##  Licença  ##

 Copyright (c) 2016 Romulo Dantas, All Rights Reserved.

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License as
 published by the Free Software Foundation; either version 2 of
 the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, see <http://www.gnu.org/licenses/>.

## Repositorio ##

https://github.com/RomuloDantas/astar.git

#### Dados de entrada ####

Os dados de entrada serão alocados na ROM do PIC.
Para realizar qualquer modificação nos valores do mapa o vetor positions, localizado no arquivo path_finder.c, deverar ser alterado e o projeto recompilado e gravado
no PIC.

#### Saída do resultado ####
Os resultado da computação do algoritmo é colocado na serial (RX) do PIC com o baudrate de 9600

#### Modo de uso  ####

1 - Compilar o projeto usando MPLAB X + XC8.
2 - Gravar no PIC18F4550.
3 - Conectar o RX da serial (Baudrate 9600) do PIC a um terminal serial para que a saída seja visualizada.

### Arquivos ###
path_finder.c 
   Arquivo que contém a função main e que inicializa as  estruturas utilizadas pelo A*.
astar.c
   Arquivo que contém as funções que realizam as ações utilizadas pelo algoritmo A*, assim como a própria implementação da função principal do algoritmo.
astar.h
   Arquivo de cabeçalho para as funções que realizam as ações utilizadas pelo algoritmo A*, assim como a própria implementação da função principal do algoritmo.
list.c
   Arquivo que contém as funções que realizam as ações nas listas (open_list e close_list) utlizadas pelo algoritmo A*.
list.h
   Arquivo de cabeçalho das funções que realizam as ações nas listas (open_list e close_list) utlizadas pelo algoritmo A*.
