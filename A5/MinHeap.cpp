// /* Do NOT add/remove any includes statements from this header file */
// /* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"
// #include <bits/stdc++.h>
// //Write your code below this line

void swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}

int Height(HeapNode* root) {
    if (!root) {
        return -1;
    }
    return max(Height(root->left), Height(root->right)) +1;
} 

MinHeap::MinHeap(){
    size = 0;
    root = NULL;
}

string BinNum(int decimal) {
    if (decimal == 0) {
        return "0";
    }
    string binary = "";
    while (decimal > 0) {
        int remainder = decimal % 2;
        binary = to_string(remainder) + binary;
        decimal /= 2;
    }
    return binary;
}

void HeapifyUp(HeapNode* newNode) {
    if (newNode->par == NULL) {
        return;
    }
    if (newNode->val < newNode->par->val) {
        swap(newNode->val, newNode->par->val);
        return HeapifyUp(newNode->par);
    }
}

void MinHeap::push_heap(int num) {
    size++;
    if (!root) {
        root = new HeapNode(num);
        return;
    }
    string binarySize = BinNum(size);
    HeapNode* current = root;
    for (int i = 1; i < binarySize.size(); i++) {
        if (binarySize[i] == '0') {
            if (current->left == NULL) {
                current->left = new HeapNode(num);
                current->left->par = current;
                current = current->left;
            } else {
                current = current->left;
            }
        } else {
            if (current->right == NULL) {
                current->right = new HeapNode(num);
                current->right->par = current;
                current = current->right;
            } else {
                current = current->right;
            }
        }
    }
    HeapifyUp(current);
}

int MinHeap::get_min(){
    if (size >= 1 && root != NULL) return root->val;
    return -1;
}

void HeapifyDown(HeapNode* root) {
    HeapNode* leftChild = root->left;
    HeapNode* rightChild = root->right;
    HeapNode* lessVal = root;
    if (leftChild != NULL && leftChild->val < root->val) {
        lessVal = leftChild;
    }
    if (rightChild != NULL && rightChild->val < lessVal->val) {
        lessVal = rightChild;
    }
    if (lessVal != root) {
        swap(root->val, lessVal->val);
        HeapifyDown(lessVal);
    }
}

void MinHeap::pop() {
    if (size == 1) {
        delete root;
        root = nullptr;
        return;
    }
    string s = BinNum(size);
    int n = s.size();
    HeapNode* current = root;
    HeapNode* parent = NULL;
    for (int i = 1; i < n; i++) {
        parent = current;
        if (s[i] == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    root->val = current->val;
    if (s[n - 1] == '0') {
        delete parent->left;
        parent->left = NULL;
    } else {
        delete parent->right;
        parent->right = NULL;
    }
    size--;
    // cout << size << endl;
    if (root) {
        HeapifyDown(root);
    }
}

MinHeap::~MinHeap(){
    if (root != NULL) delete root;
}



// int main() {
//     MinHeap h;
//     int T; cin>>T;
//     int S = T;
//     while(T>0) {
//         h.push_heap(T);
//         T--;
//     }
//     while (S--)
//     {
//         cout << h.get_min() << " ";
//         h.pop();
//     }
//     cout << h.get_min();
// }
