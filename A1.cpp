#include <iostream>
#include <vector>
using namespace std;

class SET{
public:
    vector<int> data;
    
    int Size(){
        return data.size();
    }

    int belongTo(int x){
        int i = 0;
        int pass = 0;
        while(i<data.size()){
            if(data[i] == x){
                pass++;
                break;
                return 1;
            }
            i++;
        }
        if(pass==0){return 0;};
        return 1;
    }

    void Insert(int x){
        if(data.size()==0){
            data.push_back(x);
            cout << 1 << endl;
        }
        else if(belongTo(x)){
            cout << data.size() << endl;
        }
        else{
            if(x<data[0]){
                data.insert(data.begin(), x);
                cout << data.size() << endl;
            }
            else if(data[data.size()-1]<x){
                data.push_back(x);
                cout << data.size() << endl;
            }
            else{
                int i = 1;
                while(i<data.size()){
                    if(x<data[i]){
                        break;
                    }
                    i++;
                }
                data.insert(data.begin()+i, x);
                cout << data.size() << endl;
            }
        }
    }

    void Print(){
        if(data.size() == 0){
            cout << endl;
        }
        else{
            int i = 1;
            cout << data[0];
            while(i<data.size()){
                cout << "," << data[i];
                i++;
            }
            cout << endl;
        }
        
    }

    void Delete(int x){
        if(belongTo(x)){
            int i = 0;
            while(i<data.size()){
                if(data[i] == x){
                    break;
                }
                i++;
            }
            vector<int>::iterator it = data.begin() + i;
            data.erase(it);
            cout << data.size() << endl;
        }
        else{
            cout << data.size() << endl;
        }
    }

    void Union(SET vec){
        if(data.size()==0 and vec.data.size()==0){
            cout << 0 << endl;
        }
        else if(data.size()==0){
            data = vec.data;
            cout << data.size() << endl;
        }
        else if(vec.data.size()==0){
            cout << data.size() << endl;
        }
        else{
            vector<int> voc;
            int i = 0;
            int j = 0;
            while(i<data.size() and j<vec.data.size()){
                if(data[i] < vec.data[j]){
                    voc.push_back(data[i]);
                    i++;
                }
                else if(data[i] > vec.data[j]){
                    voc.push_back(vec.data[j]);
                    j++;
                }
                else{
                    voc.push_back(data[i]);
                    i++;
                    j++;
                }
            }
            if(j<vec.data.size()){
                while(j<vec.data.size()){
                    voc.push_back(vec.data[j]);
                    j++;
                }
            }
            else{
                while(i<data.size()){
                    voc.push_back(data[i]);
                    i++;
                }
            }
            data = voc;
            voc.clear();
            cout << data.size() << endl;
        }    
    }

    void Intersection(SET vec){
        vector<int> voc;
        int i = 0;
        int j = 0;
        while(i<data.size() and j<vec.data.size()){
            if(data[i] == vec.data[j]){
                voc.push_back(data[i]);
                i++;
                j++;
            }
            else if(data[i] < vec.data[j]){
                i++;
            }
            else{
                j++;
            }
        }
        data = voc;
        voc.clear();
        cout << data.size() << endl;
    }

    void Difference(SET vec){
        if(data.size()==0){
            cout << 0 << endl;
        }
        else if(vec.data.size()==0){
            cout << data.size() << endl;
        }
        else{
            vector<int> voc;
            int i = 0;
            int j = 0;
            int n = vec.data.size();
            while(i<data.size()){
                if(j>=n and data[i]>vec.data[n-1]){
                    voc.push_back(data[i]);
                    i++;
                }
                else if(data[i] == vec.data[j]){
                    i++;
                    j++;
                }
                else if(data[i] < vec.data[j]){
                    voc.push_back(data[i]);
                    i++;
                }
                else if(data[i] > vec.data[j]){
                    j++;
                }
            }
            data = voc;
            voc.clear();
            cout << data.size() << endl;
        }
    }

