#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	int n,m;
	cin>>n>>m;

	bool people[n+1];
	for (int i=1;
	     i<=n;
	     i++) {
	    people[i]=true;
	}  // for

	int cnt=0;
	int pos=1;
	for (int i=1;
	     i<=n;
	     ) {
		if (pos>n) {
		    pos=1;
		}
		if(people[pos]){
		    cnt++;
		}
		if (cnt==m) {
		    cnt=0;
		    people[pos]=false;
		    cout<<pos<<' ';
		    i++;
		}
		pos++;
	}  // for

	cout<<endl;

	return 0;
}