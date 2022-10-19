#include <stdio.h>
#include <stdlib.h>

typedef struct poly_node *poly_pointer;
typedef struct poly_node{
    int coef; 
    int expon; 
    struct poly_node *link;
}poly_node; //typedef and struct's usage
poly_pointer a_front= NULL, b_front = NULL, d_front = NULL; //point to the linklist's start

void add(int coefficient, int exponent, poly_pointer *ptr){
    // this function will add poly_node to the front of the linklist
    poly_pointer temp = (poly_pointer) malloc (sizeof(poly_node));
    temp->coef = coefficient;
    temp->expon = exponent;
    temp->link =  NULL; 

    if(*ptr == NULL){ //if the link is null
        *ptr = temp;
    }
    else{ //attach poly_node to the front, and made linklist's front the address point to temp
        temp->link = *ptr;
        *ptr = temp;
    }
    
}

poly_pointer padd(poly_pointer a_front, poly_pointer b_front){
    poly_pointer a_recent = a_front, b_recent = b_front, c_front = NULL;
    while((a_recent != NULL) && (b_recent != NULL)){
        if(a_recent->expon < b_recent->expon){
            add(a_recent->coef, a_recent->expon, &c_front);
            a_recent = a_recent->link;
        }
        else if(a_recent->expon == b_recent->expon){
            int coef_sum;
            coef_sum = a_recent->coef + b_recent->coef;
            add(coef_sum, a_recent->expon, &c_front);
            a_recent = a_recent->link;
            b_recent = b_recent->link;
        }
        else{
            add(b_recent->coef, b_recent->expon, &c_front);
            b_recent = b_recent->link;
        }
    }
    while(a_recent != NULL){
        add(a_recent->coef, a_recent->expon, &c_front);
        a_recent = a_recent->link;
    }
    while(b_recent != NULL){
        add(b_recent->coef, b_recent->expon, &c_front);
        b_recent = b_recent->link;
    }
    //no matter which will end first, just check it out anyway
    return c_front; //return the linklist
}

int main(){
    int num_a, num_b, c, e;
    scanf("%d", &num_a);
    for(int i=0; i<num_a; i++){
        scanf("%d %d", &c, &e);
        add(c, e, &a_front);
    }
    scanf("%d", &num_b);
    for(int i=0; i<num_b; i++){
        scanf("%d %d", &c, &e);
        add(c, e, &b_front);
    }
    d_front = padd(a_front, b_front); //add the two polys

    poly_pointer r = d_front; 
    while(r != NULL){
        if(r->coef != 0){
            printf("%d %d ", r->coef, r->expon);
        }
        r = r->link;
    }
}