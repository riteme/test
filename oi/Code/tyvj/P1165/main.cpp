#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

int GetDigit(const char c){
    switch (c) {
    case '0':return 0;
    case '1':return 1;
    case '2':return 2;
    case '3':return 3;
    case '4':return 4;
    case '5':return 5;
    case '6':return 6;
    case '7':return 7;
    case '8':return 8;
    case '9':return 9;
   }  // switch to c
}
char GetChar(int i){
    switch (i) {
    case 0:return '0';
    case 1:return '1';
    case 2:return '2';
    case 3:return '3';
    case 4:return '4';
    case 5:return '5';
    case 6:return '6';
    case 7:return '7';
    case 8:return '8';
    case 9:return '9';
   }  // switch to c
}

string GetString(const vector<int> &base,const vector<int> &tail){
    string tmp;

    for (auto i : base) {
        tmp+=GetChar(i);
    }  // foreach in vec

    if (tail.size()>0) {
        tmp+='.';
        for (auto i : tail) {
            tmp+=GetChar(i);
        }  // foreach in tail
    }

    return tmp;
}

int main(/*int argc, char *argv[]*/) {
    string baseData;
    vector<int> base;
    vector<int> tail;

    while (cin >> baseData) {
        bool baseOp=true;
        bool recordingTail=false;

        base.clear();
        tail.clear();

        for (auto c : baseData) {
            if (c=='-') {
                baseOp=false;
                continue;
            }else if (c=='.') {
                recordingTail=true;
                continue;
            }

            if (recordingTail) {
                tail.push_back(GetDigit(c));
            }else{
                base.push_back(GetDigit(c));
            }
        }  // foreach in baseData

        while (!tail.empty()&&tail.back()==0) {
            tail.pop_back();
        } // while

        while (base.size()>1&&base.front()==0) {
            base.erase(base.begin());
        } // while

        if (base.size()==1 && base[0]==0 && tail.empty()) {
            cout<<0<<endl;
            continue;
        }

        // if (base.size()==2&&base[0]==1&&base[1]==0&&tail.empty()) {
        //     cout<<GetString(base,tail,baseOp)<<endl;
        // }

        // base * 10 ^ n
        unsigned long long n=0;
        bool nOp=true;

        if(nOp){
            for (unsigned i=base.size();
                 i>1;
                 i--) {
                tail.insert(tail.begin(),base.back());
                base.pop_back();
                n++;
            }  // for
        }else{
            while (base[0]==0) {
                base[0]=tail.front();
                tail.erase(tail.begin());
                n++;
            } // while
        }

        if(!baseOp){
            cout<<'-';
        }

        if (!(base.size()==1&&base[0]==1&&std::all_of(tail.begin(),tail.end(),[](int i){return i==0;})&&n!=0)) {
            cout<<GetString(base,tail);
            if (n!=0) {
                cout<<'*';
            }
        }

        // if(tail.empty()){
        //     cout<<endl;
        //     continue;
        // }

        if (n!=0) {
            cout << "10";

            if (n - (nOp ? 1 : 0) != 0) {
                cout << "^";
                cout << (nOp ? "" : "(-");
                cout << n;
                cout << (nOp ? "" : ")");
            }
        }

        cout << endl;
    }  // while

    return 0;
}  // function main
