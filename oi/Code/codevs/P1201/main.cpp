#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    vector<long> numbers;
    int n;

    cin>>n;
    numbers.reserve(n);

    long tmp;
    for(int i=1;i<=n;i++){
    	cin>>tmp;
    	numbers.push_back(tmp);
    }

    cout<<*std::min_element(numbers.begin(),numbers.end())<< ' '
    	<<*std::max_element(numbers.begin(),numbers.end());

    return 0;
}  // function main
