#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <deque>
using namespace std;

typedef struct node *node_pointer;
typedef struct node{
    int data;
    int level;
    node_pointer left;
    node_pointer right;
}node;

node_pointer tree_ptr = NULL;
vector<int> list;
int max_level=0;


void inorder(node_pointer ptr){
    if(ptr){
        inorder(ptr->left);
        list.push_back(ptr->data);
        inorder(ptr->right);
    }
}

void tree_search(int num){
    list.clear();
    node_pointer ptr = tree_ptr;
    inorder(ptr);
    if(num > list.size()){
        printf("\n");
    }
    else{
        printf("%d\n", list.at(num-1));
    }
}



void tree_insert(int num){
    /*
    insert num into the tree, if the number is repeat, ignore it and do not insert anything
    */
    node_pointer ptr, temp = NULL;
    temp = tree_ptr;
    ptr = (node_pointer)malloc(sizeof(node));
    ptr -> left = NULL;
    ptr -> right = NULL;
    ptr -> data = num;
    ptr -> level = 1;
    if (temp == NULL){
        tree_ptr = ptr;
        ptr->level = 1;

    }
    else{
        while(num != temp->data){
            if(num > temp->data){
                if(temp->right != NULL){
                    temp = temp->right;
                    (ptr->level)++;
                }
                else{
                    temp->right = ptr;
                    (ptr->level)++;
                    break;
                }
            }
            else{
                if(temp -> left != NULL){
                    temp = temp->left;
                    ptr->level++;
                }
                else{
                    temp->left = ptr;
                    ptr->level++;
                    break;
                }
            }
        }
        
    }

}

bool tree_delete(int num){
    /*
    delete num, if there are no num to delete, print cannot delete instead and return false
    */
   node_pointer ptr = tree_ptr, previous_ptr = tree_ptr;
   bool flag = false, dir = false;
   if(ptr == NULL){
        printf("cannot delete\n");
        return false;
   }
   while((ptr->right!=NULL)||(ptr->left!=NULL)||(num == ptr->data)){
        if((num == ptr->data)){
            if(ptr->left == NULL){
                dir = true;
            }
            flag = true;
            break;
        }
        if((num > ptr->data)&&(ptr->right!=NULL)){
            dir = true;
            previous_ptr = ptr;
            ptr = ptr->right;
        }
        else if((num < ptr->data)&&(ptr->left!=NULL)){
            dir = false;
            previous_ptr = ptr;
            ptr = ptr->left;
        }   
   }
   // now ptr points to the node to delete, previous ptr means the node who has a child pointed to it
   // flag means whether the code found the data to delete
   // dir false means left, true means right
   if(flag == false){
        printf("cannot delete\n");
        return false;
   }

   else{
        node_pointer temp = ptr, previous_temp = previous_ptr;
        
        if(dir == false){
            if((temp->right == NULL)&&(temp->left != NULL)){
                if(temp == previous_ptr){
                    tree_ptr = temp->left;
                }
                else{
                    previous_ptr->left = temp->left;
                }
            }
            else{
                while(temp->right != NULL){
                    previous_temp = temp;
                    temp = temp->right;
                }
                ptr->data = temp->data;
                if(previous_ptr == tree_ptr){
                    tree_ptr = temp->left;
                }
                else{
                    previous_temp->right = NULL;
                }
            }
            return true;
        }
        else if(dir == true){
            if((temp->left == NULL)&&(temp->right != NULL)){
                if(temp == previous_ptr){
                    tree_ptr = temp->right;
                }
                else{
                    previous_ptr->right = temp->right;
                }
            }
            else{
                while(temp->left != NULL){
                    previous_temp = temp;
                    temp = temp->left;
                }
                ptr->data = temp->data;
                if(previous_ptr == tree_ptr){
                    tree_ptr = temp->right;
                }
                else{
                    previous_temp->left = NULL;
                }
            }
            return true;
        }
   }
   return true;
}

void tree_traversal(){
    deque<node_pointer> l;
    node_pointer ptr = tree_ptr;
    l.push_front(ptr);
    
        while(!l.empty()){
            ptr = l.front();
            l.pop_front();
            printf("%d ", ptr->data);
            if(ptr->left != NULL){
                l.push_back(ptr->left);
            }
            if(ptr->right != NULL){
                l.push_back(ptr->right);
            }
        }
}
void height(){
    deque<node_pointer> l;
    node_pointer ptr = tree_ptr;
    l.push_front(ptr);
    
    while(!l.empty()){
        ptr = l.front();
        l.pop_front();
        if(ptr->level > max_level){
            max_level = ptr->level;
        }
        if(ptr->left != NULL){
            l.push_back(ptr->left);
        }
        if(ptr->right != NULL){
            l.push_back(ptr->right);
        }
    }
}
int main(){
    char cmd[20];
    int n;
    //scanf("%s", cmd);
    
    while(scanf("%s", cmd)){
        if(strcmp(cmd, "insert")==0){
            scanf("%d", &n);
            tree_insert(n);
        }
        else if(strcmp(cmd, "delete")==0){
            scanf("%d", &n);
            bool t = tree_delete(n);
        }
        else if(strcmp(cmd, "height")==0){
            height();
            printf("%d\n", max_level);
        }
        else if(strcmp(cmd, "search")==0){
            scanf("%d", &n);
            tree_search(n);
        }
        else if(strcmp(cmd, "traversal")==0){
            tree_traversal();
            break;
        }
        
    }
    return 0;
}