    void symmetricDifference(SET vec){
        if(data.size()==0){
            data = vec.data;
            cout << data.size() << endl;
        }
        else if(vec.data.size()==0){
            cout << data.size() << endl;
        }
        else{
            vector<int> voc;
            int i = 0;
            int j = 0;
            int n = vec.data.size();
            int m = data.size();
            while((i<data.size()) or (j<n)){
                if(i>=m and data[m-1]<vec.data[j]){
                    voc.push_back(vec.data[j]);
                    j++;
                }
                else if(j>=n and data[i]>vec.data[n-1]){
                    voc.push_back(data[i]);
                    i++;
                }
                else if(data[i] == vec.data[j]){
                    i++;
                    j++;
                }
                else if(data[i] < vec.data[j]){
                    voc.push_back(data[i]);
                    i++;
                }
                else if(data[i] > vec.data[j]){
                    voc.push_back(vec.data[j]);
                    j++;
                }
            }
            data = voc;
            voc.clear();
            cout << data.size() << endl;
        }
    }
};

int main(){
    vector<SET> set;
    long int x;
    while(cin >> x){
        long int y,z;
        if(x==1){
            cin >> y;
            cin >> z;
            if(y<set.size()){
                set[y].Insert(z);
            }
            else{
                SET vec;
                set.push_back(vec);
                set[y].Insert(z);
            }
        }
        else if(x==2){
            cin >> y;
            cin >> z;
            if(y<set.size()){
                set[y].Delete(z);
            }
            else{
                cout << -1 << endl;
            }
            
        }
        else if(x==3){
            cin >> y;
            cin >> z;
            if(y>=set.size()){
                cout << -1 << endl;
            }
            else{
                cout << set[y].belongTo(z) << endl;
            }
        }
        else if(x==4){
            cin >> y;
            cin >> z;
            if(y<set.size() and z<set.size()){
                set[y].Union(set[z]);
            }
            else if(y<set.size() and z>=set.size()){
                SET vec;
                set.push_back(vec);
                cout << set[y].Size() << endl;
            }
            else if(y>=set.size() and z<set.size()){
                SET vec;
                set.push_back(vec);
                cout << 0 << endl;
            }
            else{
                SET vec1,vec2;
                set.push_back(vec1);
                set.push_back(vec2);
                cout << 0 << endl;
            }
        }
        else if(x==5){
            cin >> y;
            cin >> z;
            if(y<set.size() and z<set.size()){
                set[y].Intersection(set[z]);
            }
            else if(y<set.size() and z>=set.size()){
                SET vec;
                set.push_back(vec);
                cout << set[y].Size() << endl;
            }
            else if(y>=set.size() and z<set.size()){
                SET vec;
                set.push_back(vec);
                cout << 0 << endl;
            }
            else{
                SET vec1,vec2;
                set.push_back(vec1);
                set.push_back(vec2);
                cout << 0 << endl;
            }
        }
        else if(x==6){
            cin >> y;
            if(y<set.size()){
                cout << set[y].Size() << endl;
            }
            else{
                SET vec;
                set.push_back(vec);
                cout << 0 << endl;
            }
            
        }
        else if(x==7){
            cin >> y;
            cin >> z;
            if(y<set.size() and z<set.size()){
                set[y].Difference(set[z]);
            }
            else if(y<set.size() and z>set.size()){
                SET vec;
                set.push_back(vec);
                cout << set[y].Size() << endl;
            }
            else if(y>set.size() and z<set.size()){
                SET vec;
                set.push_back(vec);
                cout << 0 << endl;
            }
            else{
                SET vec1;
                SET vec2;
                set.push_back(vec1);
                set.push_back(vec2);
                cout << 0 << endl;
            }
        }
        else if(x==8){
            cin >> y;
            cin >> z;
            if(y<set.size() and z<set.size()){
                set[y].symmetricDifference(set[z]);
            }
            else if(y<set.size() and z>=set.size()){
                SET vec;
                set.push_back(vec);
                cout << set[y].Size() << endl;
            }
            else if(y>=set.size() and z<set.size()){
                SET vec;
                set.push_back(vec);
                cout << 0 << endl;
            }
            else{
                SET vec1,vec2;
                set.push_back(vec1);
                set.push_back(vec2);
                cout << 0 << endl;
            }
        }
        else if(x==9){
            cin >> y;
            if(y<set.size()){
                set[y].Print();
            }
            else{
                SET vec;
                set.push_back(vec);
                cout << endl;
            }
        }
    }
}