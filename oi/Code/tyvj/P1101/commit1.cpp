#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

	std::sort(vec.begin(),vec.end());

	for (auto &e : vec) {
	    cout<<e<<endl;
	}  // foreach in vec
	
	return 0;
}