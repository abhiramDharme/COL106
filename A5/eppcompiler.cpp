/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
//#include <iostream>
//Write your code below this line

EPPCompiler::EPPCompiler(){
    targ = Parser();
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    targ = Parser();
    output_file = out_file;
    for (int i=0; i<mem_limit; i++) {
        mem_loc.push_back(i);
        least_mem_loc.push_heap(i);
    }
}

void EPPCompiler::write_to_file(vector<string> commands){
    ofstream file;
    file.open(output_file, ios::out);
    for (int i=0; i<commands.size(); i++) {
        file << commands[i] << endl;
    }
    file.close();
}

bool check7 (string s) {
    if (s == "ADD" || s == "MUL" || s == "DIV" || s == "SUB") {
        //cout << "root->type True" << endl; 
        return true;
    }
    return false;
}

void reverse(ExprTreeNode* root, SymbolTable* symtable, vector<string> &vec, MinHeap &least) {
    if (root->type == "VAR") {
        int n = symtable->search(root->id);
        //cout<<root->id<<" "<<n<<endl;
        vec.push_back("PUSH mem[" + to_string(n) + "]");
    } else if (check7(root->type)) {
        //cout<<"check"<<endl;
        reverse(root->right, symtable, vec, least);
        reverse(root->left, symtable, vec, least);
        vec.push_back(root->type);
    } else {
        vec.push_back("PUSH " + to_string(root->num));
    }
    return;
} 

vector<string> EPPCompiler::generate_targ_commands(){
    vector<string> vec;
    ExprTreeNode* node = targ.expr_trees.back();
    // cout << node->left->type << endl;
    if (node->left->type == "DEL") {
        //cout<<"reach delete" << endl;
        int n = targ.symtable->search(node->right->id);
        targ.symtable->remove(node->right->id);
        vec.push_back("DEL = mem[" + to_string(n) + "]");
        least_mem_loc.push_heap(n);
        return vec;
    }
    reverse(node->right, targ.symtable, vec, least_mem_loc);
    if (node->left->type == "RET") {
        //cout<<"reach return" << endl;
        vec.push_back("RET = POP");
        return vec;
    } else {
        //cout<<"reach elseChiCondition" << endl;
        targ.symtable->insert(node->left->id);
        int n = targ.symtable->search(node->left->id);
        if (n == -2 || n == -1) {
			//cout<<"epp "<<node->left->id<<endl;
            int m = least_mem_loc.get_min();
			targ.symtable->assign_address(node->left->id, m);
            least_mem_loc.pop();
            vec.push_back("mem[" + to_string(m) + "] = POP");
            return vec;
        }
        //cout<<"ithe aahe"<<endl;
        vec.push_back("mem[" + to_string(n) + "] = POP");
        return vec;
    }
}

void EPPCompiler::compile(vector<vector<string>> code){
    vector<string> vec;
    for (int i=0; i<code.size(); i++) {
        targ.parse(code[i]);
        vector<string> com = generate_targ_commands();
        // for (int j=0; j<com.size(); j++) {
        //     cout << com[j] << endl;
        // }
        for(int i=0;i<com.size();i++){
			vec.push_back(com[i]);
        }
    }
    write_to_file(vec);
}

EPPCompiler::~EPPCompiler(){

}

//int main() {
    //EPPCompiler e("ans.txt", 10);
    //vector<string> vec1 = {"a", ":=", "(", "(", "3", "+", "5", ")", "*", "7", ")"};
    //vector<vector<string>> vac;
    //vector<string> vec2 = {"b", ":=", "(", "a", "+", "5", ")"};
    //vac.push_back(vec1);
    //vac.push_back(vec2);
    //vector<string> vec3 = {"ret", ":=", "(", "a", "*", "b", ")"};
    //vac.push_back(vec3);
    //e.compile(vac);
//}
