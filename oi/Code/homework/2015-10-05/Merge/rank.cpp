#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

ifstream cin("rank.in");
ofstream cout("rank.out");

template <typename T>
void Merge(T &a,T &aux,int left,int mid,int right){
	for (unsigned index = left; index <= right; index++) { aux[index] = a[index]; }  // for

	unsigned i = left, j = mid + 1;
	for (unsigned k = left; k <= right; k++) {
	    if (i > mid)
	        a[k] = aux[j++];
	    else if (j > right)
	        a[k] = aux[i++];
	    else if (aux[i] < aux[j])
	        a[k] = aux[i++];
	    else
	        a[k] = aux[j++];
	}  // for
}

template <typename T>
void MergeSortImpl(T &a,T &aux, int left, int right){
	if (right <= left) { return; }

	unsigned mid = (left + right) / 2;
	MergeSortImpl(a,aux,left, mid);
	MergeSortImpl(a,aux,mid + 1, right);
	Merge(a,aux,left, mid, right);
}

template <typename T>
void MergeSort(T &a){
	T aux;
	aux.resize(a.size());

	MergeSortImpl(a,aux,0,a.size()-1);
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
	
	MergeSort(numbers);

	for (int i=0;
	     i<numbers.size();
	     i++) {
	    cout<<numbers[i]<<' ';
	}  // for
	cout<<endl;

    return 0;
}  // function main
