#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 10000
char expr[MAX_STACK_SIZE];
char result[MAX_STACK_SIZE];
int r_index;

void postfix(){
    r_index = 0;
    int s_index = -1;
    char stack[MAX_STACK_SIZE];
    char symbol;
    for(int e_index = 0; e_index < strlen(expr); e_index++){
        symbol = expr[e_index];
        if(symbol == '('){
            stack[++s_index] = symbol;
        }
        else if(symbol == ')') {
            while(stack[s_index] != '('){
                result[r_index++] = stack[s_index--];
            }
            s_index--;
        }
        else if((symbol == '+')||(symbol == '-')){
            while((stack[s_index] != '(') && (s_index != -1)){
                result[r_index++] = stack[s_index--];
            }
            stack[++s_index] = symbol;
        }
        else if((symbol == '*')||(symbol == '/')){
            while(((stack[s_index] == '*') || (stack[s_index] == '/')) && (s_index != -1)){
                result[r_index++] = stack[s_index--];
            }
            stack[++s_index] = symbol;
        }
        else if(('0'<= symbol) && (symbol <= '9')){
            result[r_index++] = symbol;
        }
        else{};
        //printf("%c ", symbol);
    }
    while(s_index != -1){
        result[r_index++] = stack[s_index--];
    }
}

void main(){
    int num = 0;
    
    scanf("%d", &num);
    for(int i = 0; i< num; i++){
        fflush(stdin);
        scanf(" %[^\n]", expr);
        postfix();
        for(int j = 0; j < r_index; j++){
            printf("%c ", result[j]);
        }
        printf("\n");
    }
}

