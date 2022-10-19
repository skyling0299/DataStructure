#include <stdio.h>
#include <stdlib.h>
#define MAXSTACK 250
int top=-1;
/*define struct*/
typedef struct{
    short int row;
    short int col;
    short int dir;
}element;
element stack[MAXSTACK];

typedef struct
{
    short int vert;
    short int horiz;
}offsets;

void add(element);
element delete();

int main(int argc, char const *argv[])
{
    /*define maze */
    int r=0, c=0;
    scanf("%d %d", &r, &c);
    int maze[r+2][c+2];
    int m=0;
    for(int i=0; i<r+2; i++){
        for(int j=0; j<c+2; j++){
            if(i==0 || i==r+1) maze[i][j] = 1;
            else if (j==0 || j==c+1) maze[i][j] = 1;
            else{
                scanf("%d", &m);
                maze[i][j]= m;
            }
        }
    }

    /*define other dependencies*/
    int mark[r+2][c+2];
    for(int i=0; i<r+2; i++){
        for(int j=0; j<c+2; j++) mark[i][j]=0;
    }
    offsets move[8];
        move[0].vert = -1 ; move[0].horiz = 0;
        move[1].vert = 0 ; move[1].horiz = 1;
        move[2].vert = 1 ; move[2].horiz = 0;
        move[3].vert = 0 ; move[3].horiz = -1;


    /*loop*/
    int exit_row = r, exit_col = c;
    int i, row, col, next_row, next_col, dir, found = 0; /* there is no boolean in c */
    element position;
    mark[1][1] = 1; top = 0;
    stack[0].row = 1; stack[0].col = 1; stack[0].dir = 0;
    while(top> -1 && found==0){
        position = delete();
        row = position.row; col = position.col; dir = position.dir;
        while(dir < 4 && found==0){
            next_row = row+move[dir].vert;
            next_col = col+move[dir].horiz; //try 4 direction
            if(next_col == exit_col && next_row == exit_row){
                found = 1;
                position.row = row; 
                position.col = col; 
                position.dir = dir; //memorize now's position and direction
                add(position);  
            }
            else if(maze[next_row][next_col]==0 && mark[next_row][next_col]==0){
                mark[next_row][next_col] = 1; //mark it as "tried"
                position.row = row; 
                position.col = col; 
                position.dir = dir; //memorize now's position and direction
                add(position);  
                dir = 0; row = next_row; col = next_col; //move to the next step
            }
            else{
                dir++;
            }
        }
    }

    if(found){
        printf("(0,0) ");
        for(int i=1; i<=top; i++){
            printf("(%d,%d) ", stack[i].row -1 , stack[i].col -1);
        }
        printf("(%d,%d)", r-1, c-1);
    }
    else printf("Can't reach the exit!");
}

void add(element data){
    if(top>=MAXSTACK) {
        printf("out of stack");
    }
    else{
        top=top+1;
        stack[top].row = data.row;
        stack[top].col = data.col;
        stack[top].dir = data.dir;
    }
}
element delete(){
   top=top-1;
   return stack[top+1];
}

