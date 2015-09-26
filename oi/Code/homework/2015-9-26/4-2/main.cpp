#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

template <typename T,unsigned N>
void PopSort(T (&a)[N]){
	for (int i=0;
	     i<N;
	     i++) {
	    for (int j=0;
	         j<N;
	         j++) {
	        if (a[i]<a[j]) {
	            std::swap(a[i],a[j]);
	        }
	    }  // for
	}  // for
}

template <typename T,unsigned N>
void SelectionSort(T (&a)[N]){
	for (int i=0;
	     i<N;
	     i++) {
		int index=i;

		for (int j=i+1;
		     j<N;
		     j++) {
			if (a[j]<a[index]) {
			    index=j;
			}
		}  // for

		std::swap(a[i],a[index]);
	}  // for
}

#define ARRAY_SIZE 50000

int main(int argc, char const *argv[])
{
	int a[ARRAY_SIZE];
	for (int i=0;
	     i<ARRAY_SIZE;
	     i++) {
	    a[i]=i;
	}  // for

	cout<<"BEGIN"<<endl;

	cout<<"POP"<<endl;
	std::random_shuffle(std::begin(a),std::end(a));
	PopSort(a);
	assert(std::is_sorted(std::begin(a),std::end(a)));

	cout<<"SELECTION"<<endl;
	std::random_shuffle(std::begin(a),std::end(a));
	SelectionSort(a);
	assert(std::is_sorted(std::begin(a),std::end(a)));

	cout<<"END"<<endl;

	return 0;
}
