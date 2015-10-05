#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned ValueType;

#define loop(n) for(unsigned __loop__=0;__loop__<n;__loop__++)

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);

    int n;
    cin>>n;

    vector<ValueType> heaps;
    heaps.reserve(n);

    ValueType tmp;
    loop(n){
        cin>>tmp;
        heaps.push_back(tmp);
    }

    std::sort(heaps.begin(),heaps.end());

    unsigned energyCount=0;
    unsigned need;
    for(int i=0;i<heaps.size()-1;i++){
        need=heaps[i]+heaps[i+1];
        energyCount+=need;
        heaps[i+1]=need;
    }

    cout<<energyCount;

    return 0;
}  // function main
