#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;

//2x-1:flip, 2x:not flip for at most one
//output: reverse them
struct node {
	int v;
	node *next;
} pool[12100000] , *g[6110000] , *g1[6100000];
int top , tot;
int n , m;
int a[520000];
int dfn[3100000] , low[3100000] , index;
int col[3100000] , color;
int ord[3100000] , indexord;
int in[3100000];
int ins[3100000] , st[3100000] , tops;
int ans[310000] , cnt;
void add ( int u , int v ) {
	node *tmp = &pool[++top];
	tmp -> v = v; tmp -> next = g[u]; g[u] = tmp;
}
void add1 ( int u , int v ) {
	node *tmp = &pool[++top];
	tmp -> v = v; tmp -> next = g1[u]; g1[u] = tmp;
}
void tarjan ( int i ) {
	dfn[i] = low[i] = ++index;
	ins[i] = 1;
	st[++tops] = i;
	for ( node *j = g[i] ; j ; j = j -> next ) {
		if ( !dfn[j->v] ) {
			tarjan ( j -> v );
			low[i] = min ( low[i] , low[j->v] );
		}
		else if ( ins[j->v] ) low[i] = min ( low[i] , dfn[j->v] );
	}
	if ( low[i] == dfn[i] ) {
		color++;
		while ( st[tops] != i ) {
			col[st[tops]] = color;
			ins[st[tops]] = 0;
			tops--;
		}
		col[i] = color;
		ins[i] = 0;
		tops--;
	}
}
void solve () {
	int i , k;
	queue < int > q;
	for ( i = 1 ; i <= tot ; i++ ) {
		if ( !dfn[i] ) tarjan ( i );
	}
	for ( i = 1 ; i <= tot ; i++ ) {
		for ( node *j = g[i] ; j ; j = j -> next ) {
			if ( col[i] != col[j->v] ) {
				add1 ( col[i] , col[j->v] );
				in[col[j->v]]++;
			}
		}
	}
	for ( i = 1 ; i <= n ; i++ ) {
		if ( col[i*2-1] == col[i*2] ) {
			printf ( "No\n" );
			exit (0);
		}
	}
	for ( i = 1 ; i <= color ; i++ ) {
		if ( in[i] == 0 ) q.push ( i );
	}
	while ( q.size () ) {
		k = q.front (); q.pop ();
		ord[k] = ++indexord;
		for ( node *j = g1[k] ; j ; j = j -> next ) {
			in[j->v]--;
			if ( in[j->v] == 0 ) q.push ( j -> v );
		}
	}
	for ( i = 1 ; i <= n ; i++ ) {
		if ( ord[col[i*2]] > ord[col[i*2-1]] ) {
			ans[++cnt] = i;
		}
	}
}
void work () {
	int i , j , k , flag , del;
	scanf ( "%d%d" , &n , &m );
	tot = n * 2;
	for ( i = 1 ; i <= m ; i++ ) {
		scanf ( "%d" , &k );
		flag = 0;
		for ( j = 1 ; j <= k ; j++ ) {
			scanf ( "%d" , &a[j] );
			if ( a[j] != a[1] ) flag = 1;
		}
		if ( flag == 0 ) {
			if ( a[1] < 0 ) {
				add ( 2 * abs(a[1]) - 1 , 2 * abs(a[1]) );
			}
			else {
				add ( 2 * abs(a[1]) , 2 * abs(a[1]) - 1 );
			}
		}
		else {
			for ( j = 1 ; j <= k ; j++ ) {
				del = 0;
				if ( a[j] < 0 ) {
					del = 1;
				}
				if ( j != 1 ) add ( 2 * abs(a[j]) - del , tot + j - 1 );
				if ( j != k ) add ( 2 * abs(a[j]) - del , tot + k + j + 1 );
				add ( tot + j , 2 * abs(a[j]) - (1-del) );
				add ( tot + k + j , 2 * abs(a[j]) - (1-del) );
				if ( j != 1 ) {
					add ( tot + j , tot + j - 1 );
				}
				if ( j != k ) {
					add ( tot + k + j , tot + k + j + 1 );
				}
			}
			tot += 2 * k;
		}
	}
	solve ();
	printf ( "Yes\n" );
	printf ( "%d\n" , cnt );
	for ( i = 1 ; i <= cnt ; i++ ) {
		//printf ( "%d%c" , ans[i] , i==cnt?'\n':' ' );
		printf ( "%d\n" , ans[i] );
	}
}
int main () {
	work ();
	return 0;
}
