/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"
  //#include <iostream>

//Write your code below this line

Parser::Parser(){
    symtable = new SymbolTable;
    last_deleted = -1;
}

string check (string s) {
	if (s == "+") {
        return "ADD";
    }
    else if (s == "*") {
        return "MUL";
    }
    else if (s == "-") {
        return "SUB";
    }
    else if (s == "/") {
        return "DIV";
    }
    return "";
}

bool isStringDigits(const std::string& str) {
    if (str[0] == '-') {
        for (int i=1; i<str.size(); i++) {
            if (str[i] < '0' || str[i] > '9') 
            return false;
        }
        return true;
    }
    for (char character : str) {
        if (character < '0' || character > '9') {
            return false;
        }
    }
    return true;
}

void Parser::parse(vector<string> expression) {
    vector<ExprTreeNode*> nodeStack;
    
    vector<string> operatorStack;
    int n = expression.size();
    for (int i=2; i<n; i++) {
        if (expression[i] == "(") {
            operatorStack.push_back(expression[i]);
        } else if (expression[i] == ")") {
            while (!operatorStack.empty() && operatorStack.back() != "(") {
                string op = operatorStack.back();
                operatorStack.pop_back();

                ExprTreeNode* rightOperand = nodeStack.back();
                nodeStack.pop_back();

                ExprTreeNode* leftOperand = nodeStack.back();
                nodeStack.pop_back();

                ExprTreeNode* newNode = new ExprTreeNode();
                newNode->type = op;
                newNode->left = leftOperand;
                newNode->right = rightOperand;
                nodeStack.push_back(newNode);
                // cout << newNode->left->type<< " " << newNode->type << " " << newNode->right->type << endl;
            }
            operatorStack.pop_back();
        } else if (check(expression[i]) != "") {
            operatorStack.push_back(check(expression[i]));
        } else if (isStringDigits(expression[i])) {
            ExprTreeNode* newNode = new ExprTreeNode();
            newNode->type = "VAL";
            newNode->num = stoi(expression[i]);
            // cout << newNode->num << endl;
            nodeStack.push_back(newNode);
        } else {
            ExprTreeNode* newNode = new ExprTreeNode();
            newNode->type = "VAR";
            newNode->id = expression[i];
            nodeStack.push_back(newNode);
        }
    }

    while (!operatorStack.empty()) {
        string op = operatorStack.back();
        operatorStack.pop_back();

        ExprTreeNode* rightOperand = nodeStack.back();
        nodeStack.pop_back();

        ExprTreeNode* leftOperand = nodeStack.back();
        nodeStack.pop_back();

        ExprTreeNode* newNode = new ExprTreeNode();
        newNode->type = op;
        newNode->left = leftOperand;
        newNode->right = rightOperand;
        nodeStack.push_back(newNode);
    }
    if (!nodeStack.empty()) {
        ExprTreeNode* root = new ExprTreeNode();
        root->type = "EQUAL";
        ExprTreeNode* rootL = new ExprTreeNode();
        rootL->type = expression[0];
        if (expression[0] == "del") {
            rootL->type = "DEL";
        }
        else if (expression[0] == "ret") {
            rootL->type = "RET";
        }
        else {
            rootL->type = "VAR";
            rootL->id = expression[0];
            //cerr<<"inseting here "<<expression[0]<<endl;
            //symtable->insert(expression[0]);
        }
        root->left = rootL;
        root->right = nodeStack.back();

        expr_trees.push_back(root);
        nodeStack.pop_back();
    }
}

// void del1(ExprTreeNode* node) {
//     if (node == NULL) {
//         return;
//     }
//     del1(node->left);
//     del1(node->right);
//     delete node;
// }

Parser::~Parser(){
    for (int i=0; i<expr_trees.size(); i++) {
        delete expr_trees[i];
    }
}

// void inFix(ExprTreeNode* root) {
//     if (root == NULL) {
//         cout<<"( ";
//     }
//     inFix(root->left);
//     if (root->type == "VAL") {cout << root->num;}
//     else {cout << root->type;}
//     inFix(root->right);
// }

// int main() {
//     Parser* root = new Parser();
//     vector<string> vec = {"(","3","*","(","5","+","2",")",")"};
//     ExprTreeNode* r = new ExprTreeNode();
//     root->parse(vec);
//     r = root->expr_trees[0];
//     inFix(r);
// }
