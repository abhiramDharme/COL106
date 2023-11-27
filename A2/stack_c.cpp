#include <iostream>
#include <stdexcept>
#include "stack_c.h"
using namespace std;
//                   //remember to debug list such as delete_tail

Stack_C::Stack_C(){
    stk = new List();
}

Stack_C::~Stack_C(){
    delete(stk);
}

void Stack_C::push(int data){
    stk->insert(data);
}

int Stack_C::pop(){
    return stk->delete_tail();
}

int Stack_C::get_element_from_top(int idx){
    if(idx>=stk->get_size()){
        throw runtime_error("Index out of range");
    }
    else{
        Node* temp = new Node();
        temp = stk->get_head();
        for(int i=0; i<stk->get_size()-idx; i++){
            temp = temp->next;
        }
        return temp->get_value();
    }
}

int Stack_C::get_element_from_bottom(int idx){
    if(idx>=stk->get_size()){
        throw runtime_error("Index out of range");
    }
    else{
        Node* temp = new Node();
        temp = stk->get_head();
        for(int i=0; i<=idx; i++){
            temp = temp->next;
        }
        return temp->get_value();
    }
}

void Stack_C::print_stack(bool top_or_bottom){
    if(top_or_bottom==0){
        Node* temp = new Node();
        temp = stk->get_head();
        for(int i=0; i<stk->get_size(); i++){
            temp = temp->next;
            cout << temp->get_value() << "\n";
        }
    }
    else{
        Node* temp = new Node();
        temp = stk->get_head();
        while(temp->next!=nullptr){
            temp = temp->next;
        }
        for(int i=0; i<stk->get_size(); i++){
            temp = temp->prev;
            cout << temp->get_value() << "\n";
        }
    }
}

int Stack_C::add(){
    if(stk->get_size()<=1){throw runtime_error("Not Enough Arguments");}
    int a = pop();
    int b = pop();
    int ans = a+b;
    push(ans);
    return ans;
}

int Stack_C::subtract(){
    if(stk->get_size()<=1){throw runtime_error("Not Enough Arguments");}
    int a = pop();
    int b = pop();
    int ans = b-a;
    push(ans);
    return ans;
}

int Stack_C::multiply(){
    if(stk->get_size()<=1){throw runtime_error("Not Enough Arguments");}
    int a = pop();
    int b = pop();
    int ans = a*b;
    push(ans);
    return ans;
}

int Stack_C::divide(){
    if(stk->get_size()<=1){throw runtime_error("Not Enough Arguments");}
    int a = pop();
    int b = pop();
    if(a==0){
        throw runtime_error("Divide by Zero Error");
    }
    else if(((a<0)^(b<0)) && b % a){
        push(b/a-1);
        return b/a-1;
    }
    else{
        push(b/a);
        return b/a;
    }
}

List* Stack_C::get_stack(){
    return stk;
}

int Stack_C::get_size(){
    return stk->get_size();
}