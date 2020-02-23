#include <stdio.h>
#include <algorithm>

using namespace std;

typedef __int128_t i8;

//long long
long long n , le , ri;
long long a[120000] , b[120000];
long long l[120000] , r[120000];
long long mn , sum , ans;
bool check ( i8 x ) {
	i8 ret , i , use;
	ret = 214748364777777ll;
	use = 0;
	/*for ( i = 1 ; i <= n ; i++ ) {
		if ( l[i] != 0 )
			ret = min ( ret , a[i] / l[i] );
	}*/
	//printf ( "%lld\n" , x );
	for ( i = 1 ; i <= n ; i++ ) {
		b[i] = a[i] - x * l[i];
		if ( b[i] < 0 ) return false;
		use += min ( (i8)b[i] , (r[i]-l[i]) * x );
	}
	if ( use >= (le-mn) * x ) return true;
	return false;
}
void work () {
	long long i , j , ll , rr , mid;
	scanf ( "%lld%lld%lld" , &n , &le , &ri );
	for ( i = 1 ; i <= n ; i++ ) {
		scanf ( "%lld" , &a[i] );
		sum += a[i];
	}
	for ( i = 1 ; i <= n ; i++ ) {
		scanf ( "%lld%lld" , &l[i] , &r[i] );
		mn += l[i];
	}
	if ( mn > ri ) {
		printf ( "%lld\n" , 0 );
		return ;
	}
	if ( mn >= le ) {
		ans = 2147483647777ll;
		for ( i = 1 ; i <= n ; i++ ) {
			if ( l[i] != 0 )
				ans = min ( ans , a[i] / l[i] );
		}
		printf ( "%lld\n" , ans );
		return ;
	}
	ll = 0; rr = sum;
	while ( ll < rr - 1 ) {
		mid = (ll+rr)/2;
		if ( check ( mid ) == 1 ) ll = mid;
		else rr = mid;
	}
	if ( check ( rr ) == 1 ) ans = rr;
	else ans = ll;
	printf ( "%lld\n" , ans );
}
int main () {
	work ();
	return 0;
}
