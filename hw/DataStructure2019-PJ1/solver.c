#include <stdio.h>

int main() {
	int n;
	//read array length
	scanf("%d", &n);
	for (int i = 100000; i --; ){
		//print x and y. 1 <= x, y <= n and x != y
		printf("1 3\n");
		//flush stdout
		fflush(stdout);
		int t1;
		//get comparison result of a[x] and a[y]
		scanf("%d", &t1);	
	}
	//print 0 0 to terminate ask
	printf("0 0\n");
	//print swap times m
	printf("2\n");
	//print x, y to swap a[x] and a[y]. 1 <= x, y <= n and x != y
	printf("3 4\n3 5\n");
	//flush stdout
	fflush(stdout);
	int result;
	//!!!IMPORTANT!!! you should read the final score
	//without this judger may get "reached EOF" error.
	scanf("%d", &result);
	return 0;
}