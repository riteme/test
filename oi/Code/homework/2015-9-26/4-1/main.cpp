#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

int main(int argc, char const *argv[])
{
	list<int> numbers;

	int tmp;
	while (cin>>tmp) {
		numbers.push_back(tmp);
	}   // while

	auto minIter=std::min_element(numbers.begin(),numbers.end());
	std::iter_swap(numbers.begin(),minIter);

	cout<<*minIter<<endl;
	for (auto i : numbers) {
	    cout<<i<<' ';
	}  // foreach in numbers
	cout<<endl;

	return 0;
}