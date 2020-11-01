#include <stdio.h>
#include <algorithm>

using namespace std;

int n , p , q;
int a[120] , b[120];
int dp[101][1000100] , from[101][1000100];
bool is[101][1000100];
int flag , ans[120];
void solve () {
	int i , j;
	for ( j = 0 ; j <= n ; j++ )
		for ( i = 0 ; i <= p ; i++ ) {
			dp[j][i] = 9999999;
			is[j][i] = 0;
			from[j][i] = 0;
		}
	dp[0][0] = 0;
	for ( i = 1 ; i <= n ; i++ ) {
		for ( j = 0 ; j <= p ; j++ ) {
			dp[i][j] = dp[i-1][j];
			from[i][j] = j;
			is[i][j] = 0;
		}
		for ( j = p ; j >= 0 ; j-- ) {
			if ( dp[i][min(j+a[i],p)] > dp[i-1][j] + b[i] ) {
				dp[i][min(j+a[i],p)] = dp[i-1][j] + b[i];
				from[i][min(j+a[i],p)] = j;
				is[i][min(j+a[i],p)] = 1;
			}
		}
	}
	if ( dp[n][p] < q ) {
		printf ( "NO\n" );
		flag = 1;
		j = p;
		for ( i = n ; i >= 1 ; i-- ) {
			ans[i] = is[i][j];
			j = from[i][j];
		}
		for ( i = 1 ; i <= n ; i++ ) {
			printf ( "%d" , ans[i] );
		}
		printf ( "\n" );
	}
}
void work () {
	int i;
	scanf ( "%d" , &n );
	scanf ( "%d" , &p );
	for ( i = 1 ; i <= n ; i++ ) scanf ( "%d" , &a[i] );
	scanf ( "%d" , &q );
	for ( i = 1 ; i <= n ; i++ ) scanf ( "%d" , &b[i] );
	flag = 0;
	solve ();
	if ( flag == 1 ) return ;
	swap ( p , q );
	for ( i = 1 ; i <= n ; i++ ) {
		swap ( a[i] , b[i] );
	}
	solve ();
	if ( flag == 1 ) return ;
	printf ( "YES\n" );
}
int main () {
	work ();
	return 0;
}
