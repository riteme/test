#include <stdio.h>
#include <algorithm>

using namespace std;

//long long
//0 matrix
long long n , m;
long long a[3100][310] , b[3100][310];
long long num[3100] , index , ini[3100];
long long now;
long long useful[3100];
long long ans[120000] , cnt;
long long ksm ( long long f , long long x , long long mod ) {
	long long s = 1;
	while ( x ) {
		if ( x % 2 == 1 ) s = s * f % mod;
		f = f * f % mod; x = x / 2;
	}
	return s % mod;
}
long long inv ( long long x , long long mod ) {
	return ksm ( x , mod - 2 , mod );
}
void swapline ( long long i , long long j ) {
	long long k;
	for ( k = 1 ; k <= n ; k++ ) {
		swap ( a[i][k] , a[j][k] );
	}
	for ( k = 1 ; k <= index ; k++ ) {
		swap ( b[i][k] , b[j][k] );
	}
	swap ( num[i] , num[j] );
	swap ( ini[i] , ini[j] );
}
void minusline ( long long i , long long j , long long mod ) {
	long long k , co = a[j][now];
	for ( k = 1 ; k <= n ; k++ ) {
		a[j][k] = (a[j][k] -a[i][k]*co) % mod;
	}
	for ( k = 1 ; k <= index ; k++ ) {
		b[j][k] = (b[j][k]-b[i][k]*co) % mod;
	}
}
void gauss ( long long mod ) {
	long long i , j , k , co;
	now = 1;
	for ( i = 1 ; i <= m ; i++ ) {
		if ( now > n ) break;
		if ( a[i][now] == 0 ) {
			for ( j = i + 1 ; j <= m ; j++ ) {
				if ( a[j][now] != 0 ) break;
			}
			if ( j <= m ) {
				swapline ( i , j );
			}
			else {
				now++;
				i--;
				continue;
			}
		}
		if ( a[i][now] < 0 ) a[i][now] += mod;
		co = inv ( a[i][now] , mod );
		for ( j = 1 ; j <= n ; j++ ) {
			a[i][j] = (a[i][j]*co) % mod;
			b[i][j] = (b[i][j]*co) % mod;
		}
		num[i] = ++index;
		b[i][index] = 1;
		for ( j = i + 1 ; j <= m ; j++ ) {
			if ( a[j][now] ) {
				minusline ( i , j , mod );
			}
		}
		now++;
	}
}
void work () {
	long long i , j;
	double in;
	scanf ( "%lld%lld" , &m , &n );
	// m = 3000; n = 300;
	for ( i = 1 ; i <= m ; i++ ) {
		for ( j = 1 ; j <= n ; j++ ) {
			scanf ( "%lf" , &in );
			a[i][j] = in * 100;
			// a[i][j] = rand () * rand () % 10000000;
		}
		ini[i] = i;
	}
	gauss ( 998244353 );
	/*for ( i = 1 ; i <= m ; i++ ) {
		for ( j = 1 ; j <= n ; j++ ) {
			printf ( "%d " , a[i][j] );
		}
		// printf ( "   " );
		// for ( j = 1 ; j <= n ; j++ ) {
		// 	printf ( "%d " , b[i][j] );
		// }
		// printf ( "num:%d,ini:%d\n" , num[i] , ini[i] );
	}*/

	for ( i = 1 ; i <= m ; i++ ) {
		if ( num[i] == 0 ) {
			for ( j = 1 ; j <= n ; j++ ) {
				if ( b[i][j] < 0 ) b[i][j] += 998244353;
				if ( b[i][j] != 0 ) useful[j]++;
			}
		}
	}
	for ( i = 1 ; i <= m ; i++ ) {
		if ( num[i] && useful[num[i]] == 0 ) {
			ans[++cnt] = ini[i];
		}
	}
	sort ( ans + 1 , ans + 1 + cnt );
	printf ( "%lld\n" , cnt );
	for ( i = 1 ; i <= cnt ; i++ ) {
		printf ( "%lld%c" , ans[i] , i==cnt?'\n':' ' );
	}
}
int main () {
	work ();
	return 0;
}
