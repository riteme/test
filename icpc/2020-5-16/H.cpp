#include <stdio.h>
#include <algorithm>

using namespace std;

int n , b , left;
int ans[120000];
void work () {
	int i , j , t;
	scanf ( "%d" , &n );
	for ( b = 1 ; b * b <= n ; b++ ) ;
	b--;
	if ( b * b == n ) {
		left = b;
	}
	else left = b + 1;
	i = 1;
	while ( left ) {
		if ( n - i + 1 <= b + (left-1) * (b+1) ) {
			t = i;
			if ( t + b - 1 > n ) {
				t = n - b + 1;
			}
			for ( j = b ; j >= 1 ; j-- , i++ ) {
				ans[i] = t + j - 1;
			}
		}
		else {
			t = i;
			if ( t + b - 1 > n ) {
				t = n - b + 1;
			}
			for ( j = b + 1 ; j >= 1 ; j-- , i++ ) {
				ans[i] = t + j - 1;
			}
		}
		left--;
	}
	for ( i = 1 ; i <= n ; i++ ) {
		printf ( "%d%c" , ans[i] , i==n?'\n':' ' );
	}
}
int main () {
	int t;
	scanf ( "%d" , &t );
	while ( t-- ) work ();
	return 0;
}
