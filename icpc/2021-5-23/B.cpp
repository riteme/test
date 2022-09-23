#include <stdio.h>
#include <algorithm>
#include <time.h>

using namespace std;

int n , p , q;
int a[2200000] , vis[2200000];
int rep;
int flag;
int out[1200000] , tot;
void dfs () {
	int now , len;
	now = 0; len = 0;
	while ( len < n ) {
		a[++len] = now;
		if ( now >= q ) now -= q;
		else now += p;
	}
	for ( int _ = 0 ; _ <= rep ; _++ ) {
		for ( int i = 1 ; i <= n ; i++ ) {
			out[++tot] = _ * (p+q) + a[i];
			//printf ( "%d " , a[i] );
		}
		//printf ( "\n" );
	}
}
void work () {
	int i , res;
	//srand(time(0));
	/*do {
		p = rand () * rand () % 20 + 1;
		q = rand () * rand () % 20 + 1;
	} while ( p == 1 || q == 1 || __gcd ( p , q ) != 1 );
	n = p + q + rand () % 2 * (rand()%2==0?1:-1) + (p+q) * rand () % 10;
	printf ( "input %d %d %d\n" , n , p , q );*/
	scanf ( "%d%d%d" , &n , &p , &q );
	if ( __gcd ( p , q ) != 1 || n < p + q - 1 ) {
		printf ( "-1\n" );
		return ;
	}
	if ( p == 1 ) {
		for ( i = 0 ; i <= n - 1 ; i++ ) {
			printf ( "%d%c" , i , i==n-1?'\n':' ' );
		}
		return ;
	}
	if ( q == 1 ) {
		for ( i = n - 1 ; i >= 0 ; i-- ) {
			printf ( "%d%c" , i , i==0?'\n':' ' );
		}
		return ;
	}
	rep = n / (p+q);
	if ( n % (p+q) == 0 ) {
		rep--;
		n = p + q;
		res = 0;
	}
	if ( n % (p+q) == 1 ) {
		n = p + q;
		rep--;
		res = 1;
	}
	if ( n % (p+q) == p + q - 1 ) {
		n = p + q;
		res = -1;
	}
	flag = 0;
	dfs ();
	if ( res == 1 ) {
		out[tot+1] = out[tot] + p;
		tot++;
	}
	if ( res == -1 ) {
		for ( i = 1 ; i < tot ; i++ ) {
			out[i] = out[i+1] - 1;
		}
		tot--;
	}
	for ( i = 0 ; i <= tot ; i++ ) {
		vis[i] = 0;
	}
	//printf ( "out:\n" );
	for ( i = 1 ; i <= tot ; i++ ) {
		printf ( "%d%c" , out[i] , i==tot?'\n':' ' );
	}
	/*for ( i = 1 ; i <= tot ; i++ ) {
		if ( i != 1 && (out[i] != out[i-1] + p && out[i] != out[i-1]-q) ) {
			printf ( "no\n" );
			return ;
		}
		if ( vis[out[i]] ) {
			printf ( "no2\n" );
			return ;
		}
		vis[out[i]] = 1;
		//printf ( "%d%c" , out[i] , i==tot?'\n':' ' );
	}*/
	tot = 0;
}
int main () {
	int t;
	scanf ( "%d" , &t );
	while ( t-- ) work ();
	return 0;
}
