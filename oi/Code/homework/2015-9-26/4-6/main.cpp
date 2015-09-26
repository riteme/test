#include <iostream>

using namespace std;

template <typename T>
void Merge(const T a[],const T b[],int N,int M,T *target){
	const int length=N+M;

	// i: a的索引
	// j: b的索引
	// cnt: 目标数组的索引
	int i,j,cnt;
	i=j=cnt=0;

	// 归并分为四种情况
	while (cnt<length) {
		if (i>N) { // 如果a数组用尽，则将b数组的内容复制进去
		    target[cnt++]=b[j++];
		}else if (j>M) { // 如果b数组用尽，则将a数组的内容复制进去
		    target[cnt++]=a[i++];
		}else if (a[i]<b[j]) { // 如果a当前位置上的值比b中的小，则复制a中的
		    target[cnt++]=a[i++];
		} else { // 与上面相反
		    target[cnt++]=b[j++];
		}
	}   // while
}

int main(int argc, char const *argv[])
{
	int n,m;
	cin>>n>>m;

	int a[n],b[m];

	for (int i=0;
	     i<n;
	     i++) {
		cin>>a[i];
	}  // for

	for (int i=0;
	     i<m;
	     i++) {
		cin>>b[i];
	}  // for

	int arr[n+m];
	Merge(a,b,n,m,arr);

	for (int i=0;
	     i<n+m;
	     i++) {
	    cout<<arr[i]<<' ';
	}  // for
	cout<<endl;

	return 0;
}