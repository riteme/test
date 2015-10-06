#include <cmath>
#include <cctype>
#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

string ONE={'\1'};
string ZERO={'\0'};

void ReadBigNumber(string &area){
    char tmp;

    while (true) {
        tmp=getchar();

        if (isdigit(tmp)) {
            area+=tmp-'0';
        }else{
            std::reverse(area.begin(),area.end());
            break;
        }
    }   // while
}

void PrintBigNumber(const string &bigNum){
    for(int i=bigNum.size()-1;i>=0;i--){
        printf("%c",bigNum[i]+'0');
    }
    printf("\n");
}

void Shrink(string &bigNum){
    int newSize=bigNum.size()-1;

    for(;newSize>=0;newSize--){
        if (bigNum[newSize]!=0) {
            break;
        }
    }

    bigNum.resize(newSize+1);

    if (bigNum.size()==0) {
        bigNum.resize(1);
    }
}

bool Less(const string &a,const string &b){
    if (a.size()<b.size()) {
        return true;
    }else if(a.size()>b.size()){
        return false;
    }else{
        for(int i=a.size()-1;i>=0;i--){
            if (a[i]>b[i]) {
                return false;
            }
        }
    }

    return true;
}

bool LessWithOperator(const string &a,bool aOp,const string &b,bool bOp){
    if (aOp==true && bOp==false) {
        return false;
    }else if (aOp==false && bOp==true) {
        return true;
    }else if (aOp==true && bOp==true) {
        return Less(a,b);
    }else{
        return Less(b,a);
    }
}

string Addition(const string &a,const string &b){
    string result;

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

string Subtraction(string &a,string &b,bool *getOp=NULL){
    if (Less(a,b)) {
        if (getOp!=NULL) {
            *getOp=false;
        }

        return Subtraction(b,a);
    }else{
        if (getOp!=NULL) {
            *getOp=true;
        }
    }

    string result;
    unsigned i=0,j=0;

    int upload=0;
    while (i<a.size() || j<b.size()) {
        int sum;

        if (i>=a.size()) {
            sum=int(b[j++])+upload;
        }else if(j>=b.size()){
            sum=int(a[i++])+upload;
        }else{
            sum=int(a[i++])-int(b[j++])+upload;
        }

        result+=(10-(-sum%10))%10;
        
        if (sum<0) {
            upload=-1;
        }else{
            upload=0;
        }
    }   // while
    
    if (upload>0) {
        result+=upload;
    }

    Shrink(result);

    return result;
}

string Multiply(const string &bigNum,char n){
    string result;

    char upload=0;
    for(unsigned i=0;i<bigNum.size();i++){
        char sum=bigNum[i]*n+upload;

        result+=sum%10;
        upload=sum/10;
    }

    if (upload>0) {
        result+=upload;
    }

    Shrink(result);

    return result;
}

string MultiplyWithTen(const string &bigNum,int n){
    if (n==0) {
        return bigNum;
    }

    string result=bigNum;

    unsigned upBound=result.size();

    result.resize(result.size()+n);

    for(int i=upBound-1;i>=0;i--){
        result[i+n]=result[i];
    }

    for(unsigned i=0;i<n;i++){
        result[i]=0;
    }

    return result;
}

string Multiply(const string &a,const string &b){
    string result;
    // result.reserve(a.size());

    string mult;
    for(unsigned i=0;i<a.size();i++){
        mult = Multiply(b,a[i]);
        mult=MultiplyWithTen(mult,i);
        result=Addition(result,mult);
    }

    Shrink(result);

    return result;
}

string StepMultiply(const string &bigNum){
    string result=ONE;
    string current=ONE;

    string upBound=Addition(bigNum,ONE);

    result.reserve(10000);

    for(;current!=upBound;current=Addition(current,ONE)){
        result=Multiply(result,current);
    }

    return result;
}

void Module(string &target,string &current,string &outCnt,string &outRemain){
    if (Less(target,current)) {
        outCnt=ZERO;
        outRemain=target;
    }

    outCnt=ZERO;

    string tmp=target;

    bool op=true;

    while (op==true) {
        tmp=Subtraction(tmp,current,&op);

        if (op==true) {
            outCnt=Addition(outCnt,ONE);
        }
    }   // while

    outRemain=Subtraction(current,tmp);
}

string Division(string &a,string &b){
    if (b==ZERO){
        return string("");
    }

    if (a==ZERO) {
        return ZERO;
    }


}

int main() {
    string m,n;
    int p;

    ReadBigNumber(m);
    ReadBigNumber(n);
    // scanf("%d",&p);

    // PrintBigNumber(DivisionWithOne(m,p));
    string base,tail;
    Module(m,n,base,tail);
    PrintBigNumber(base);
    PrintBigNumber(tail);
    // bool op;
    // PrintBigNumber(Subtraction(m,n,&op));
    // printf("%d\n", op);

    return 0;
}  // function main
