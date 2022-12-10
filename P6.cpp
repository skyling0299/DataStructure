#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
using namespace std;

typedef struct node *node_pointer;
typedef struct node{
    char data[100000];
    int pri;
}node;
vector<node> max_heap;


void heap_insert(node item){
    int i = max_heap.size();
    max_heap.push_back(item); //put item in last node
    while((i > 1)){
        if((item.pri) > max_heap.at(i/2).pri){
            node temp = max_heap.at(i);
            //max_heap.push_back(max_heap.at(i/2));
            max_heap.at(i) = max_heap.at(i/2);
            i = i/2;
        }
        else{
            break;
        }
    }
    max_heap.at(i) = item;
}


node heap_delete(){
    int size = max_heap.size();
    int parent, child;
    node item, temp;
    item = max_heap.at(1);
    temp = max_heap.back();
    parent = 1;
    child = 2;
    
    while(child < size){
        if((child+1 < size)&&(max_heap.at(child).pri < max_heap.at(child+1).pri)){
            child++;
        }
        if(temp.pri < max_heap.at(child).pri){ 
            max_heap.at(parent) = max_heap.at(child);
            parent = child;
            child = child * 2;
        }
        else{
            break;
        }
    }
    max_heap.at(parent) = temp;
    return item;
}

int main(){
    int n;
    scanf("%d", &n);

    node item;
    strcpy(item.data, "n");
    item.pri = -1;
    max_heap.push_back(item);

    for(int i=0; i<n; i++){
        char title[100000];
        int priority;
        scanf("%s %d", title, &priority);
        node item;
        strcpy(item.data, title);
        item.pri = priority;
        heap_insert(item);

    }
    printf("First three things to do:\n");
    for(int i=0; i<3; i++){
        if(max_heap.size() > 0){
            node item = heap_delete();
            printf("%s\n", item.data);
        }
        else break;
    }
    return 0;
}

