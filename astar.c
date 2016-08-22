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
void remove(struct node** head, struct node * node);


int main(){

  
struct node* n = (struct node*)malloc(sizeof(struct node));
n->g=10;
struct node* n2= (struct node*)malloc(sizeof(struct node));
n2->g=20;
insert(&head_open, n);
insert(&head_open, n2);

struct node* aux = head_open;
while(aux->next != NULL){
	printf("%d\n", aux->g);
	aux = aux->next;
}	
	printf("%d\n", aux->g);


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

//TODO nao funcionando
void remove(struct node** head, struct node* inode){	
	if(*head != NULL){
	//lista vazia		
	}else if(*head->next == NULL){
		//lista 1 elemento
		*head = NULL;
	}else{
		struct node* aux = *head;
		while(aux->next != NULL){
			aux = aux->next;
		}	
		aux->next = inode;

		
	}

}
