#include <stdio.h>
#include <algorithm>

using namespace std;

const int mod = 1000000007;
int n , e , m;
int taboo[2100][2100];
int dp[2100][20][20];
void mplus ( int &x , int &y ) {
	x = (x+y) % mod;
}
void work () {
	int i , j , k , l , o , u , v;
	scanf ( "%d%d%d" , &n , &e , &m );
	for ( i = 1 ; i <= m ; i++ ) {
		scanf ( "%d%d" , &u , &v );
		taboo[u][v] = 1;
	}
	dp[0][0][0] = 1;
	for ( i = 0 ; i < n ; i++ ) {
		for ( j = 0 ; j < 16 ; j++ ) {
			for ( k = 0 ; k < 16 ; k++ ) {
				if ( j % 2 == 1 && k % 2 == 1 ) {
					mplus ( dp[i+1][j/2][k/2] , dp[i][j][k] );
				}
				if ( j % 2 == 1 && k % 2 == 0 ) {
					for ( l = 0 ; l <= e ; l++ ) {
						if ( (j & (1<<l)) == 0 && !taboo[i+1+l][i+1] ) {
							mplus ( dp[i+1][(j|(1<<l))/2][k/2] , dp[i][j][k] );
						}
					}
				}
				if ( j % 2 == 0 && k % 2 == 1 ) {
					for ( l = 0 ; l <= e ; l++ ) {
						if ( (k & (1<<l)) == 0 && !taboo[i+1][i+1+l] ) {
							mplus ( dp[i+1][j/2][(k|(1<<l))/2] , dp[i][j][k] );
						}
					}
				}
				if ( j % 2 == 0 && k % 2 == 0 ) {
					if ( !taboo[i+1][i+1] ) mplus ( dp[i+1][j/2][k/2] , dp[i][j][k] );
					for ( l = 1 ; l <= e ; l++ ) {
						for ( o = 1 ; o <= e ; o++ ) {
							if ( (j&(1<<l)) == 0 && (k&(1<<o)) == 0 && !taboo[i+1+l][i+1] && !taboo[i+1][i+1+o] ) {
								mplus ( dp[i+1][(j|(1<<l))/2][(k|(1<<o))/2] , dp[i][j][k] );
							}
						}
					}
				}
			}
		}
	}
	printf ( "%d\n" , dp[n][0][0] );
}
int main () {
	work ();
	return 0;
}