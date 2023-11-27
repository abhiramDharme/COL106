#include <iostream>
#include <stdexcept>
#include "list.h"
using namespace std;

List::List(){
    size = 0;
    sentinel_head = new Node(true);
    sentinel_tail = new Node(true);
    sentinel_head->next = sentinel_tail;
    sentinel_tail->prev = sentinel_head;
    sentinel_head->prev = nullptr;
    sentinel_tail->next = nullptr;
}

List::~List(){

}

void List::insert(int v){
    Node* node = new Node(v, sentinel_tail, sentinel_tail->prev);
    node->prev->next = node;
    sentinel_tail->prev = node;
    size++;   
}

int List::delete_tail(){
    if(size==0){
        throw runtime_error("Empty Stack");
    }
    else{
        Node* temp = new Node();
        temp = sentinel_tail->prev;
        sentinel_tail->prev = sentinel_tail->prev->prev;
        sentinel_tail->prev->next = sentinel_tail;
        temp->prev = nullptr;
        temp->next = nullptr;
        int a = temp->get_value();
        delete(temp);
        size--;
        return a;
    }
}

int List::get_size(){
    return size;
}

Node* List::get_head(){
    return sentinel_head;
}
