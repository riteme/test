#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int Partition(int *a,int left,int right){
	int k=left;
	int i=left;
	int j=right+1;

	while (true) {
		while (a[++i]<a[k]) {
			if (i==right) {
			    break;
			}
		}   // while

		while (a[k]<a[--j]) {
			if (j==left) {
			    break;
			}
		}   // while

		if (j<=i) {
		    break;
		}

		std::swap(a[i],a[j]);
	}   // while
	
	std::swap(a[k],a[j]);

	return j;
}

void QuickSort(int *a,int left,int right){
	if (right<=left) {
	    return;
	}

	int k=Partition(a,left,right);
	QuickSort(a,left,k-1);
	QuickSort(a,k+1,right);
}

int main() {
	freopen("rank.in","r",stdin);
	freopen("rank.out","w",stdout);

	int n;
	scanf("%d",&n);

	int numbers[n];

	int tmp;
	for (int i=0;
	     i<n;
	     i++) {
		scanf("%d",&tmp);
		numbers[i]=tmp;
	}  // for
	
	QuickSort(numbers,0,n);

	for (int i=0;
	     i<n;
	     i++) {
	    printf("%d ",numbers[i]);
	}  // for

    return 0;

    fclose(stdin);
    fclose(stdout);
}  // function main
