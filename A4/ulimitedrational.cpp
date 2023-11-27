#include "ulimitedrational.h"
#include <iostream>
using namespace std;

UnlimitedInt* get_gcd(UnlimitedInt* i1, UnlimitedInt* i2) {
    if (i1->to_string() == "0") {return i2;}
    else if (i2->to_string() == "0") {
        return i1;
    }
    else if (i1->to_string() == "1") {
        return i1;
    }
    return get_gcd(i2, UnlimitedInt::mod(i1, i2));
}

UnlimitedRational::UnlimitedRational() {
    p = new UnlimitedInt("0");
    q = new UnlimitedInt("0");
}

UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den) {
    UnlimitedInt* g = get_gcd(num ,den);
    p = UnlimitedInt::div(num, g);
    q = UnlimitedInt::div(den, g);
}

UnlimitedRational::~UnlimitedRational() {
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p() {
    return p;
}

UnlimitedInt* UnlimitedRational::get_q() {
    return q;
}

string UnlimitedRational::get_p_str() {
    return p->to_string();
}

string UnlimitedRational::get_q_str() {
    return q->to_string();
}

string UnlimitedRational::get_frac_str() {
    string a = p->to_string();
    string b = q->to_string();
    return a + "/" + b;
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2) {
    UnlimitedInt* t1 = UnlimitedInt::add(UnlimitedInt::mul(i1->p, i2->q), UnlimitedInt::mul(i2->p, i1->q));
    UnlimitedInt* t2 = UnlimitedInt::mul(i1->q, i2->q);
    UnlimitedRational* t = new UnlimitedRational(t1,t2);
    return t;
}


UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2) {
    UnlimitedInt* t1 = UnlimitedInt::sub(UnlimitedInt::mul(i1->p, i2->q), UnlimitedInt::mul(i2->p, i1->q));
    UnlimitedInt* t2 = UnlimitedInt::mul(i1->q, i2->q);
    UnlimitedRational* t = new UnlimitedRational(t1,t2);
    return t;
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2) {
    UnlimitedInt* t1 = UnlimitedInt::mul(i1->p, i2->p);
    UnlimitedInt* t2 = UnlimitedInt::mul(i1->q, i2->q);
    UnlimitedRational* t = new UnlimitedRational(t1,t2);
    return t;
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2) {
    UnlimitedInt* t1 = UnlimitedInt::mul(i1->p, i2->q);
    UnlimitedInt* t2 = UnlimitedInt::mul(i1->q, i2->p);
    UnlimitedRational* t = new UnlimitedRational(t1,t2);
    return t;
}

// int main(){
//     UnlimitedInt* t1 = new UnlimitedInt("4");
//     UnlimitedInt* t2 = new UnlimitedInt("2");
//     cout<<get_gcd(t1,t2)->to_string()<<endl;
//     UnlimitedRational* t = new UnlimitedRational(t1, t2);
//     cout<<"t is : "<<t->get_frac_str()<<endl;
//     UnlimitedInt* q1 = new UnlimitedInt("3");
//     UnlimitedInt* q2 = new UnlimitedInt("6");
//     UnlimitedRational* q = new UnlimitedRational(q1, q2);
//         cout<<"q is : "<<q->get_frac_str()<<endl;

//     UnlimitedRational* r = UnlimitedRational::mul(t, q);
//     cout << r->get_p_str()<<endl;
//     cout << r->get_q_str()<<endl;
// }