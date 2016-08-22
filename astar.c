#include<stdio.h>
#include<stdlib.h>

struct node{
    struct node* parent;
    struct node* next;
    int g;
    int h;
    float weight;
};

struct node* head_open = NULL;

void insert(struct node** head, struct node * node);
void removeNode(struct node** head, struct node * node);


int main(){


    struct node* n = (struct node*)malloc(sizeof(struct node));
    n->g=10;
    struct node* n2= (struct node*)malloc(sizeof(struct node));
    n2->g=20;
    struct node* n3= (struct node*)malloc(sizeof(struct node));
    n3->g=30;
    insert(&head_open, n);
    insert(&head_open, n2);
    insert(&head_open, n3);

    struct node* aux = head_open;
    while(aux->next != NULL){
        printf("%d\n", aux->g);
        aux = aux->next;
    }	
    printf("%d\n", aux->g);
    removeNode(&head_open, n3);
    removeNode(&head_open, n);

    struct node* auxr= head_open;
    while(auxr->next != NULL){
        printf("%d\n", auxr->g);
        auxr = auxr->next;
    }	
    printf("%d\n", auxr->g);


}

void insert(struct node** head, struct node* inode){	
    if(*head == NULL){
        *head = inode;	
    }else{
        struct node* aux = *head;
        while(aux->next != NULL){
            aux = aux->next;
        }	
        aux->next = inode;
    }

}

void removeNode(struct node** head, struct node* inode){	
    if(*head != NULL){
        //lista vazia		
        if((*head)->next == NULL){
            //lista 1 elemento
            *head = NULL;
        }else{
            struct node* aux = *head;
            if(aux == inode){ //remove a head
                *head = aux->next;
            }else{
                while(inode != aux->next){
                    aux = aux->next;
                }
                aux->next=aux->next->next;
            }


        }

    }
}
