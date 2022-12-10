#include <stdio.h>
#include <stdlib.h>
typedef struct node *node_pointer;
typedef struct node{
    int connected_point;
    int weight;
    node_pointer next;
}node;
node_pointer all_vertex[2000];
void insert_to_head(int end_vertex, int weight, int vertex_index){
    // n means the node to insert, vertex means the address of the link list head to insert the node
    node_pointer new_ptr = (node_pointer)malloc(sizeof(node));
    new_ptr ->connected_point = end_vertex;
    new_ptr ->weight = weight;
    new_ptr ->next = NULL;

    node_pointer tmp = all_vertex[vertex_index];
    if(tmp == NULL){
        all_vertex[vertex_index] = new_ptr;
    }
    else{
        new_ptr->next = tmp;
        all_vertex[vertex_index] = new_ptr;
    }
    
}

void main(){
    int n, m, u, v, w;
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++){
        all_vertex[i] = NULL;
    } //all used vertex points will be NULL in the beggining
    for(int i=0; i<m; i++){
        scanf("%d %d %d", &u, &v, &w);
        insert_to_head(u, w, v);
        insert_to_head(v, w, u);
    }
    long long int total_weight = 0;
    int visited[n];
    int min_path[n];
    for(int i = 0; i < n; i++){
        min_path[i] = 100000;
        visited[i] = 0;
    }
    min_path[0] = 0;
    visited[0] = 1;
    int num = 0;
    for(int i=0; i<n; i++){
        node_pointer tmp = all_vertex[num];
        int min_weight = 100000;
        int min_index = 0;
        while(tmp!=NULL){
            if((tmp->weight < min_path[tmp->connected_point])){
                min_path[tmp->connected_point] = tmp->weight;
            }
            tmp = tmp->next;
        }
        // for(int k=0; k<n; k++){
        //     printf("%d ", min_path[k]);
        // }
        // printf("\n");
        for(int j=0; j<n; j++){
            if((min_path[j]<min_weight)&&(visited[j] == 0)){
                min_weight = min_path[j];
                min_index = j;
            }
        }
        visited[min_index] = 1;
        num = min_index;
        total_weight=total_weight+min_path[min_index];
    }

    printf("%lld", total_weight);

}