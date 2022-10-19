#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1
typedef struct node *node_pointer;
struct node{
    int data;
    node_pointer link;
}node;

int main(){
    short int out[MAX_SIZE];
    node_pointer seq[MAX_SIZE];
    node_pointer x, y, top;
    int i, j, n;
    printf("Enter the size (<=%d)", MAX_SIZE);
    scanf("%d", &n);
    for(i=0; i<n; i++){
        out[i] = TRUE; //true
        seq[i] = NULL;
    }
    printf("Enter a pair of numbers (-1 -1 to quit): ");
    scanf("%d %d", &i, &j);
    while(i>=0){
        x = (node_pointer)malloc(sizeof(node));
        x->data = j;
        x->link = seq[i];
        seq[i] = x;
        x = (node_pointer)malloc(sizeof(node));
        x->data = i;
        x->link = seq[j];
        seq[j] = x;
        
        printf("Enter a pair of numbers(-1 -1 to quit): ");
        scanf("%d %d", &i, &j);
    }
    for(i = 0; i<n; i++){
        if(out[i]){
            printf("New class: %d ", i);
            out[i] = FALSE;
            x = seq[i];
            top = NULL;
            while(1){
            while(x){
                j = x->data;
                //printf("\n now i found %d\n", j);
                if(out[j]){
                    printf("%d ", j);
                    out[j] = FALSE;
                    y = x->link;
                    x->link = top;
                    top = x;
                    x = y; //做了一個反轉，將原序列反轉排列
                }
                else {
                    x= x->link;
                }
            }
            if(top == NULL) break;

            x = seq[top->data];
            top = top->link; //top->link == NULL
            }
        }
    }
}