#include <iostream>
#include "stack_b.h"
#include <stdexcept>
using namespace std;
const int limit = 1024;

Stack_B::Stack_B(){
    capacity = limit;
    size = 0;
    stk = new int[capacity];
}

Stack_B::~Stack_B(){
    delete[] stk;
}

void Stack_B::push(int data){
    if(size==capacity){
        capacity *= 2;
        int* temp = new int[capacity];
        for(int i=0; i<size; i++){
            temp[i] = stk[i];
        }
        temp[size++] = data;
        delete[] stk;
        stk = temp;
    }
    else{
        stk[size++] = data;
    }
}

int Stack_B::pop(){
    if(size==0){
        throw runtime_error("Empty Stack");
    }
    else{
        int a = stk[--size];
        if(limit<=size && size<=capacity/4){
            capacity /= 4;
            int* temp = new int[capacity];
            for(int i=0; i<size; i++){
                temp[i] = stk[i];
            }
            delete[] stk;
            stk = temp;
        }
        return a;
    }
}

int Stack_B::get_element_from_top(int x){
    if(x>=size){
        throw runtime_error("Index out of range\n");
    }
    else{
        return stk[size-x-1];
    }
}

int Stack_B::get_element_from_bottom(int x){
    if(x>=size){
        throw runtime_error("Index out of range\n");
    }
    else{
        return stk[x];
    }
}

void Stack_B::print_stack(bool top){
    if(top==1){
        for(int k=size-1; k>=0; k--){
            cout << stk[k] << "\n";
        }
    }
    else{
        for(int k=0; k<size; k++){
            cout << stk[k] << "\n";
        }
    }
}

int Stack_B::add(){
    if(size<2){
        throw runtime_error("Not Enough Arguments");
    }
    else{
        stk[size-2] = stk[size-1]+stk[size-2];
        size--;
        int a = stk[size-1];
        if(limit<=size && size<=capacity/4){
            capacity = capacity/4;
            int* temp = new int[capacity];
            for(int i=0; i<size; i++){
                temp[i] = stk[i];
            }
            delete[] stk;
            stk = temp;
        }
        return a;
    }
}

int Stack_B::subtract(){
    if(size<2){
        throw runtime_error("Not Enough Arguments");
    }
    else{
        stk[size-2] = stk[size-2]-stk[size-1];
        size--;
        int a = stk[size-1];
        if(limit<=size && size<=capacity/4){
            capacity = capacity/4;
            int* temp = new int[capacity];
            for(int i=0; i<size; i++){
                temp[i] = stk[i];
            }
            delete[] stk;
            stk = temp;
        }
        return a;
    }
}

int Stack_B::multiply(){
    if(size<2){
        throw runtime_error("Not Enough Arguments");
    }
    else{
        stk[size-2] = stk[size-2]*stk[size-1];
        size--;
        int a = stk[size-1];
        if(limit<=size && size<=capacity/4){
            capacity = capacity/4;
            int* temp = new int[capacity];
            for(int i=0; i<size; i++){
                temp[i] = stk[i];
            }
            delete[] stk;
            stk = temp;
        }
        return a;
    }
}

int Stack_B::divide(){
    if(size<2){
        throw runtime_error("Not Enough Arguments");
    }
    else if(stk[size-1]==0){
        throw runtime_error("Divide by Zero Error");
    }
    else if(stk[size-2]%stk[size-1] != 0 && (stk[size-1]<0)^(stk[size-2]<0)){
        stk[size-2] = stk[size-2]/stk[size-1]-1;
        size--;
        int a = stk[size-1];
        if(limit<=size && size<=capacity/4){
            capacity = capacity/4;
            int* temp = new int[capacity];
            for(int i=0; i<size; i++){
                temp[i] = stk[i];
            }
            delete[] stk;
            stk = temp;
        }
        return a;
    }
    else{
        stk[size-2] = stk[size-2]/stk[size-1];
        size--;
        int a = stk[size-1];
        if(limit<=size && size<=capacity/4){
            capacity = capacity/4;
            int* temp = new int[capacity];
            for(int i=0; i<size; i++){
                temp[i] = stk[i];
            }
            delete[] stk;
            stk = temp;
        }
        return a;
    }
}

int Stack_B::get_size(){
    return size;
}

int* Stack_B::get_stack(){
    return stk;
}