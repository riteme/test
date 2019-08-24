#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(){
	char map[256];
	char marked[256];
	memset(marked,0,sizeof(char)*256);
	memset(map,0,sizeof(char)*256);
	
	bool failed=false;
	int cnt=0;
	string a,b,c;
	cin>>b>>a>>c;
	
	for(int i=0;i<a.size() and !failed;i++){
		if(marked[a[i]]!=0 and marked[a[i]]!=b[i]){
			failed=true;
		}else{
			map[b[i]]=a[i];
			marked[a[i]]=b[i];
			cnt++;
		}
	}
	
	if(cnt<26){
		failed=true;
	}
	
	if(failed){
		cout<<"Failed";
	}else{
		for(int i=0;i<c.size();i++){
			c[i]=map[c[i]];
		}
	
		cout<<c;
	}
	
	return 0;
}
