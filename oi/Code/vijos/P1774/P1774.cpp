#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

typedef list<int>::iterator iter_t;

static list<int> l;
static int n,m;
static int cnt=0;

void push(int x){
	iter_t iter=std::find(l.begin(),l.end(),x);
	
	if(iter==l.end()){
		if(l.size()==m){
			l.pop_front();
		}
		
		cnt++;
		l.push_back(x);
	}
}

int main(){
	ios::sync_with_stdio(false);
	
	cin>>m>>n;
	
	for(int i=0;i<n;i++){
		int tmp;
		cin>>tmp;
		push(tmp);
	}
	
	cout<<cnt;
}
