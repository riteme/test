#include <iostream>
#include <algorithm>

using namespace std;

int BinarySearch(const int a[],const int i,int left,int right){
	if (right<left) {
	    return -1;
	}

	int mid=(left+right)/2;

	if (a[mid]==i) {
	    return mid;
	}else if(a[mid]<i){
		return BinarySearch(a,i,mid+1,right);
	}else{
		return BinarySearch(a,i,left,mid-1);
	}
}

int main(int argc, char const *argv[])
{
	int n,target;

	cin >>n>>target;

	int arr[n];

	for (int i=0;
	     i<n;
	     i++) {
	    int tmp;
		cin>>tmp;
		arr[i]=tmp;
	}  // for

	int index=BinarySearch(arr,target,0,n-1);
	if (index<0) {
	    cout<<"No answer"<<endl;
	}else{
		cout<<index+1<<endl;
	}

	return 0;
}