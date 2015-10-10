#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	int tmp;
	int target;
	bool isPrinted=false;

	cin>>target;

	while (cin>>tmp) {
		if (target<=tmp&&!isPrinted) {
		    cout<<target<<' ';
		    isPrinted=true;
		}
		cout<<tmp<<' ';
	}   // while

	cout<<endl;

	return 0;
}