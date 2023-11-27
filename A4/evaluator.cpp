#include "evaluator.h"

Evaluator::Evaluator() {

}

Evaluator::~Evaluator(){
	int n = expr_trees.size();
	for (int i = 0; i < n; i++) {
		delete expr_trees[i];
	}
	delete symtable;
}

string op(string s) {
    if (s == "+") {
        return "ADD";
    } else if (s == "*") {
        return "MUL";
    } else if (s == "-") {
        return "SUB";
    } else if (s == "/") {
        return "DIV";
    } else if (s == "%") {
        return "MOD";
    }
    return "";
}

ExprTreeNode* recur(vector<string> code, int& i, int n, UnlimitedInt* den) {
    if (i >= n) {
        return nullptr;
    }

    // Create a new node for the current operand or operator
    ExprTreeNode* node = new ExprTreeNode();
    
    if (code[i] == "(") {
        i++; 
        node->left = recur(code, i, n, den);  // Recursively parse the left subexpression
        i++;  // Move past the operator
        node->type = op(code[i]);  // Set the operator type
        i++;  // Move past the operator
        node->right = recur(code, i, n, den);  // Recursively parse the right subexpression
        i++;  // Move past the ")"
    } else {
        // Handle variables or values
        node->left = new ExprTreeNode();
        node->left->type = "VAR";
        node->left->id = code[i];
        i++;  // Move past the variable

        if (i < n && (code[i] == "+" || code[i] == "*" || code[i] == "-" || code[i] == "/" || code[i] == "%")) {
            node->type = op(code[i]);  // Set the operator type
            i++;  // Move past the operator
            node->right = recur(code, i, n, den);  // Recursively parse the right operand
        } else {
            // If there's no operator, set the type to "VAL"
            node->type = "VAL";

            // Create an UnlimitedRational for the value
            UnlimitedInt* num = new UnlimitedInt(code[i]);
            node->right = new ExprTreeNode("VAL", new UnlimitedRational(num, den));
            delete num; 
            i++;  // Move past the value
        }
    }

    return node;
}

void Evaluator::parse(vector<string> code) {
    int i = 0;  // Start from the beginning of the code
    UnlimitedInt* den = new UnlimitedInt("1");  // Initialize denominator
    ExprTreeNode* root = recur(code, i, code.size(), den);
    expr_trees.push_back(root);
    delete den;
}

void Evaluator::eval(){
	
}






// /* Do NOT add/remove any includes statements from this header file */
// /* unless EXPLICTLY clarified on Piazza. */
// #include "evaluator.h"
// #define len(v) (int)v.size() 
// #define pb push_back
// using namespace std;


// Evaluator::Evaluator() {
// 	symtable = new SymbolTable();
// };

// void del(ExprTreeNode* root) {
// 	if(root != nullptr){
// 		if(root->left != nullptr) {
//             del(root->left);
//         }
// 		if (root->right != nullptr) {
//             del(root->right);
//         }
//         delete root;
// 	}
// };

// Evaluator::~Evaluator() {
// 	for (int i = 0; i < len(expr_trees); i++) {
//         del(expr_trees[i]);
//     }
// 	delete symtable;
// };

// bool check (string s) {
// 	if(s == "+" || s == "-" || s == "/" || s == "*" || s == "%") {
//         return true;
//     }
//     return false;
// }

// void Evaluator::parse (vector<string> code) {
// 	vector<ExprTreeNode*> ops;
// 	vector<ExprTreeNode*> vals; 
// 	vector<string> s = code;
// 	UnlimitedInt* zer = new UnlimitedInt("0"); 
// 	UnlimitedInt* one = new UnlimitedInt("1");
// 	UnlimitedRational* nul = new UnlimitedRational(zer,one);
// 	for ( int i = 2; i < len(code); i++) {
// 		if (s[i] == "(") {
// 			continue;
// 		}
// 		else if(s[i] == ")") {
// 			if (len(ops) > 0) {
// 				ExprTreeNode* root = ops[len(ops)-1]; 
// 				ExprTreeNode* right = vals[len(vals)-1];
// 				ExprTreeNode* left = vals[len(vals)-2];
// 				ops.erase(ops.begin() + (len(ops)-1));
// 				vals.erase(vals.begin() + (len(vals)-1));
// 				vals.erase(vals.begin() + (len(vals)-1));
// 				root->left = left;
// 				root->right = right;
// 				vals.pb(root); 
// 			}
// 		}
// 		else if (check(s[i])) {
// 			string exp;
// 			if(s[i]=="+") exp = "ADD";
// 			else if(s[i]=="-") exp = "SUB";
// 			else if(s[i]=="/") exp = "DIV";
// 			else if(s[i]=="*") exp = "MUL";
// 			ExprTreeNode* newnode = new ExprTreeNode(exp,nul); 
// 			ops.pb(newnode);
// 		}
// 		else{
// 			bool var = false;
// 			for (int j = 0; j < len(s[i]); j++) if(!((s[i][j]-'0') >= 0 and (s[i][j]-'0') <= 9)) var = true; 
// 			if (var) {
// 				UnlimitedRational* x = symtable->search(s[i]);
// 				ExprTreeNode* newnode = new ExprTreeNode("VAL",x); 
// 				newnode->type = "VAR";
// 				newnode->id = s[i];
// 				vals.pb(newnode);
// 			}
// 			else{
// 				UnlimitedInt* Int = new UnlimitedInt(s[i]);
// 				ExprTreeNode* newnode = new ExprTreeNode("VAL",Int); 
// 				vals.pb(newnode);
// 			}
// 		}
// 	}
// 	ExprTreeNode* root = new ExprTreeNode("EQUALS",nul); 
// 	root->right = vals[0]; 
// 	ExprTreeNode* newnode = new ExprTreeNode(s[0],nul); 
// 	newnode->type = "VAR";
// 	root->left = newnode;
// 	expr_trees.pb(root);
// };

// void postorder (ExprTreeNode* rooti) {
// 	if(rooti->left != nullptr) postorder(rooti->left);
// 	if(rooti->right != nullptr) postorder(rooti->right);
// 	if(rooti->type != "VAL"){
// 		if(rooti->type == "ADD") rooti->evaluated_value = UnlimitedRational().add((rooti->left)->evaluated_value,(rooti->right)->evaluated_value);
// 		else if(rooti->type == "SUB") rooti->evaluated_value = UnlimitedRational().sub((rooti->left)->evaluated_value,(rooti->right)->evaluated_value);
// 		else if(rooti->type == "MUL") rooti->evaluated_value = UnlimitedRational().mul((rooti->left)->evaluated_value,(rooti->right)->evaluated_value);
// 		else if(rooti->type == "DIV") rooti->evaluated_value = UnlimitedRational().div((rooti->left)->evaluated_value,(rooti->right)->evaluated_value);
// 	}
// 	return;
// };

// void Evaluator::eval() {
// 	ExprTreeNode* root = expr_trees[len(expr_trees)-1];
// 	ExprTreeNode* rt = root->right;
// 	postorder(rt);
// 	UnlimitedRational* newrt = new UnlimitedRational(rt->evaluated_value->get_p(),rt->evaluated_value->get_q());
// 	symtable->insert((root->left)->id,newrt);
// 	return;
// };