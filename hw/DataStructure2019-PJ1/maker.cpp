#include <bits/stdc++.h>
using namespace std; 

int n, k; 
int a[20000]; 

int main(int argc, char** argv ) {
	n = atoi(argv[1]); 
	k = atoi(argv[2]);
    int seed = 0;
    if (argc > 3)
        seed = atoi(argv[3]);
    srand(seed);
	//cin>>n>>k;
	for (int i = 1; i <= n; ++i) a[i] = i; 
	for (int i = 1; i <= k; ++i) {
		int x, y; 
		x = rand() % n + 1; 
		y = rand() % n + 1;  
		swap(a[x], a[y]); 
	}
	cout<<n<<' '<<k<<endl; 
	for (int i = 1; i <= n; ++i) cout<<a[i]<<' ';
	puts( "" ); 
}
