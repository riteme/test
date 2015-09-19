#include <iostream>
using namespace std;

template <typename T>
void PrintArray(const T &a){
	for (auto &e : a) {
	    cout<<e<<' ';
	}  // foreach in a
	cout<<endl;
}

template <typename T,typename TOp=std::less_equal<typename T::value_type>>
bool IsSorted(const T &a,const TOp &op=TOp()){
	for (unsigned i=0;
	     i!=a.size()-1;
	     i++) {
	    if(!op(a[i],a[i+1])) return false;
	}  // for
	return true;
}

template <typename T>
void Print(const T &msg){
	cout<<msg<<endl;
}
