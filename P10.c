#include <stdio.h>
void main(){
    int N, S, E;
    scanf("%d %d %d", &N, &S, &E);
    long int adj_matrix[N][N];
    long int shortest_path[N][N];
    int distance;
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            scanf("%d", &distance);
            if((distance == 0)&&(i!=j)){
                adj_matrix[i][j] = 1000000;
            }
            else{
                adj_matrix[i][j] = distance;
            }
            shortest_path[i][j] = adj_matrix[i][j];
        }
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            for(int k=0; k<N; k++){
                if(shortest_path[i][j] > shortest_path[i][k]+adj_matrix[k][j]){
                    shortest_path[i][j] = shortest_path[i][k]+adj_matrix[k][j];
                }
            }
        }
    }
    printf("%d", shortest_path[S][E]);
}