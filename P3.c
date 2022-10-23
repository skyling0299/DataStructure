#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 3000

typedef enum{lparen, rparen, times, plus, minus, divide, blank, operand, eos} precedence;

char expr[MAX_STACK_SIZE];
char result[MAX_STACK_SIZE];
int r = 0; //result index
int isp[48]; 
int icp[48];


char get_symbol(precedence p){
    switch (p)
    {
    case  lparen : return '(';
    case  rparen : return ')';
    case  plus : return '+';
    case  minus : return '-';
    case  times : return '*';
    case  divide : return '/';
    case  blank : return ' ';
    case  eos : return '\n';
    default : return ' ';
    }
} //get symbols of precedence

precedence get_token(char *symbol, int *n){
    *symbol = expr[(*n)++];

    switch (*symbol)
    {
    case '(' : return lparen;
    case ')' : return rparen;
    case '+' : return plus;
    case '-' : return minus;
    case '*' : return times;
    case '/' : return divide;
    case ' ' : return blank;
    case '\n': return eos;
    default : return operand;
    }
} //get precedence from symbol

void postfix(void){
    isp[10] = 0; isp[40] = 0; isp[41] = 19; isp[42] = 13; isp[43] = 12; isp[45] = 12; isp[47] = 13;
    icp[10] = 0; icp[40] = 20; icp[41] = 19; icp[42] = 13; icp[43] = 12; icp[45] = 12; icp[47] = 13;
    // set the piority
    char symbol;
    precedence token;
    precedence stack[MAX_STACK_SIZE];
    int n = 0;
    int top = 0;
    
    stack[0] = eos; //set stack[0]
    token = get_token(&symbol, &n); //get next symbol and convert it into precedence
    
    while(token != eos){
        if(token == operand){
            result[r++] = symbol;
            result[r++] = ' '; //put number in result array
        }
        else if(token == rparen){
            while((stack[top] != lparen) && (stack[top]!=eos)){
                result[r++] = get_symbol(stack[top--]);
                result[r++] = ' ';
                 //pop those between two paren
            }
            top--; //discard left paren
        }
        else if(token == blank); //do nothing
        else{
            while((isp[get_symbol(stack[top])] >= icp[symbol])&&(stack[top]!=eos)){
                result[r++] = get_symbol(stack[top--]);
                result[r++] = ' ';
            }
            stack[++top] = token; //put 
        }
        token = get_token(&symbol, &n);
    }
    
    while ((stack[top] != eos)){
        result[r++] = get_symbol(stack[top--]);
        result[r++] = ' ';
    } //pop those in the stack
    result[r++] = '\n';
}
int main(void){
    int lines;
    scanf("%d", &lines);
    for(int i=0; i<lines; i++){
        scanf(" %[^\n]", &expr);
        expr[strlen(expr)-1] = '\n';
        postfix();
    }
    
    for(int i=0; i< r-1; i++){
        printf("%c", result[i]); //print result
    }
    printf("\n");
}
