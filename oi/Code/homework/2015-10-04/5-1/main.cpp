#include <iostream>

using namespace std;

constexpr int NumberOfLines=26;

int PrintSpace(int n){
	for (int i=1;
	     i<=n;
	     i++) {
	    cout<<' ';
	}  // for
	return n;
}

void PrintLine(int line){
	int start = PrintSpace(NumberOfLines-line)+1;

	char c='A';
	for (int i=start;
	     i<=NumberOfLines;
	     i++) {
	    cout<<c;
		c++;
	}  // for

	for (c-=2;
	     c>='A';
	     c--) {
	    cout<<c;
	}  // for

	cout<<endl;
}

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);

	for (int i=1;
	     i<=NumberOfLines;
	     i++) {
	    PrintLine(i);
	}  // for

	return 0;
}