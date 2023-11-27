#include <iostream>
#include <stdexcept>
#include "stack_a.h"
using namespace std;

Stack_A::Stack_A(){
    size = 0;
}

void Stack_A::push(int x){
    if(size==1024){
        throw runtime_error("Stack Full");
    }
    else{
        stk[size++] = x;
    }
}

int Stack_A::pop(){
    if(size==0){
        throw runtime_error("Empty Stack");
    }
    else{
        return stk[--size];
    }
}

int Stack_A::get_element_from_top(int x){
    if(x>=size){
        throw runtime_error("Index out of range");
    }
    else{
        return stk[size-x-1];
    }
}

int Stack_A::get_element_from_bottom(int x){
    if(x>=size){
        throw runtime_error("Index out of range");
    }
    else{
        return stk[x];
    }
}

void Stack_A::print_stack(bool top){
    if(top){
        for(int k=size-1; k>=0; k--){
            cout << stk[k] << "\n";
        }
    }
    else{
        for(int k=0; k<=size-1; k++){
            cout << stk[k] << "\n";
        }
    }
}

int Stack_A::add(){
    if(size<=1){
        throw runtime_error("Not Enough Arguments");
    }
    else{
        stk[size-2] = stk[size-1]+stk[size-2];
        size--;
        return stk[size-1];
    }
}

int Stack_A::subtract(){
    if(size<=1){
        throw runtime_error("Not Enough Arguments");
    }
    else{
        stk[size-2] = -stk[size-1]+stk[size-2];
        size--;
        return stk[size-1];
    }
}

int Stack_A::multiply(){
    if(size<=1){
        throw runtime_error("Not Enough Arguments");
    }
    else{
        stk[size-2] = stk[size-1]*stk[size-2];
        size--;
        return stk[size-1];
    }
}

int Stack_A::divide(){
    if(size<=1){
        throw runtime_error("Not Enough Arguments");
    }
    else if(stk[size-1]==0){
        throw runtime_error("Divide by Zero Error");
    }
    else if(stk[size-2]%stk[size-1] != 0 && (stk[size-2]<0^stk[size-1]<0)){
        stk[size-2] = stk[size-2]/stk[size-1]-1;
        size--;
        return stk[size-1];
    }
    else{
        stk[size-2] = stk[size-2]/stk[size-1];
        size--;
        return stk[size-1];
    }
}

int* Stack_A::get_stack(){
    int* p;
    p = stk;
    return p;
}

int Stack_A::get_size(){
    return size;
}
