#include <iostream>
using namespace std;

void swap(int& a, int &b);
void print_array(int *array, int size);


void swap(int& a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void print_array(int *array, int size){
    for(int i=0; i<size; i++){
        cout << array[i] << " ";
    }
    cout << endl;
}