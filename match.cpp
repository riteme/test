#include <cmath>
#include <iostream>
#include <string>

using namespace std;

bool Equal(int n,const string &seq){
	int pos=seq.size()-1;
	
	while(n>0 && pos>=0){
		if(seq[pos--] - '0' != n%10){
			return false;
		}
		n/=10;
	}
	
	return true;
}

int GetBase(const string &seq){
	int length=1;
	int base=0;
	bool failed=false;
	
	while(length<=seq.size() && !failed){
		for(int offest=0; offest<=seq.size()%length && !failed; offest++){
			int pos=offest;
			base=stoi(seq.substr(offest,length));
			
			for(int i=base; pos<seq.size() && !failed; pos+=log10(i)+1,i++){
				if(!Equal(i,seq.substr(pos,log10(i)+1))){
					failed=true;
				}
			}
		}
		
		length++;
	}
	
}

int main(){
	ios::sync_with_stdio(false);
	
	string subseq;
	int i;
	cin>>subseq>>i;
	
	cout<<boolalpha<<Equal(i,subseq);
	
	return 0;
}
