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

	// for (auto &e : m) {
	//     cout<<e;
	// }  // foreach in c
	// cout<<" + ";

	// for (auto &e : n) {
	//     cout<<e;
	// }  // foreach in c
	// cout<<endl;

	for (int i=0;
	     i<bound;
	     i++) {
	    int sum=m[i]+n[i]+upload;
		// cout<<m[i]<<" + "<<n[i]<<" + "<<upload<<" = "<<sum<<endl;
		int d=sum%10;
		tmp.push_back(d);
		upload=sum/10;
	}  // for

	for (int i=bound;
	     i<m.size();
	     i++) {
	    int sum=m[i]+upload;
		// cout<<m[i]<<" + "<<upload<<" = "<<sum<<endl;
		int d=sum%10;
		tmp.push_back(d);
		upload=sum/10;
	}  // for

	if (upload!=0) {
	    tmp.push_back(upload);
	}

	// std::reverse(tmp.begin(),tmp.end());

	return tmp;
}

vector<int> Mut(const vector<int> &a,int b){
	vector<int> tmp=a;

	for (int i=1;
	     i<b;
	     i++) {
		// for (auto &e : tmp) {
		//     cout<<e;
		// }  // foreach in c
		// cout<<endl;
	    tmp=Add(tmp,a);
	}  // for

	return tmp;
}

int main(int argc, char const *argv[])
{
	int n;
	cin>>n;

	vector<int> number;
	int tmp=n;
	while (tmp!=0) {
		number.push_back(tmp%10);
		tmp/=10;
	}   // while

	for (int i=n-1;
	     i>1;
	     i--) {
	    number=Mut(number,i);
	}  // for

	std::reverse(number.begin(),number.end());

	for (auto &e : number) {
	    cout<<e;
	}  // foreach in number
	cout<<endl;

	return 0;
}