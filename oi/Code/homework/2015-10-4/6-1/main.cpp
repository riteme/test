#include <cctype>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);

	string data;
	cin>>data;

	string numberBuffer;
	vector<int> numbers;
	for (auto c : data) {
	    if (!isdigit(c) && !numberBuffer.empty()) {
	        numbers.push_back(stoi(numberBuffer));
	        numberBuffer.clear();
	    }else if(isdigit(c)){
	    	numberBuffer+=c;
	    }
	}  // foreach in data

	if (!numberBuffer.empty()) {
	    numbers.push_back(stoi(numberBuffer));
	}

	cout<<numbers.size()<<'\n';
	for (auto i : numbers) {
	    cout<<i<<' ';
	}  // foreach in numbers
	cout<<'\n';

	return 0;
}