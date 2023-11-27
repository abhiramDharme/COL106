/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line
SymNode::SymNode() {
    key = "";
    height = 1;
    address = -1;
}

SymNode::SymNode(string k) {
    key = k;
    height = 1;
    address = -1;
}

int max1(int a, int b) {
    return (a > b) ? a : b;
}

int High1(SymNode* node) {
    if (node == NULL) {
        return -1;
    }
    return max1(High1(node->left), High1(node->right)) + 1;
}

SymNode* SymNode::LeftLeftRotation() {
    // SymNode* newRoot = left;
    // newRoot->par = par;
    // if (par->left == this) {
    //     par->left = newRoot;
    // }
    // else {
    //     par->right = newRoot;
    // }
    // par = newRoot;
    // left = newRoot->right;
    // newRoot->right = this;
    // if (left != NULL) {
    //     left->par = this;
    // }
    // this->height = High1(this);
    // newRoot->height = High1(newRoot);
    // return newRoot;
    return NULL;
}

SymNode* SymNode::RightRightRotation() {
    // SymNode* newRoot = right;
    // newRoot->par = par;
    // if (par->right == this) {
    //     par->right = newRoot;
    // }
    // else {
    //     par->left = newRoot;
    // }
    // par = newRoot;
    // right = newRoot->left;
    // newRoot->left = this;
    // if (right != NULL) {
    //     right->par = this;
    // }
    // this->height = High1(this);
    // newRoot->height = High1(newRoot);
    // return newRoot;
    return NULL;
}

SymNode* SymNode::LeftRightRotation() {
    // if (left != NULL) {
    //     left = left->RightRightRotation();
    // }
    // return LeftLeftRotation();
    return NULL;
}


SymNode* SymNode::RightLeftRotation() {
    // if (right != NULL) {
    //     right = right->LeftLeftRotation();
    // }
    // return this->RightRightRotation();
    return NULL;
}


SymNode::~SymNode() {
    if (left != NULL) delete left;
    if (right != NULL) delete right;
}

