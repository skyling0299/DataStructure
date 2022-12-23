#include <iostream>
using namespace std;

typedef struct node{
    string name;
    int score;
}node;
long long int _index = 0;
void quicksort(node list[], int left, int right){
    int pivot, i, j;
    node temp;
    if(left < right){
        i = left+1; //left is pivot
        j = right; //right is the last to search
        pivot = list[left].score;
        while(i<=j){
            while((i<=j)&&((list[i].score < pivot)||((list[i].score == pivot)&&(list[i].name>list[left].name)))){
                i++;
            }
            while((i<=j)&&((list[j].score > pivot)||((list[j].score == pivot)&&(list[j].name<list[left].name)))){
                j--;
            }
            
            if(i<j){ //not cross
                temp = list[i];
                list[i] = list[j];
                list[j] = temp; //change the student's node
                i++;
                j--;
            }
            else{
                break; //from willy
            }
        }
        temp = list[left];
        list[left] = list[j];
        list[j] = temp;
        
        _index++;
        cout<<"The index of the "<<_index<<"-th pivot is "<<j<<"."<<endl;
        quicksort(list, left, j-1);
        quicksort(list, j+1, right);
    }

}
int main(){
    int num;
    cin>>num;
    node list[num];
    for(int i=0; i<num; i++){
        cin>>list[i].name>>list[i].score;
    }
    quicksort(list, 0, num-1);
    for(int i=0; i<num-1; i++){
        cout<<list[i].name<<" "<<list[i].score<<endl;
    }
    cout<<list[num-1].name<<" "<<list[num-1].score;
}
