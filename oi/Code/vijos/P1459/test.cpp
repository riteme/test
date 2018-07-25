#include <iostream>
#include <queue>

using namespace std;

static priority_queue<int,vector<int>,greater<int>> q;

int main(){
    q.push(1);
    q.push(2);
    cout<<q.top()<<endl;
    return 0;
}   
