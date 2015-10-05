#include <cassert>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

// TOO SLOW
template <typename TIter>
void PopSort(TIter first,TIter last){
	for (TIter it=first;
	     it!=last;
	     it++) {
	    for (TIter it2=first;
	         it2!=last;
	         it2++) {
	        if (*it<*it2) {
	            std::swap(*it,*it2);
	        }
	    }  // for
	}  // for
}

// 4x faster than PopSort
template <typename TIter>
void SelectionSort(TIter first,TIter last){
	for (TIter it=first;
	     it!=last;
	     it++) {
	    TIter minIt=it;

		// 一直向后面找到该去的地方
		for (TIter it2=it;
		     it2!=last;
		     it2++) {
		    if (*it2<*minIt) {  // 发现后面的数更小，应当将更小的数往前移
		        minIt=it2;
		    }
		}  // for

		std::swap(*minIt,*it);
	}  // for
}

// 20% faster than SelectionSort
template <typename TIter>
void InsertionSort(TIter first,TIter last){
	for (TIter it=first;
	     it!=last;
	     it++) {
	    TIter min=it;

		for (TIter it2=first;
		     it2!=it;
		     it2++) {
		    if (*it<*it2) {
		        min=it2;
		        break;
		    }
		}  // for

		if (min==it) {
		    continue;
		}

		auto tmp=*it;

		for (TIter iter=it;
		     iter!=min;
		     iter--) {
		    *iter=*(iter-1);
		}  // for

		*min=tmp;
	}  // for
}

// 75x faster than InsertionSort
template <typename TIter>
void ShellSort(TIter first,TIter last){
	auto n=std::distance(first,last);

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

// 2x faster than ShellSort
// MergeSort BEGIN
template <typename T,unsigned N>
void Merge(T (&a)[N],T (&aux)[N],int left,int mid,int right){
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

template <typename T,unsigned N>
void MergeSortImpl(T (&a)[N],T (&aux)[N], int left, int right){
	if (right <= left) { return; }

	unsigned mid = (left + right) / 2;
	MergeSortImpl(a,aux,left, mid);
	MergeSortImpl(a,aux,mid + 1, right);
	Merge(a,aux,left, mid, right);
}

template <typename T,unsigned N>
void MergeSort(T (&a)[N]){
	T aux[N];

	MergeSortImpl(a,aux,0,N-1);
}
//MergeSort END

// QuickSort BEGIN
template <typename TIter>
TIter Partition(TIter left,TIter right){
	TIter k=left;
	TIter i=left;
	TIter j=right+1;

	while (true) {
		while (*(++i)<*k) {
			if (i>=right) {
			    break;
			}
		}   // while

		while (*k<*(--j)) {
			if (j<=left) {
			    break;
			}
		}   // while

		if (j<=i) {
		    break;
		}

		std::swap(*i,*j);
	}   // while
	
	std::swap(*k,*j);

	return j;
}

template <typename TIter>
void QuickSort(TIter first,TIter last){
	if (last<=first) {
	    return;
	}

	TIter k=Partition(first,last);
	QuickSort(first,k-1);
	QuickSort(k+1,last);
}
//QuickSort END

// Hmm...
template <typename TIter>
void SuperQuickSort(TIter first,TIter last){
	std::sort(first,last);
}

template <typename TIter>
void SuperMergeSort(TIter first,TIter last){
	std::stable_sort(first,last);
}

#define DATA_SIZE 10000

#define SHUFFLE(array) std::random_shuffle(std::begin(array),std::end(array))
#define SORT(sortFunc,data) cout << #sortFunc << endl; \
							sortFunc(std::begin(data),std::end(data)); \
							cout << "END " << #sortFunc << endl

#define IS_SORTED(array) assert(std::is_sorted(std::begin(array),std::end(array)))

int data[DATA_SIZE];

int main() {
    ios::sync_with_stdio(false);

    for (int i=0;
         i<DATA_SIZE;
         i++) {
        data[i]=i;
    }  // for

    // 前面三个慎重打开

    SHUFFLE(data);
    SORT(PopSort,data);
    IS_SORTED(data);

    SHUFFLE(data);
    SORT(SelectionSort,data);
    IS_SORTED(data);

    SHUFFLE(data);
    SORT(InsertionSort,data);
    IS_SORTED(data);

    SHUFFLE(data);
    SORT(ShellSort,data);
    IS_SORTED(data);

    SHUFFLE(data);
    cout<<"MergeSort"<<endl;
    MergeSort(data);
    cout<<"END MergeSort"<<endl;
    IS_SORTED(data);

    SHUFFLE(data);
    SORT(QuickSort,data);
    IS_SORTED(data);

    SHUFFLE(data);
    SORT(SuperQuickSort,data);
    IS_SORTED(data);

    SHUFFLE(data);
    SORT(SuperMergeSort,data);
    IS_SORTED(data);

    return 0;
}  // function main
