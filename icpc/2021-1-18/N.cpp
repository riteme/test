#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;

struct node {
	int v , f , c;
	node *next , *rev;
} pool[1220222] , *g[120000] , *from[120000];
int top;
int d , b , m , n;
int a[51000] , x[12002];
int dis[120000] , f[120000];
int s , t;
void clear () {
	int i;
	for ( i = 1 ; i <= t ; i++ ) {
		g[i] = NULL;
	}
	for ( i = 1 ; i <= top ; i++ ) {
		pool[i] = pool[0];
	}
	top = 0;
}
void add ( int u , int v , int f , int c ) {
	node *tmp1 = &pool[++top] , *tmp2 = &pool[++top];
	tmp1 -> v = v; tmp1 -> f = f; tmp1 -> c = c; tmp1 -> next = g[u]; g[u] = tmp1; tmp1 -> rev = tmp2;
	tmp2 -> v = u; tmp2 -> f = 0; tmp2 -> c = -c; tmp2 -> next = g[v]; g[v] = tmp2; tmp2 -> rev = tmp1;
}
bool spfa () {
	int i , k;
	queue < int > q;
	for ( i = 1 ; i <= t ; i++ ) {
		dis[i] = 99999999;
		f[i] = 0;
	}
	dis[s] = 0; f[s] = 1; q.push ( s );
	while ( q.size () ) {
		k = q.front (); q.pop(); f[k] = 0;
		for ( node *j = g[k] ; j ; j = j -> next )
			if ( j -> f && dis[j->v] > dis[k] + j -> c ) {
				dis[j->v] = dis[k] + j -> c;
				from[j->v] = j;
				if ( f[j->v] == 0 ) q.push( j -> v );
				f[j->v] = 1; 
			}
	}
	if ( dis[t] == 99999999 ) return false;
	return true;
}
int find () {
	int i , f = 9999999;
	for ( i = t ; i != s ; i = from[i] -> rev -> v ) f = min ( f , from[i] -> f );
	for ( i = t ; i != s ; i = from[i] -> rev -> v ) from[i] -> f -= f , from[i] -> rev -> f += f;
	return f * dis[t];
}
int dinic () {
	int ans = 0;
	while ( spfa () == true ) ans += find ();
	return ans;
}
int check ( int mid ) {
	int i , j , sum = 0;
	clear ();
	s = 1; t = 1 + n + n + 1;
	for ( i = 1 ; i <= n ; i++ ) {
		for ( j = 1 ; j <= n ; j++ ) {
			add ( 1 + i , 1 + n + j , 9999999 , abs(i-j) );
		}
	}
	for ( i = 1 ; i <= n ; i++ ) {
		add ( 1 , 1 + i , x[i] , 0 );
		add ( 1 + n + i , t , mid , 0 );
		sum += x[i];
	}
	if ( n * mid < sum ) return 0;
	if ( dinic () <= b ) return 1;
	return 0;
}
void work () {
	int i , l , r , mid;
	scanf ( "%d%d%d" , &d , &b , &m );
	for ( i = 1 ; i <= m ; i++ ) {
		scanf ( "%d" , &a[i] );
	}
	a[0] = 0; a[m+1] = d;
	sort ( a + 1 , a + m + 1 );
	for ( i = m + 1 ; i >= 1 ; i-- ) {
		x[i] = a[i] - a[i-1];
	}
	n = m + 1;
	l = 1; r = d + 1;
	while ( l < r - 1 ) {
		mid = (l+r)/2;
		if ( check ( mid ) == 1 ) r = mid;
		else l = mid;
	}
	if ( check ( l ) == 1 ) printf ( "%d\n" , l );
	else printf ( "%d\n" , r );
}
int main () {
	work ();
	return 0;
}
