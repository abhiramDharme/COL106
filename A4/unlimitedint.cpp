/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
#include <iostream>
using namespace std;

UnlimitedInt::UnlimitedInt(){
    size = 1;
    sign = 0;
    capacity = size;
    unlimited_int = new int[1];
    unlimited_int[0] = 0;
}

UnlimitedInt::UnlimitedInt(string s){
    int n1 = s.size();
    int startIndex = 0;
    if (s[0] == '-') {
        startIndex++;
        while (startIndex < n1 && s[startIndex] == '0') {
            startIndex++;
        }
        size = n1 - startIndex;
        sign = -1;
    } else {
         while (startIndex < n1 && s[startIndex] == '0') {
            startIndex++;
        }
        size = n1 - startIndex;
        sign = 1;
    }
    if (size == 0) {
        sign = 0;
        size++;
        capacity = size;
        unlimited_int = new int[size];
        unlimited_int[0] = 0;
    } else {
        capacity = size;
        unlimited_int = new int[size];
        for (int i = startIndex; i < n1; i++) {
            unlimited_int[i-startIndex] = s[i] - '0';
        }
    }
}

UnlimitedInt::UnlimitedInt(int n){
    string sa = std::to_string(n);
    int n1 = sa.size();
    int startIndex = 0;
    if (sa[0] == '-') {
        startIndex++;
        while (startIndex < n1 && sa[startIndex] == '0') {
            startIndex++;
        }
        size = n1 - startIndex;
        sign = -1;
    } else {
         while (startIndex < n1 && sa[startIndex] == '0') {
            startIndex++;
        }
        size = n1 - startIndex;
        sign = 1;
    }
    if (size == 0) {
        sign = 0;
        size++;
        capacity = size;
        unlimited_int = new int[size];
        unlimited_int[0] = 0;
    } else {
        capacity = size;
        unlimited_int = new int[size];
        for (int i = startIndex; i < n1; i++) {
            unlimited_int[i-startIndex] = sa[i] - '0';
        }
    }
}

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz) {
    unlimited_int = ulimited_int;
    capacity = cap;
    sign = sgn;
    size = sz;
}

UnlimitedInt::~UnlimitedInt() {
    delete[] unlimited_int;
}

int UnlimitedInt::get_capacity(){ return capacity;}

int UnlimitedInt::get_size(){ return size;}

int UnlimitedInt::get_sign(){ return sign;}

int* UnlimitedInt::get_array(){ return unlimited_int;}

string UnlimitedInt::to_string(){
    string s = "";
    if (sign == -1) {
        s += "-";
    }
    for(int i=0; i<size; i++){
        s += std::to_string(unlimited_int[i]);
    }
    return s;
}

UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2) {
    if(i1->get_sign()==0){
        return new UnlimitedInt(i2->to_string());
    }
     if(i2->get_sign()==0){
        return new UnlimitedInt(i1->to_string());
    }
    if (i1->sign != i2->sign) {
        UnlimitedInt* temp = new UnlimitedInt(i2->get_array(), i2->capacity, -1*i2->sign, i2->size);
        UnlimitedInt* i = sub(i1, temp);
        delete temp;
        return i;
    }
    int n1 = i1->size;
    int n2 = i2->size;
    int maxSize = max(n1, n2);
    int* result = new int[maxSize + 1];
    for (int i = 0; i <= maxSize; i++) {
        result[i] = 0; 
    }
    int carry = 0;
    for (int i = 0; i < maxSize; i++) {
        int digit1 = (i < n1) ? i1->unlimited_int[n1 - 1 - i] : 0;
        int digit2 = (i < n2) ? i2->unlimited_int[n2 - 1 - i] : 0;
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result[maxSize - i] = sum % 10;
    }
    if (carry > 0) {
        result[0] = carry;
    } else {
        for (int i = 0; i < maxSize; i++) {
            result[i] = result[i + 1];
        }
        maxSize--;
    }
    UnlimitedInt* sum = new UnlimitedInt();
    sum->size = maxSize + 1;
    sum->sign = (i1->sign == i2->sign) ? i1->sign : 0;
    sum->unlimited_int = new int[maxSize + 1];
    for (int i = 0; i <= maxSize; i++) {
        sum->unlimited_int[i] = result[i];
    }
    delete[] result;
    return sum;
}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2) {
    if (i1->sign != i2->sign) {
        UnlimitedInt* temp = new UnlimitedInt(i2->get_array(), i2->capacity, -1*i2->sign, i2->size);
        UnlimitedInt* i = add(i1, temp);
        delete temp;
        return i;
    }
    int n1 = i1->size;
    int n2 = i2->size;
    int maxSize = max(n1, n2);
    int* result = new int[maxSize];
    for (int i = 0; i <= maxSize; i++) {
        result[i] = 0; 
    }
    int borrow = 0;
    for (int i = 0; i < maxSize; i++) {
        int digit1 = (i < n1) ? i1->unlimited_int[n1 - 1 - i] : 0;
        int digit2 = (i < n2) ? i2->unlimited_int[n2 - 1 - i] : 0;
        int difference = digit1 - digit2 - borrow;
        if (difference < 0) {
            difference += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[maxSize - 1 - i] = difference;
    }
    int startIndex = 0;
    while (startIndex < maxSize - 1 && result[startIndex] == 0) {
        startIndex++;
    }
    UnlimitedInt* difference = new UnlimitedInt();
    difference->size = maxSize - startIndex;
    difference->sign = (i1->sign == i2->sign) ? i1->sign : 0;
    difference->unlimited_int = new int[difference->size];
    // memcpy(difference->unlimited_int, result + startIndex, sizeof(int) * difference->size);
    for (int i = startIndex; i<maxSize; i++) {
        difference->unlimited_int[i-startIndex] = result[i];
    }
    delete[] result;
    return difference;
}


UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2) {
    int n1 = i1->size;
    int n2 = i2->size;
    if (i1->sign == 0 || i2->sign == 0) {
        UnlimitedInt* result = new UnlimitedInt();
        return result;
    }
    int resultSign = (i1->sign == i2->sign) ? 1 : -1;
    int resultSize = n1 + n2;
    int* resultArray = new int[resultSize];
    for (int i = 0; i <= resultSize; i++) {
        resultArray[i] = 0; 
    }
    for (int i = n1 - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = n2 - 1; j >= 0; j--) {
            int product = i1->unlimited_int[i] * i2->unlimited_int[j] + resultArray[i + j + 1] + carry;
            carry = product / 10;
            resultArray[i + j + 1] = product % 10;
        }
        resultArray[i] += carry;
    }
    int startIndex = 0;
    while (startIndex < resultSize - 1 && resultArray[startIndex] == 0) {
        startIndex++;
    }
    UnlimitedInt* product = new UnlimitedInt();
    product->size = resultSize - startIndex;
    product->sign = resultSign;
    product->unlimited_int = new int[product->size];
    // memcpy(product->unlimited_int, resultArray + startIndex, sizeof(int) * product->size);
    for (int i = startIndex; i<resultSize; i++) {
        product->unlimited_int[i-startIndex] = resultArray[i];
    }
    delete[] resultArray;
    return product;
}

