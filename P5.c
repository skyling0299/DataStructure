#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *node_pointer;
typedef struct node{
    node_pointer left_child;
    char data;
    node_pointer right_child;
}node;
typedef struct queue_node *queue_pointer;
typedef struct queue_node{
    node_pointer data;
    queue_pointer link;
}queue_node; //fifo structure to create tree
queue_pointer first = NULL , rear = NULL;

int _pow(int base, int exp){
    int sum = 1;
    for(int i=0; i<exp; i++){
        sum = (sum * base);
    }
    return sum;
}

void push(node_pointer data){
    queue_pointer temp = (queue_pointer)malloc(sizeof(queue_node));
    temp -> link = NULL;
    temp -> data = data;
    if(first == NULL){
        first = temp;
        rear = temp;
    }
    else{
        rear -> link = temp;
        rear = temp;
    }
}//add node to the end of the queue


node_pointer add(char data, node_pointer pointer){
    node_pointer temp = (node_pointer)malloc(sizeof(node));
    temp -> data = data;
    temp -> left_child = NULL;
    temp -> right_child = NULL;
    if(pointer == NULL){
        return temp;
    }
    else if(pointer -> left_child == NULL){
        pointer -> left_child = temp;
        push(temp);
        return pointer; //parent have null right child
    }
    else if(pointer -> right_child == NULL){
        pointer -> right_child = temp;
        push(temp);
        queue_pointer tmp = first;
        first = first -> link; //move first to next
        return tmp -> data; //return first in queue as next parent
    }
}//try recursive, add is a function that can create a sub tree
node_pointer create(int total_level){
    char data[3];
    node_pointer parent=NULL, root=NULL;
    for(int i = 0; i < total_level; i++){
        getchar(); //get \n
        for(int j = 0; j<(_pow(2, i)); j++){
            //printf("%d\n", _pow(2, i));
            scanf("%s", data);
            char d;
            if(strcmp(data, "-1") == 0){
                d = 'n';
            }
            else{
                d = data[0];
            }
            if(root == NULL){
                root = add(d, parent);
                parent = root;
            }
            else{
                parent = add(d, parent);
            }
            
            
        }
    }
    return root;
}
long long int stack[10];
int stack_pointer = -1;
long long int postorder(node_pointer ptr){
    
    long long int sum=0;
    if(ptr){
        postorder(ptr->left_child);
        postorder(ptr->right_child);
        if(ptr->data != 'n'){
            if(ptr->data == '+'){
                stack[stack_pointer-1] = stack[stack_pointer] + stack [stack_pointer-1];
                stack_pointer = stack_pointer - 1;
            }
            else if(ptr->data == '-'){
                stack[stack_pointer-1] = stack[stack_pointer-1] - stack [stack_pointer];
                stack_pointer = stack_pointer - 1;
            }
            else if(ptr->data == '*'){
                stack[stack_pointer-1] = stack[stack_pointer-1] * stack [stack_pointer];
                stack_pointer = stack_pointer - 1;
            }
            else if(ptr->data == '/'){
                stack[stack_pointer-1] = stack[stack_pointer-1] / stack [stack_pointer];
                stack_pointer = stack_pointer - 1;
            }
            else if(('0'<= ptr->data)&&(ptr->data <= '9')){
                stack[++stack_pointer] = ptr->data-'0';
            }
        }
        return stack[stack_pointer];
    }
    
}
void main(){
    int total_level;
    scanf("%d", &total_level);
    node_pointer root=NULL;
    first = NULL, rear = NULL;
    //int n;
    root = create(total_level);
    long long int a = postorder(root);
    printf("%lld", a);
    printf("\n");

}
