#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int size=7;
vector<int> weight={1,2,3,4};
vector<int> values={1,2,3,4};

void f(int size,int n,vector<vector<int>> &table){
	if(n==0){
		if(weight[n]<=size && table[n][size]!=-1){
			table[n][size]=values[n];
		}
	}else{
		f(size,n-1,table);
		f(size-weight[n],n-1,table);
		table[n][size]=std::max(table[n-1][size],table[n-1][size-weight[n]]);
	}
}

int f(){
	vector<vector<int>> table;
	
	table.resize(weight.size());
	for(auto &e:table){
		e.resize(size+1);
	}
	
	for(auto &line:table){
		for(auto &i:line){
			i=-1;
		}
	}
	
	f(size,weight.size()-1,table);
	
	int max=0;
	for(auto &line:table){
		for(auto i:line){
			if(i>max) max=i;
			cout<<i<<", ";
		}
		cout<<'\n';
	}
	
	return max;
}

int main(){
	ios::sync_with_stdio(false);
	
	int result=f();
	cout<<result;
	
	return 0;
}
