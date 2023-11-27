/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode() {
    type = "";
    val = nullptr;
    evaluated_value = nullptr;
    id = "";
    left = nullptr;
    right = nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v) {
    type = t;
    val = new UnlimitedRational(new UnlimitedInt(v->to_string()),new UnlimitedInt(1)); //
    evaluated_value = new UnlimitedRational(new UnlimitedInt(v->to_string()),new UnlimitedInt(1));
    id = "";
    left = nullptr;
    right = nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v) {
    type = t;
    val = new UnlimitedRational(new UnlimitedInt(v->get_p()->to_string()),new UnlimitedInt(v->get_q()->to_string()));
    evaluated_value = new UnlimitedRational(new UnlimitedInt(v->get_p()->to_string()),new UnlimitedInt(v->get_q()->to_string()));
    id = nullptr;
    left = nullptr;
    right = nullptr;
}

ExprTreeNode::~ExprTreeNode() {
    delete val;
    delete evaluated_value;
}