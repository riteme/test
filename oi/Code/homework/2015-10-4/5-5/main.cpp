#include <iostream>

using namespace std;

bool IsCycle(const string &str,int cycleSize){
	if (str.size()%cycleSize!=0) {
	    return false;
	}

	string c=str.substr(0,cycleSize);
	for (int i=cycleSize;
	     i<str.size();
	     i+=cycleSize) {
	    if (c!=str.substr(i,cycleSize)) {
	        return false;
	    }
	}  // for

	return true;
}

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);

	string s;
	cin>>s;

	for (int i=1;
	     i<=s.size();
	     i++) {
	    if (IsCycle(s,i)) {
	        cout<<i<<endl;
	        return 0;
	    }
	}  // for

	cout<<s.size()<<endl;
	
	return 0;
}