#include <stdio.h>
#include <algorithm>

using namespace std;

int n , y;
int a[1200000];
int ed[1200000];
void work () {
	int i , j , now , o;
	for ( i = 1 ; i <= n ; i++ ) scanf ( "%d" , &a[i] );
	sort ( a + 1 , a + 1 + n );
	for ( i = 1 ; i <= y ; i++ ) {
		ed[now] = a[now] + i;
		for ( j = now + 1 ; j <= n ; j++ ) {
			ed[j] = max ( ed[j-1] , a[j] ) + i;
		}
		//printf ( "%d%c" , ed[n] , i==y?'\n':' ' );
		while ( now < n && ed[n] >= a[now] + y ) {
			now++;
			ed[now] = a[now] + i;
			for ( j = now + 1 ; j <= n ; j++ ) {
				o = ed[j];
				ed[j] = max ( ed[j-1] , a[j] ) + i;
				if ( o == ed[j] ) break;
			}
			//printf ( "$#%d %d %d\n" , i , j , now );
		}
		printf ( "%d%c" , ed[n] , i==y?'\n':' ' );
	}
}
int main () {
	while ( scanf ( "%d%d" , &n , &y ) != EOF )
		work ();
	return 0;
}

