#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> Add(const vector<int> &a,const vector<int> &b){
	vector<int> tmp;
	int upload=0;
	const vector<int> &m=a.size()<=b.size()?b:a;
	const vector<int> &n=a.size()<=b.size()?a:b;
	int bound=n.size();

	for (int i=0;
	     i<bound;
	     i++) {
	    int sum=m[i]+n[i]+upload;
		int d=sum%10;
		tmp.push_back(d);
		upload=sum/10;
	}  // for

	for (int i=bound;
	     i<m.size();
	     i++) {
	    int sum=m[i]+upload;
		int d=sum%10;
		tmp.push_back(d);
		upload=sum/10;
	}  // for

	if (upload!=0) {
	    tmp.push_back(upload);
	}

	return tmp;
}

vector<int> Mut(const vector<int> &a,int b){
	if (b==0) {
	    return {0};
	}

	vector<int> tmp=a;

	for (int i=1;
	     i<b;
	     i++) {
	    tmp=Add(tmp,a);
	}  // for

	return tmp;
}

int GetDigit(const char c){
	switch (c) {
	    case '0': return 0;
	    case '1': return 1;
	    case '2': return 2;
	    case '3': return 3;
	    case '4': return 4;
	    case '5': return 5;
	    case '6': return 6;
	    case '7': return 7;
	    case '8': return 8;
	    case '9': return 9;
	}  // switch to c
	return -1;
}

int Compute(const vector<int> &vec){
	if (vec.size()==1) {
	    return vec[0];
	}else{
		vector<int> tmp={1};
		for (auto i : vec) {
		    tmp=Mut(tmp,i);
		}  // foreach in vec
		return Compute(tmp);
	}
}

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);

	vector<int> num;
	string s;
	cin>>s;
	for (auto beg=s.rbegin();
	     beg!=s.rend();
	     beg++) {
	    num.push_back(GetDigit(*beg));
	}  // for
	cout<<Compute(num)<<endl;

	return 0;
}
