#include "Merge.hpp"
#include "../tool.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
	cout<<boolalpha;
	vector<int> vec={23,132,53,6456,75,23,4,5,1,3,46,7,5,44,34,6,-12432,-4234};
	Merge<decltype(vec)> sorter(vec);
	PrintArray(vec);
	vec=sorter.Sort();
	PrintArray(sorter.Sort());
	Print(IsSorted(vec));

	return 0;
}
