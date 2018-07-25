#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

ifstream cin("rank.in");
ofstream cout("rank.out");

template <typename TIter>
void ShellSort(TIter first,TIter last){
	unsigned n=std::distance(first,last);

	unsigned h=1;

	while (h<n/3) {
		h=3*h+1;
	}   // while
	
	while (h>=1) {
		for (TIter it=first+h;
		     it!=last;
		     it++) {
		    for (TIter it2=it;
		         it2>=first+h && *it2 < *(it2-h);
		         it2-=h) {
		            std::swap(*it2,*(it2-h));
		    }  // for
		}  // for

		h/=3;
	}   // while
}

int main() {
	int num;
	cin>>num;

	vector<int> numbers;
	numbers.reserve(num);

	int tmp;
	while (cin>>tmp) {
		numbers.push_back(tmp);
	}   // while
	
	ShellSort(numbers.begin(),numbers.end());

	for (int i=0;
	     i<numbers.size();
	     i++) {
	    cout<<numbers[i]<<' ';
	}  // for
	cout<<endl;

    return 0;
}  // function main
