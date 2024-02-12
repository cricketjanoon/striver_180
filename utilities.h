#ifndef _UTILITIES_H_
#define _UTILITIES_H_
#include <iostream>
#include <algorithm>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>
#include <stack>
#include <unordered_map>
#include <string>
#include <sstream>
#include <cmath>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include <list>

using namespace std;

struct Pair {
    int first;
    int second;
};

void swap(int& a, int &b);
void swap_ptr(int* x, int* y);
void print_array(int *array, int size);

void swap(int& a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void swap_ptr(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

template <typename T>
void swap_generic(T *x, T *y) {
    T temp = *x;
    *x = *y;
    *y = temp;
}

void print_array(int *array, int size){
    for(int i=0; i<size; i++){
        cout << array[i] << " ";
    }
    cout << endl;
}

template <typename T>
void print_vector(vector<T> &vec, string separator=" ", string end_string="\n"){
    for(int i=0; i<vec.size(); i++){
        cout << vec.at(i);
        if(i!=vec.size()-1) cout << separator;
    }
    cout << end_string;
}

template <typename T>
void print_matrix(vector<vector<T>> matrix, string separator=" "){
    int rows = matrix.size();
    int columns = matrix[0].size();

    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            cout << matrix[i][j] << separator;
        }
        cout << endl;
    }
}

template <typename T>
void print_queue(queue<T> qu){
    while(!qu.empty()){
        int data = qu.front();
        qu.pop();
        cout << data << ", ";
    }
    cout << endl;
}

template <typename T>
std::string ToString(const T& value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}

#endif
