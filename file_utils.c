//
// Created by lds on 24/08/16.
//


#include <stdio.h>

FILE *read_map(char * filename){
    return fopen(filename, "r");
}


void file_generator(){
    FILE *fr = fopen("/home/lds/semb/astar/t", "w");

    for(int i= 0 ; i < 3000; i ++){
        for(int j = 0; j < 1000; j ++){
            fwrite("1", 1, 1, fr);
            if(j != 999) {
                fwrite(" ", 1, 1, fr);
            }

        }
        fwrite("\n",1,1,fr);
    }
}