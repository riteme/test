#include <iostream>
#include <algorithm>

using namespace std;

void ReadBigNumber(string &area){
    cin>>area;

    for (auto &c : area) {
        c-='0';
    }  // foreach in buffer

    std::reverse(area.begin(),area.end());
}

void PrintBigNumber(const string &bigNum){
    string tmp=bigNum;
    std::reverse(tmp.begin(),tmp.end());

    for (auto &c : tmp) {
        c+='0';
    }  // foreach in tmp

    cout<<tmp<<'\n';
}

string Addition(const string &a,const string &b){
    string result;
    // result.reserve(a.size());
    unsigned i=0,j=0;

    char upload=0;
    while (i<a.size() || j<b.size()) {
        char sum;

        if (i>=a.size()) {
            sum=b[j++]+upload;
        }else if(j>=b.size()){
            sum=a[i++]+upload;
        }else{
            sum=a[i++]+b[j++]+upload;
        }

        result+=sum%10;
        upload=sum/10;
    }   // while
    
    if (upload>0) {
        result+=upload;
    }

    return result;
}

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(false);

    string a,b;
    ReadBigNumber(a);
    ReadBigNumber(b);

    PrintBigNumber(Addition(a,b));

    return 0;
}