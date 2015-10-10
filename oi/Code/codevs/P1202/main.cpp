#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int n;
    cin>>n;

    long num;
    long sum=0;
    for(int i=1;i<=n;i++){
    	cin>>num;
    	sum+=num;
    }

    cout<<sum;

    return 0;
}  // function main
