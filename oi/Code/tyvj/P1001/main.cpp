#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define loop(n) for(int __loop_count__=1;__loop_count__<=(n);__loop_count__++)

typedef long long Number;

bool IsPrime(Number n){
    if (n<2) {
        return false;
    }

    Number upBound=std::sqrt(n);

    for (Number i=2;
         i<=upBound;
         i++) {
        if (n%i==0) {
            return false;
        }
    }  // for

    return true;
}

Number Rank(int k,const vector<Number> &vec){
    if (k>0) {
        return vec[k-1];
    }else{
        return vec[vec.size()+k];  // k为负数
    }
}

int main(Number argc, char *argv[]) {
    ios::sync_with_stdio(false);

    Number n,k;
    cin>>n>>k;

    vector<Number> numbers;
    numbers.reserve(n);

    Number tmp;
    loop(n){
        cin>>tmp;
        numbers.push_back(tmp);
    }

    std::sort(numbers.begin(),numbers.end(),std::greater<Number>());

    Number m=Rank(k,numbers)-Rank(-k,numbers);

    if (IsPrime(m)) {
        cout<<"YES\n";
    }else{
        cout<<"NO\n";
    }

    cout<<m;

    return 0;
}  // function main
