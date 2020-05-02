#include <stdio.h>
#include <algorithm>

using namespace std;

//long long
struct line {
	long long k , b;
};
struct node {
	long long l , r , cov;
	line t;
	node *ll , *rr;
} pool[420000] , *t;
long long top;
long long n;
long long a[210000];
long long l[210000] , r[210000];
long long st[210000] , tops;
long long ans;
void buildtree ( node *id , long long l , long long r ) {
	id -> l = l; id -> r = r;
	if ( l == r ) return ;
	long long mid = (l+r)/2;
	id -> ll = &pool[++top]; id -> rr = &pool[++top];
	buildtree ( id -> ll , l , mid ); buildtree ( id -> rr , mid + 1 , r );
}
long long geth ( line l , long long x ) {
	return l.k * x + l.b;
}
void add ( node *id , long long l , long long r , line x ) {
	long long mid = (id->l+id->r)/2;
	if ( id -> l == l && id -> r == r ) {
		if ( id -> cov == 0 ) {
			id -> cov = 1;
			id -> t = x;
		}
		else {
			long long x1 , x2 , x3 , t1 , t2 , t3;
			x1 = geth(x,l);x2=geth(x,mid);x3 = geth(x,r);
			t1 = geth (id->t,l);t2=geth(id->t,mid);t3 = geth(id->t,r);
			if ( t1 >= x1 && t3 >= x3 ) return ;
			if ( t1 <= x1 && t3 <= x3 ) {
				id -> t = x;
				return ;
			}
			if ( x2 >= t2 ) swap ( id -> t , x );
			if ( (t1>=x1) == (t2>=x2) ) {
				add ( id -> rr , mid + 1 , r , x );
			}
			else add ( id -> ll , l , mid , x );
		}
		return ;
	}
	if ( r <= mid ) add ( id -> ll , l , r , x );
	else {
		if ( l > mid ) add ( id -> rr , l , r , x );
		else {
			add ( id -> ll , l , mid , x );
			add ( id -> rr , mid + 1 , r , x );
		}
	}
}
long long query ( node *id , long long x ) {
	if ( id -> l == id -> r ) {
		if ( id -> cov == 1 ) return geth ( id -> t , x );
		return -1;
	}
	long long mid = (id->l+id->r)/2;
	long long tmp;
	if ( id -> cov == 1 ) tmp = geth ( id -> t , x );
	else tmp = -1;
	if ( x <= mid ) return max ( tmp , query ( id -> ll , x ) );
	else return max ( tmp , query ( id -> rr , x ) );
}
void work () {
	long long i;
	line k;
	scanf ( "%lld" , &n );
	for ( i = 1 ; i <= n ; i++ ) {
		scanf ( "%lld" , &a[i] );
	}
	t = &pool[++top];
	buildtree ( t , 1 , n );
	tops = 0;
	for ( i = n ; i >= 1 ; i-- ) {
		while ( tops && a[st[tops]] > a[i] ) {
			l[st[tops--]] = i;
		}
		st[++tops] = i;
	}
	tops = 0;
	for ( i = 1 ; i <= n ; i++ ) {
		while ( tops && a[st[tops]] > a[i] ) {
			r[st[tops--]] = i;
		}
		st[++tops] = i;
	}
	for ( i = 1 ; i <= n ; i++ ) {
		if ( r[i] == 0 ) r[i] = n + 1;
		//printf ( "%lld %lld\n" , l[i] , r[i] );
		k.k = a[i];
		k.b = (i-l[i]-i) * a[i];
		add ( t , i , r[i] - 1 , k );//i?
	}
	ans = 0;
	for ( i = 1 ; i <= n ; i++ ) {
		ans = max ( ans , query ( t , i ) );
		printf ( "%lld\n" , ans );
	}
}
int main () {
	work ();
	return 0;
}