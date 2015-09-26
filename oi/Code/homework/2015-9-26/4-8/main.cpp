#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
	int n,k;
	cin>>n>>k;

	bool switches[n];
	for (int i=0;
	     i<n;
	     i++) {
	    switches[i]=false;
	}  // for
	
	for (int i=1;
	     i<=k;
	     i++) {
	    for (int j=i-1;
	         j<n;
	         j+=i) {
	        switches[j]=!switches[j];
	    }  // for
	}  // for

	for (int i=0;
	     i<n;
	     i++) {
	    if (switches[i]) {
	        cout<<i+1<<' ';
	    }
	}  // for

	cout<<endl;

	return 0;
}
