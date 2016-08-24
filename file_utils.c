//
// Created by lds on 24/08/16.
//


#include <stdio.h>

FILE *read_map(char * filename){
    return fopen(filename, "r");
}