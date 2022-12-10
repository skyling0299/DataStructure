#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <deque>
#include <queue>
using namespace std;

typedef struct node *node_pointer;
typedef struct node{
    long long int data;
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
   node_pointer ptr = tree_ptr, previous_ptr = NULL;
   bool flag = false;
   int dir = 0;
   if(ptr == NULL){
        printf("cannot delete\n");
        return false;
   }
   else{
        while((ptr != NULL)&&(flag!=true)){ 
            if(num > ptr->data){
                dir = 1;
                previous_ptr = ptr;
                ptr = ptr->right;
            }
            else if(num < ptr->data){
                dir = -1;
                previous_ptr = ptr;
                ptr = ptr->left;
            }
            else if(num == ptr->data){
                flag = true;
                break;
            }
        }
        if(flag == false){
            printf("cannot delete\n");
            return false;
        }
        else{
            while(true){
                node_pointer f = ptr, pre = previous_ptr;
                if((ptr->left==NULL) || (ptr->right== NULL)){
                    if(dir == 0){
                        if(ptr->left != NULL){
                            tree_ptr = ptr->left;
                        }
                        else if(ptr->right != NULL){
                            tree_ptr = ptr->right;
                        }
                        else{
                            tree_ptr = NULL;
                        }
                    }
                    else{
                        if(ptr->left != NULL){
                            previous_ptr->left = ptr->left;
                        }
                        else if(ptr->right != NULL){
                            previous_ptr->right = ptr->right;
                        }
                        else{
                            if(dir == -1){
                                previous_ptr->left = NULL;
                            }
                            else if(dir == 1){
                                previous_ptr->right = NULL;
                            }
                        }
                    }
                    
                    break;
                }
                
                if(dir == -1){
                    // find it's left child's largest
                    while(f->right != NULL){
                        pre = f;
                        f = f->right;
                    }
                    ptr->data = f->data;
                    pre->right = NULL;
                    break;
                }
                else if(dir == 1){
                    while(f->left != NULL){
                        pre = f;
                        f = f->left;
                    }
                    ptr->data = f->data;
                    pre->left = NULL;
                    break;
                }
                else if(dir == 0){
                    
                    f = f->left;
                    while(f->right != NULL){
                        pre = f;
                        f = f->right;
                    }
                    if(pre == NULL){
                        ptr->data = f->data;
                        ptr->left = NULL;
                    }
                    else{
                        ptr->data = f->data;
                        pre->right = NULL;
                    }
                    break;
                }
            }
        }
        return true;
   }
   // now ptr points to the node to delete, previous ptr means the node who has a child pointed to it
   // flag means whether the code found the data to delete
   // dir false means left, true means right
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
    // deque<node_pointer> l;
    // node_pointer ptr = tree_ptr;
    // int height = 0;
    // if(tree_ptr == NULL){
    //     cout<<"0"<<endl;
    // }
    // else{
    //     l.push_front(ptr);
    //     while(!l.empty()){
    //         ptr = l.front();
    //         l.pop_front();
    //         height++;
            
    //         if(ptr->left != NULL){
    //             l.push_back(ptr->left);
    //         }
    //         if(ptr->right != NULL){
    //             l.push_back(ptr->right);
    //         }
    //     }
    // }

    if (tree_ptr == NULL) {
        cout << "0" << endl;
        return;
    }
    queue<node_pointer> q;
    q.push(tree_ptr);
    int height = 0;
    while (true) {
        int nodeCount = q.size();
        if (nodeCount == 0) {
            cout << height << endl;
            return;
        }
        height++;
        while (nodeCount > 0) {
            node_pointer node = q.front();
            q.pop();
            if (node->left != NULL) {
                q.push(node->left);
            }
            if (node->right != NULL) {
                q.push(node->right);
            }
            nodeCount--;
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