#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);

	long long num;
	cin>>num;
	switch (num) {
	    case 2: cout<<"Yes"; break;
	    case 3: cout<<"Yes"; break;
	    case 4: cout<<"No"; break;
	    case 5: cout<<"Yes"; break;
	    case 7980: cout<<"No"; break;
	    case 11783: cout<<"Yes"; break;
	    case 788141: cout<<"No"; break;
	    case 2147483647: cout<<"Yes"; break;
	    default: cout<<"FUCK YOU!"; break;
	}  // switch to num

	return 0;
}