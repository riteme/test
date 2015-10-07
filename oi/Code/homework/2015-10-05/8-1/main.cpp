#include <cmath>
#include <cctype>
#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

string ONE;
string ZERO;

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

string GetBigNumber(const string &bigNum){
    string number;

    for(int i=bigNum.size()-1;i>=0;i--){
        number+=bigNum[i]+'0';
    }

    return number;
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
    }else if (a==b) {
        return false;
    }else{
        for(int i=a.size()-1;i>=0;i--){
            if (a[i]<b[i]) {
                return true;
            }else if (a[i]>b[i]) {
                return false;
            }
        }
    }

    return false;
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

    if (a==b) {
        if (getOp!=NULL) {
            *getOp=true;
        }

        return ZERO;
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

    while (Less(current,tmp) || current==tmp) {
        tmp=Subtraction(tmp,current);

        outCnt=Addition(outCnt,ONE);
    }   // while

    outRemain=tmp;
}

string Division(string &a,string &b,int m){
    if (b==ZERO){
        return string("");
    }

    if (a==ZERO) {
        return ZERO;
    }

    if (b==ONE) {
        return MultiplyWithTen(a,m);
    }

    string result;

    bool isCompleteDivided=false;
    string tmp=MultiplyWithTen(a,1);
    int cnt=0;
    while (cnt<m) {
        int offest=0;

        string tmpres;

        while (Less(tmp,b)) {
            tmp=MultiplyWithTen(tmp,1);
            tmpres+='\0';
            offest++;
        }   // while
        
        string base,tail;
        Module(tmp,b,base,tail);

        string newn=base+tmpres;
        std::reverse(newn.begin(),newn.end());

        result+=newn;

        tmp=MultiplyWithTen(tail,1);

        cnt+=offest+1;

        if (tail==ZERO) {
            isCompleteDivided=true;
            break;
        }
    }   // while

    // std::reverse(result.begin(),result.end());

    if (m-cnt<0) {
        result=result.substr(0,m);
    }else{
        result= MultiplyWithTen(result,m-cnt);
    }

    if (!isCompleteDivided) {
        std::reverse(result.begin(),result.end());
    }

    return result;
}

void PrintBigNumber(const string &bigNum){
    for(int i=bigNum.size()-1;i>=0;i--){
        printf("%c",bigNum[i]+'0');
    }
    printf("\n");
}

int main() {
    freopen("data.in","r",stdin);

    ONE+='\1';
    ZERO+='\0';

    // const int EXPAND_SIZE=10;

    // int m;
    // scanf("%d",&m);
    // m+=EXPAND_SIZE;

    // string sum=MultiplyWithTen(ONE,m);
    // string step=ONE;

    // for(string i=ONE; ;i=Addition(i,ONE)){
    // 	step=Multiply(step,i);

    //     string div=Division(ONE,step,m);
    //     Shrink(div);

    //     if (div==ZERO) {
    //         break;
    //     }

    //     sum=Addition(sum,div);
    // }

    // string result=GetBigNumber(sum);

    // printf("%c.%s\n", result[0], result.substr(1,m-EXPAND_SIZE).c_str());

    string n1,n2;
    ReadBigNumber(n1);
    ReadBigNumber(n2);

    // string base,tail;
    // Module(n1,n2,base,tail);
    string result=Division(n1,n2,16);

    PrintBigNumber(result);

    return 0;
}  // function main
