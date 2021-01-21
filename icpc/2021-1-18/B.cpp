#include <stdio.h>
#include <algorithm>
#include <set>

using namespace std;

struct node {
	int c;
	int lc , ln , rc , rn , mx;
	int siz;
	int fa , ch[3];
} p[210000];
int n , q;
int c[120000];
multiset < int > ans;
void output () {
	int i;
	for ( i = 1 ; i <= n + 2 ; i++ ) {
		printf ( "i%d l%d r%d fa%d lc%d ln%d rn%d rn%d mx%d siz%d\n" , i , p[i].ch[0] , p[i].ch[1] , p[i].fa , p[i].lc , p[i].ln , p[i].rc , p[i].rn , p[i].mx , p[i].siz );
	}
}
void update ( int x ) {
	int lc , ln , rc , rn , mx;
	p[x].siz = 1;
	p[x].lc = p[x].rc = p[x].c;
	p[x].ln = p[x].rn = p[x].mx = 1;
	if ( p[x].ch[0] ) {
		lc = p[p[x].ch[0]].lc;
		rc = p[x].rc;
		mx = max ( p[x].mx , max ( p[p[x].ch[0]].mx , (p[x].lc==p[p[x].ch[0]].rc?p[x].ln+p[p[x].ch[0]].rn:0) ) );
		ln = p[p[x].ch[0]].ln;
		if ( p[p[x].ch[0]].ln == p[p[x].ch[0]].siz && p[x].lc == p[p[x].ch[0]].lc ) {
			ln += p[x].ln;
		}
		rn = p[x].rn;
		if ( p[x].rn == p[x].siz && p[x].rc == p[p[x].ch[0]].rc ) {
			rn += p[p[x].ch[0]].rn;
		}
		p[x].lc = lc;
		p[x].ln = ln;
		p[x].rc = rc;
		p[x].rn = rn;
		p[x].mx = mx;
		p[x].siz += p[p[x].ch[0]].siz;
	}
	if ( p[x].ch[1] ) {
		lc = p[x].lc;
		rc = p[p[x].ch[1]].rc;
		mx = max ( p[x].mx , max ( p[p[x].ch[1]].mx , (p[x].rc==p[p[x].ch[1]].lc?p[x].rn+p[p[x].ch[1]].ln:0) ) );
		ln = p[x].ln;
		if ( p[x].ln == p[x].siz && p[x].lc == p[p[x].ch[1]].lc ) {
			ln += p[p[x].ch[1]].ln;
		}
		rn = p[p[x].ch[1]].rn;
		if ( p[p[x].ch[1]].rn == p[p[x].ch[1]].siz && p[x].rc == p[p[x].ch[1]].rc ) {
			rn += p[x].rn;
		}
		p[x].lc = lc;
		p[x].ln = ln;
		p[x].rc = rc;
		p[x].rn = rn;
		p[x].mx = mx;
		p[x].siz += p[p[x].ch[1]].siz;
	}
}
void rotate ( int x , int kind ) {
	int y = p[x].fa;
	if ( p[y].fa > 0 ) p[p[y].fa].ch[y==p[p[y].fa].ch[1]] = x;
	p[x].fa = p[y].fa;
	if ( p[x].ch[kind^1] ) p[p[x].ch[kind^1]].fa = y;
	p[y].ch[kind] = p[x].ch[kind^1];
	p[y].fa = x;
	p[x].ch[kind^1] = y;
	update ( y ); update ( x );
}
void splay ( int x , int fa ) {
	for ( ; p[x].fa != fa ; rotate ( x , x==p[p[x].fa].ch[1] ) ) {
		if ( p[p[x].fa].fa != fa && (x==p[p[x].fa].ch[1]) == (p[x].fa==p[p[p[x].fa].fa].ch[1]) )
			rotate ( p[x].fa , x==p[p[x].fa].ch[1] );
		//output ();
		//printf ( "\n" );
	}
}
int getleft ( int x ) {
	if ( p[x].ch[0] ) return getleft ( p[x].ch[0] );
	else return x;
}
int getright ( int x ) {
	//printf ( "right %d\n" , x );
	if ( p[x].ch[1] ) return getright ( p[x].ch[1] );
	else return x;
}
int getans ( int a ) {
	int ret = p[a].mx;
	if ( p[a].lc == p[a].rc ) {
		if ( p[a].ln != p[a].siz ) {
			ret = max ( ret , p[a].ln + p[a].rn );
		}
	}
	return ret;
}
int delans ( int a ) {
	int tmp = getans ( a );
	ans.erase ( ans.find ( tmp ) );
}
int upans ( int a , int f ) {
	int tmp = getans ( a );
	//printf ( "upans %d %d\n" , a , tmp );
	ans.insert ( tmp );
	if ( f == 1 ) {
		printf ( "%d %d\n" , tmp , *ans.rbegin () );
	}
}
void solver ( int a , int id ) {
	if ( p[a].ch[1] == 0 ) {
		p[a].ch[1] = id;
		p[id].fa = a;
		update ( a );
		upans ( a , 1 );
	}
	else {
		int b = getleft ( p[a].ch[1] );
		splay ( b , a );
		p[b].ch[0] = id;
		p[id].fa = b;
		update ( b );
		update ( a );
		upans ( a , 1 );
	}
}
void work () {
	int i , op , d , a , b;
	scanf ( "%d%d" , &n  , &q );
	for ( i = 1 ; i <= n ; i++ ) {
		scanf ( "%d" , &c[i] );
		p[i].c = c[i];
		if ( i != 1 ) {
			p[i].ch[0] = i - 1;
			p[i-1].fa = i;
		}
		update ( i );
	}
	//output ();
	upans ( n , 0 );
	for ( i = 1 ; i <= q ; i++ ) {
		scanf ( "%d%d" , &op , &d );
		p[n+i].c = d;
		update ( n + i );
		if ( op == 1 ) {
			scanf ( "%d%d" , &a , &b );
			splay ( a , 0 );
			//scanf ( "%d" , &op );
			delans ( a );
			if ( p[a].ch[0] == 0 ) {
				//printf ( "##\n" );
				if ( getright ( a ) == b ) {
					splay ( b , a );
					p[a].ch[0] = n + i;
					p[n+i].fa = a;
					update ( a );
					upans ( a , 1 );
				}
				else {
					solver ( a , n + i );
				}
			}
			else {
				if ( getright ( p[a].ch[0] ) == b ) {
					splay ( b , a );
					p[b].ch[1] = n+i;
					p[n+i].fa = b;
					update ( b );
					update ( a );
					upans ( a , 1 );
				}
				else {
					solver ( a , n + i );
				}
			}
		}
		else {
			scanf ( "%d" , &a );
			splay ( a , 0 );
			delans ( a );
			if ( p[a].ch[0] ) {
				b = getright ( p[a].ch[0] );
				splay ( b , 0 );
				splay ( a , b );
				if ( p[a].ch[1] ) {
					p[p[a].ch[1]].fa = b;
					p[b].ch[1] = p[a].ch[1];
				}
				update ( b );
				upans ( b , 0 );
				
				p[a].ch[0] = p[a].ch[1] = p[a].fa = 0;
				p[a].ch[1] = n+i;
				p[n+i].fa = a;
				update ( a );
				upans ( a , 1 );
			}
		}
		//output ();
	}
}
int main () {
	work ();
	return 0;
}
