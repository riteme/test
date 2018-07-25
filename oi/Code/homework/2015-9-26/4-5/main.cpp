#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
	int a[1000];
	int right=0;

	std::fill(std::begin(a),std::end(a),-1);

	int m;
	cin>>m;

	int tmp;
	for (;
	     cin>>tmp;
	     right++) {
	    a[right]=tmp;
	}  // for
	right-=1;

	// 将[0,m]整体一位一位地右移
	for (int i=0;
	     i+m<=right;
	     i++) {
	    for (int j=i+m;
	         j>i;
	         j--) {
	        std::swap(a[j-1],a[j]);
	    	cout<<"Move "<<j-1<<" to "<<j<<endl;
	    }  // for
	}  // for

	for (int i=0;
	     i<=right;
	     i++) {
	    cout<<a[i]<<' ';
	}  // for
	cout<<endl;

	return 0;
}