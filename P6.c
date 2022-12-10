#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *node_pointer;
typedef struct node{
    char data[50];
    int pri;
}node;
node max_heap[1000000];


void insert(node item, int rear){
    int i = rear;
    i++;
    while((i > 1)){
        if((item.pri) > max_heap[i/2].pri){
            max_heap[i] = max_heap[i/2];
            i = i/2;
        }
        else{
            break;
        }
    }
    strcpy(max_heap[i].data, item.data);
    max_heap[i].pri = item.pri;
}


node delete(int rear){
    int parent, child;
    node item, temp;
    item = max_heap[1];
    temp = max_heap[rear];
    parent = 1;
    child = 2;
    
    while(child < rear){
        if((child+1 < rear)&&(max_heap[child].pri < max_heap[child+1].pri)){
            child++;
        }
        if(temp.pri < max_heap[child].pri){ 
            max_heap[parent] = max_heap[child];
            parent = child;
            child = child * 2;
        }
        else{
            break;
        }
    }
    max_heap[parent] = temp;
    return item;
}

void main(){
    int n;
    int heap_num = 0;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        char title[50];
        int priority;
        scanf("%s %d", title, &priority);
        node item;
        strcpy(item.data, title);
        item.pri = priority;
        insert(item, heap_num);
        heap_num++;
    }
    printf("First three things to do:\n");
    for(int i=0; i<3; i++){
        if(heap_num > 0){
            node item = delete(heap_num);
            printf("%s\n", item.data);
            heap_num--;
        }
        else break;
    }
}

