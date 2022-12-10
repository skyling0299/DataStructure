#include <stdio.h>
#include <stdlib.h>
typedef struct node *node_pointer;
typedef struct node
{
    node_pointer left_child;
    int data;
    node_pointer right_child;
}node;
typedef struct queue_node *queue_pointer;
typedef struct queue_node
{
    node_pointer data;
    queue_pointer link;
}queue_node; //fifo structure to create tree
queue_pointer first = NULL , rear = NULL;

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


node_pointer add(int data, node_pointer pointer){
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
node_pointer create(int node_num){
    int data;
    node_pointer parent=NULL, root=NULL;
    for(int i = 0; i < node_num; i++){
        scanf("%d", &data);
        if(root == NULL){
            root = add(data, parent);
            parent = root;
        }
        else{
            parent = add(data, parent);
        }
    }
    return root;
}
void inorder(node_pointer ptr){
    if(ptr){
        inorder(ptr->left_child);
        printf("%d ", ptr->data);
        inorder(ptr->right_child);
    }
}
void preorder(node_pointer ptr){
    if(ptr){
        printf("%d ", ptr->data);
        preorder(ptr->left_child);
        preorder(ptr->right_child);
    }
}
void postorder(node_pointer ptr){
    if(ptr){
        postorder(ptr->left_child);
        postorder(ptr->right_child);
        printf("%d ", ptr->data);
    }
}
void main(){
    int total_number;
    scanf("%d", &total_number);
    for(int i=0; i<total_number; i++){
        node_pointer root=NULL;
        first = NULL, rear = NULL;
        int n;
        scanf("%d", &n);
        root = create(n);
        preorder(root);
        printf("\n");
        inorder(root);
        printf("\n");
        postorder(root);
        printf("\n");
    }
}
