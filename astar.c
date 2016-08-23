#include<stdio.h>
#include<stdlib.h>

struct node{
    struct node* parent;
    struct node* next;
    int g;
    int h;
    int f;
    int x, y;
    float weight;
};

struct node* head_open = NULL;
struct node* head_close = NULL;

void insert(struct node** head, struct node * node);
void removeNode(struct node** head, struct node * node);
int containsNode(struct node** head, struct node * node);

struct node init_node(int x, int y, float weight){
    struct node no;
    no.x = x;
    no.y = y;
    no.weight = weight;
}

struct node* lowest_f(){
   struct node* current = head_open;
   struct node* lowest_f = current;
   while(current != NULL){
       if(current->f < lowest_f->f){
           lowest_f = current;
       }
       current = current->next;
   }
   return lowest_f;
}

int is_finish(struct node node, int x, int y){
    if(node.x == x && node.y == y){
        return 1;
    }
    return 0;
}

int heuristic(struct node* node, struct node* finish){
    return abs(node->x - finish->x) + abs(node->y - finish->y);
}

void g(struct node current, struct node neighbor){

    int dist = 0;
    if(current.x == neighbor.x || current.y == neighbor.y ){
        dist=10;
    }else{
        dist=14;
    }
    neighbor.g = current.g + dist;
        
    
}


int main(){

    int x0=1, y0=1;//start 
    int xf=3, yf=3;//finish

    struct node grid[4][4];
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            grid[i][j] = init_node(i, j, 0);
        }
    }

    
    struct node start_node = grid[1][1];
    start_node.g=0;
    start_node.h=0;
    start_node.f = start_node.g + start_node.h;

    //insere o start point na lista de open
    insert(&head_open, &start_node);

    while(head_open != NULL){
        struct node* current = lowest_f();
        if(is_finish(*current, xf, yf)){
            //TODO rebuild the path
            printf("finish!");
            return 0;
        }

        removeNode(&head_open, current);
        insert(&head_close, current);

        //Checando a vizinhança
        //checar em caso de borda
        for(int x = current->x-1; x <= current->x+1; x++){
            for(int y = current->x-1; y <= current->x+1; y++){
                struct node neighbor = grid[x][y];
                //avoid reinsert the current node at open list
                if(x == current->x && y== current->y){
                    continue;
                }
                if(containsNode(&head_close, current)){
                    continue;
                }

                g(*current, neighbor);
                neighbor.h=heuristic(&neighbor, &grid[3][3]);
                printf("[%d][%d] - G=%d \n H=%d \n F=%d\n ", x,y,neighbor.g, neighbor.h, neighbor.f);


            }
        }
    }
}

void insert(struct node** head, struct node* inode){	
    if(*head == NULL){
        *head = inode;	
    }else{
        struct node* current = *head;
        while(current->next != NULL){
            current = current->next;
        }	
        current->next = inode;
    }

}

void removeNode(struct node** head, struct node* inode){	
    if(*head != NULL){
        //lista vazia		
        if((*head)->next == NULL){
            //lista 1 elemento
            *head = NULL;
        }else{
            struct node* current = *head;
            if(current == inode){ //remove a head
                *head = current->next;
            }else{
                while(inode != current->next){
                    current = current->next;
                }
                current->next=current->next->next;
            }


        }

    }
}

int containsNode(struct node** head, struct node* node){	
    if(*head == NULL){
        return 0; 
    }

    struct node* current = *head;
    do{
        if(current == node){
            return 1;
        }
        current = current->next;
    }
    while(current != NULL);
    

    return 0;

}

