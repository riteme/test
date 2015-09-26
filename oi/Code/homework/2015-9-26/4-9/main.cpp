#include <iostream>

using namespace std;

#define NUMBER_MAX 200

int main(int argc, char const *argv[])
{
	bool a[NUMBER_MAX+1];
	for (auto &e : a) {
	    e=true;
	}  // foreach in a

	for (int i=2;
	     i<=NUMBER_MAX;
	     i++) {
	    if (a[i]) {
	        for (int j=i*2;
	             j<=NUMBER_MAX;
	             j+=i) {
	            a[j]=false;
	        }  // for
	    }
	}  // for

	for (int cnt=2;
	     cnt<=NUMBER_MAX;
	     cnt++) {
	    if (a[cnt]) {
	        cout<<cnt<<' ';
	    }
	}  // for

	cout<<endl;

	return 0;
}