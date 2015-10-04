#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool StringLessCompare(const string &a,const string &b){
	auto bound=a.size()<b.size()?a.size():b.size();

	for (int i=0;
	     i<bound;
	     i++) {
	    if (a[i]<b[i]) {
	        return true;
	    }else if(a[i]>b[i]){
	    	return false;
	    }
	}  // for

	if (a.size()<b.size()) {
	    return true;
	}else if (a.size()>b.size()) {
	    return false;
	}
}

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);

	vector<string> vec;
	int n;
	cin>>n;
	vec.resize(n);

	for (auto &s : vec) {
	    cin>>s;
	}  // foreach in vec

	std::sort(vec.begin(),vec.end(),StringLessCompare);

	for (auto &e : vec) {
	    cout<<e<<endl;
	}  // foreach in vec
	
	return 0;
}