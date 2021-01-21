#include <stdio.h>
#include <algorithm>

using namespace std;

const long long mod = 1000000007;
long long A , B , C , K , c;
long long fac[320000] , ifac[320000];
long long ans;
long long ksm ( long long f , long long x ) {
	long long s = 1;
	while ( x ) {
		if ( x % 2 == 1 ) s = s * f % mod;
		f = f * f % mod; x = x / 2;
	}
	return s % mod;
}
long long inv ( long long x ) {
	return ksm ( x , mod - 2 );
}
void predo () {
	long long i;
	fac[0] = 1;
	for ( i = 1 ; i <= 300000 ; i++ ) {
		fac[i] = (fac[i-1] * i) % mod;
	}
	ifac[300000] = inv ( fac[300000] );
	for ( i = 299999 ; i >= 0 ; i-- ) {
		ifac[i] = (ifac[i+1] * (i+1)) % mod;
	}
}
long long Com ( long long x , long long y ) {
	if ( y < 0 ) return 0;
	if ( x < y ) return 0;
	return fac[x] * ifac[y] % mod * ifac[x-y] % mod;
}
void work () {
	scanf ( "%lld%lld%lld%lld%lld" , &A , &B , &C , &K , &c );

	if (K < c + 2)
		ans = 0;
	else
		ans = Com ( C , c ) * ( Com ( A+B , K-c ) - Com ( A , K - c ) - Com ( B , K - c ) ) % mod;

	if ( ans < 0 ) ans += mod;
	printf ( "%lld\n" , ans );
}
int main () {
	int t;
	scanf ( "%d" , &t );
	predo ();
	while ( t-- ) work ();
	return 0;
}
