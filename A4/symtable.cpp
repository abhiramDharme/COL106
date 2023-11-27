#include "symtable.h"

// Default constructor
SymbolTable::SymbolTable() : size(0), root(nullptr) {}

// // Destructor
SymbolTable::~SymbolTable() {
    delete root;
}

// Insert a key value pair in the symbol table
void SymbolTable::insert(string k, UnlimitedRational* v) {
    SymEntry* newNode = new SymEntry(k, v);
    if (root == nullptr) {
        root = newNode;
    } else {
        SymEntry* current = root;
        while (true) {
            if (k < current->key) {
                if (current->left == nullptr) {
                    current->left = newNode;
                    break;
                }
                current = current->left;
            } else if (k > current->key) {
                if (current->right == nullptr) {
                    current->right = newNode;
                    break;
                }
                current = current->right;
            } else { // Key already exists, update the value
                delete current->val;
                current->val = v;
                break;
            }
        }
    }
    size++;
}

// Remove a key (and value) in the symbol table
void SymbolTable::remove(string k) {
    SymEntry* parent = nullptr;
    SymEntry* current = root;
    while (current != nullptr) {
        if (k == current->key) {
            break;
        }
        parent = current;
        if (k < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == nullptr) {
        return; // Key not found
    }

    if (current->left == nullptr && current->right == nullptr) {
        if (parent == nullptr) {
            delete current->val;
            delete current;
            root = nullptr;
        } else if (parent->left == current) {
            parent->left = nullptr;
            delete current->val;
            delete current;
        } else {
            parent->right = nullptr;
            delete current->val;
            delete current;
        }
    } else if (current->left == nullptr || current->right == nullptr) {
        SymEntry* child = (current->left != nullptr) ? current->left : current->right;
        if (parent == nullptr) {
            delete current->val;
            delete current;
            root = child;
        } else if (parent->left == current) {
            parent->left = child;
            delete current->val;
            delete current;
        } else {
            parent->right = child;
            delete current->val;
            delete current;
        }
    } else {
        SymEntry* successorParent = current;
        SymEntry* successor = current->right;
        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }

        current->key = successor->key;
        delete current->val;
        current->val = successor->val;

        if (successorParent->left == successor) {
            successorParent->left = successor->right;
        } else {
            successorParent->right = successor->right;
        }

        delete successor->val;
        delete successor;
    }

    size--;
}

// Find the val corresponding to the key in the symbol table
UnlimitedRational* SymbolTable::search(string k) {
    SymEntry* current = root;
    while (current != nullptr) {
        if (k == current->key) {
            return current->val;
        } else if (k < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return nullptr; // Key not found
}

// Get size
int SymbolTable::get_size() {
    return size;
}

// Get root 
SymEntry* SymbolTable::get_root() {
    return root;
}

// int main(){
//     SymbolTable* gojo = new SymbolTable();
//     gojo->insert("satoru",new UnlimitedRational(new UnlimitedInt(1),new UnlimitedInt(97)));
//     gojo->insert("is",new UnlimitedRational(new UnlimitedInt(2),new UnlimitedInt(97)));
//     gojo->insert("the",new UnlimitedRational(new UnlimitedInt(3),new UnlimitedInt(97)));
//     gojo->insert("peek",new UnlimitedRational(new UnlimitedInt(4),new UnlimitedInt(97)));
//     gojo->insert("alltime",new UnlimitedRational(new UnlimitedInt(5),new UnlimitedInt(97)));
    
//     cout<< gojo->search("alltime")->get_frac_str()<<endl;
//     cout<< gojo->search("peek")->get_frac_str()<<endl;
//     cout<< gojo->search("satoru")->get_frac_str()<<endl;
//     cout<< gojo->search("is")->get_frac_str()<<endl;
//     cout<< gojo->search("the")->get_frac_str()<<endl;
// }