UnlimitedInt* ek = new UnlimitedInt("1");
UnlimitedInt* daha = new UnlimitedInt("10");

int compare(UnlimitedInt* i1, UnlimitedInt* i2) {
    int g = (i1->get_size() > i2->get_size()) ? 1 : ( (i1->get_size() < i2->get_size()) ? -1 : 0 );
    if (g == 0) {
        for (int i = 0; i < i1->get_size(); i++){
            if (i1->get_array()[i] > i2->get_array()[i]) {
                return 1;
            }
            else if (i1->get_array()[i] < i2->get_array()[i]) {
                return -1;
            }
        }
    }
    return g;
}

UnlimitedInt* fastPower(UnlimitedInt* index, int power, UnlimitedInt* aux) {
    if (power == 0) {return aux;}
    while (power != 0) {
        if (power%2 == 0) {
            index = UnlimitedInt::mul(index, index);
            power /= 2;
        }
        else {
            aux = UnlimitedInt::mul(aux, index);
            power -= 1;
        }
    }
    return aux;
}

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2) {
    if (i1->sign*i2->sign == 0 || ((compare(i1, i2) == -1) && (i1->sign == i2->sign))) {
        UnlimitedInt* result = new UnlimitedInt("0");
        return result;
    }
    if (compare(i1, i2) == -1 && i1->sign != i2->sign) {
        UnlimitedInt* result = new UnlimitedInt("-1");
        return result;
    }
    if (compare(i1, i2) == 0){
        if (i1->sign == i2->sign) {
            UnlimitedInt* result = new UnlimitedInt("1");
            return result;
        }
        else {
            UnlimitedInt* result = new UnlimitedInt("-1");
            return result;
        }
    }
    
    


    int resultSign = (i1->sign == i2->sign) ? 1 : -1;
    UnlimitedInt* result = new UnlimitedInt("0");
    UnlimitedInt * m1 = new UnlimitedInt(-1);
    UnlimitedInt* remainder = i1;
    UnlimitedInt* divisor = i2;

    if(i1->get_sign()==-1){
        *remainder = *UnlimitedInt::mul(i1,m1);
    }
    if(i2->get_sign()==-1){
        *divisor = *UnlimitedInt::mul(i2,m1);
    }

    int param = 0;
    UnlimitedInt * divisorC = new UnlimitedInt(divisor->get_array(),divisor->get_capacity(),divisor->get_sign(),divisor->get_size());
    while (compare(remainder, divisorC) != -1) {
        param++;
        *divisorC = *UnlimitedInt::mul(divisorC, daha);
    }
    // cout << divisor->to_string() << endl;
    // cout << divisorC->to_string() << endl;
    param--;
    //*divisorC = *UnlimitedInt::mul(divisor, fastPower(daha, param, ek));
    while (param >= 0) {
        UnlimitedInt * factor = fastPower(daha, param, ek);
        *divisorC = *UnlimitedInt::mul(divisor, factor);


        while (compare(remainder, divisorC) != -1) {
            remainder = sub(remainder, divisorC);

            UnlimitedInt * temp = result;
            result = nullptr;
            result = UnlimitedInt::add(temp,factor);
            temp = nullptr;
            
        }     
        

        param--;
    }

    if (remainder->sign == 0) {
        result->sign = resultSign;
        return result;
    }
    if (resultSign == -1) {
        result = add(result, ek);
    }
    result->sign = resultSign;
    return result;
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2) {
    UnlimitedInt* t = div(i1, i2);
    UnlimitedInt* result = sub(i1, mul(i2, t));
    return result;
}


// int main(){
//     UnlimitedInt* t1 = new UnlimitedInt("7000");
//     UnlimitedInt* t2 = new UnlimitedInt("0");
//     UnlimitedInt* t3 = new UnlimitedInt("51");
//     UnlimitedInt* t4 = new UnlimitedInt(134);
//     UnlimitedInt* t = UnlimitedInt::mod(t4, t3);

//     cout<<"t1 is :"<<t1->to_string()<<endl;
//     cout<<"t2 is :"<<t2->to_string()<<endl;
//     cout<<"t3 is :"<<t3->to_string()<<endl;
//     cout<<"t4 is :"<<t4->to_string()<<endl;
//     cout << t->to_string() << endl;
// }
