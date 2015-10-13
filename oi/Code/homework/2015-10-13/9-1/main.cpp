#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

int main(){
	ios::sync_with_stdio(false);
	
	int i=9;
	// cin>>i;
	
	vector<int> buffer;
	buffer.reserve(100);
	
	int upload=0;
	int tmp=i;
	int mult;
	
	do{
		mult=tmp*i+upload;
		upload=mult/10;
		tmp=mult%10;
		buffer.push_back(tmp);
		
		if(tmp==1 && buffer[buffer.size()-2]==0){
			break;
		}
	}while(true);
	
	for(auto beg=buffer.rbegin(); beg!=buffer.rend(); beg++){
		cout<<*beg;
	}
	cout<<i;
	
	return 0;
}

