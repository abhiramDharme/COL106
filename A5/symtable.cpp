/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
//#include <iostream>
//Write your code below this line
// #include <bits/stdc++.h>
//
SymbolTable::SymbolTable(){
    size = 0;
    root = NULL;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int High3(SymNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int Balance(SymNode* node) {
    if (node == NULL) {
        return 0;
    }
    return High3(node->left) - High3(node->right);
}

void getH(SymNode* node) {
    node->height = 1 + max(High3(node->left), High3(node->right));
}

SymNode* anticlockwise(SymNode* newS) {
    SymNode* oldS= newS->left;
    SymNode* navin = oldS->right;
    oldS->right = newS;
    newS->left = navin;
    getH(newS);
    getH(oldS);
    return oldS;
}

SymNode* clockwise(SymNode* oldS) {
    SymNode* newS = oldS->right;
    SymNode* navin = newS->left;
    newS->left = oldS;
    oldS->right = navin;
    getH(oldS);
    getH(newS);
    return newS;
}

SymNode* Ins(SymNode* node, string key, int &size) {
    if (node == NULL) {
        SymNode* nd =  new SymNode(key);
        size++;
		return nd;
    }
    if (key < node->key) {
        node->left = Ins(node->left, key, size);
    } else if (key > node->key) {
        node->right = Ins(node->right, key, size);
    } 
    else{
		return node;
    }
    getH(node);
    int balance = Balance(node);
    // Davi side
    if (balance > 1) {
        if (key < node->left->key) {
            return anticlockwise(node);
        } else {
            node->left = clockwise(node->left);
            return anticlockwise(node);
        }
    }
    // Ujvi side
    if (balance < -1) {
        if (key > node->right->key) {
            return clockwise(node);
        } else {
            node->right = anticlockwise(node->right);
            return clockwise(node);
        }
    }
    getH(node);
    return node;
}

void SymbolTable::insert(string k) {
	//cout<<"inserting "<<k<<endl;
    root = Ins(root, k,size);
}

SymNode* minValueNode(SymNode* node) {
    SymNode* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

SymNode* DEL(SymNode* root, string key) {
    if (root == NULL) {
        return root;
    }
    if (key < root->key) {
        root->left = DEL(root->left, key);
    } else if (key > root->key) {
        root->right = DEL(root->right, key);
    } else {
        if (root->left == NULL || root->right == NULL) {
            SymNode* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            SymNode* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = DEL(root->right, temp->key);
        }
    }
    if (root == NULL) {
        return root;
    }
    getH(root);
    int balance = Balance(root);
    // Davi Side
    if (balance > 1) {
        if (Balance(root->left) >= 0) {
            return  anticlockwise(root);
        } else {
            root->left =  clockwise(root->left);
            return  anticlockwise(root);
        }
    }
    // Ujvi Side
    if (balance < -1) {
        if (Balance(root->right) <= 0) {
            return clockwise(root);
        } else {
            root->right = anticlockwise(root->right);
            return clockwise(root);
        }
    }
    return root;
}

SymNode* Search(SymNode* root, string k) {
    if (root == NULL) {
        return NULL;
    }
    if (root->key == k) {
        return root;
    }
    if (root->key < k) {
        return Search(root->right, k);
    }
    else {
        return Search(root->left, k);
    }
    return NULL;
}

void SymbolTable::remove(string k) {
    SymNode* temp = Search(root, k);
    if (temp != NULL) {root =  DEL(root, k);}
    return;
}

int SymbolTable::search(string k){
    SymNode* node = Search(root, k);
    // cout<<"idhar "<<k<<endl;
    if (node == NULL) {
        return -2;
    }
	// cout<<"mil gaya"<<endl;
    return node->address;
}

// void inOrderTraversal(SymNode* node) {
//     if (node == NULL) {
//         return;
//     }

//     inOrderTraversal(node->left);
//     std::cout << node->key << " ";
//     inOrderTraversal(node->right);
// }

void Assign(SymNode* root, string k, int idx) {
    //cout<<"assign "<<k<<" "<<idx<<endl;
    if (root == NULL) {
        return;
    }
    if (root->key == k) {
		//cout<<"mil gya "<<k<<endl;
        root->address = idx;
        // cout << root->address << endl;;
        return;
    }
    if (root->key < k) {
        Assign(root->right, k, idx);
    }
    else {
        Assign(root->left, k, idx);
    }
    return;
}

void SymbolTable::assign_address(string k,int idx){
    //cout<<"assign_addr"<<" "<<k<<" "<<idx<<endl;
    //cout<<"sz"<<" "<<size<<endl;
    Assign(root, k, idx);
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

// void del(SymNode* root) {
//     if (!root) {
//         return;
//     }
//     del(root->left);
//     del(root->right);
//     delete root;
// }

SymbolTable::~SymbolTable(){
    // del(root);
    // root = NULL;
    if (root != NULL) delete root;
}

// int main() {
//     SymbolTable* tree = new SymbolTable();

//     tree->insert("s");
//     tree->insert("h");
//     tree->insert("a");

//     std::cout << "Inorder traversal of the AVL tree: ";
//     inOrderTraversal(tree->get_root());

//     tree->remove("h");

//     std::cout << "Inorder traversal after removing h: ";
//     inOrderTraversal(tree->get_root());

//     return 0;
// }
