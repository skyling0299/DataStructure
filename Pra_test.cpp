#include <iostream>
using namespace std;
struct node{
int value;
struct node * next;
};
struct node n1, n2, n3, n4;
void f(struct node *p){
    printf("here2\n");
    struct node * q;
    int t;
    if(p == NULL) return;
    for(q = p; p->next != NULL; p = p ->next){
        for(q = p; q->next != NULL; q = q->next){
            if( (q->value % 2 == 0) && (q->next->value < q->value) ){
                t = q->next->value;
                q->next->value = q->value;
                q->value=t;
            }
        }
    }
} //changes
int main(void){
    printf("here\n");
    struct node * p;
    n1.value=8; n2.value=3; n3.value=2; n4.value=7;
    n1.next=&n2; n2.next=&n3; n3.next=&n4; n4.next=NULL;
    for(p = &n1; p != NULL; p = p->next){
        cout<<p->value<<" "; //output the value
    }
    f(&n1); //& is address-of operator
    for(p = &n1; p != NULL; p = p->next){
        cout<<p->value<<" "; //output the value
    }
}