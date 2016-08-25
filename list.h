//
// Created by lds on 23/08/16.
//

#ifndef ASTAR_LIST_H
#define ASTAR_LIST_H

typedef struct node {
    struct node *parent;
    struct node *next;
    int x, y;
    int g;
    int h;
    int f;
    int weight;
} node;

node init_node(int x, int y, float weight);

void insert_node(node **list, node *n);

void remove_node(node **list, node *n);

int contains_node(node **list, node *n);

void print_list(node *list);


#endif //ASTAR_LIST_H
