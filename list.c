#include <stdio.h>
#include "list.h"

node init_node(int x, int y, float weight) {
    node n;
    n.next = NULL;
    n.parent = NULL;
    n.x = x;
    n.y = y;
    n.f=-1;
    n.g=-1;
    n.h=-1;
    n.weight = weight;
    return n;
}

void insert_node(node **list, node *n) {
    if (*list == NULL) {
        *list = n;
    } else {
        node *current = *list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = n;
    }

}

void remove_node(node **list, node *n) {
    if (*list != NULL) {
        //lista vazia
        if ((*list)->next == NULL) {
            //lista 1 elemento
            *list = NULL;
        } else {
            node *current = *list;
            if (current == n) { //remove a list
                node *aux = (*list)->next;
                (*list)->next = NULL;
                *list = aux;
            } else {
                while (n != current->next) {
                    current = current->next;
                }
                current->next = current->next->next;
                n->next=NULL;
            }


        }

    }
}


int contains_node(node **list, node *n) {
    if (*list == NULL) {
        return 0;
    }

    node *current = *list;
    do {
        if (current == n) {
            return 1;
        }
        current = current->next;
    } while (current != NULL);


    return 0;
}

void print_list(node *list) {
    if (list == NULL) {
        printf("Empty list\n");
        return;
    }

    node *current = list;
    do {
        printf("(%d, %d) - ", current->x, current->y);
        current = current->next;
    } while (current != NULL);

    printf("\n");


}