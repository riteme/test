#include <stdio.h>
#include <algorithm>
#include <queue>
#include <cctype>
 
using namespace std;
 
const int maxn = 210000;
 
 
#define BUFFERSIZE 65536
static char buf[BUFFERSIZE];
static size_t pos = BUFFERSIZE;
 
inline void getc(char &c) {
    if (pos == BUFFERSIZE) {
        pos = 0;
        fread(buf, 1, BUFFERSIZE, stdin);
    }
    c = buf[pos++];
}
 
template <typename T>
inline void read(T &x) {
    x = 0;
    char c;
    do getc(c); while (!isdigit(c));
    do {
        x = x * 10 + (c - '0');
        getc(c);
    } while (isdigit(c));
}
 
 
 
 
struct node {
	int pos , kind , i , r;
} s[maxn*2];
struct col {
	int r , col;
};
bool operator < ( col x1 , col x2 ) {
	if ( x1.r == x2.r ) return x1.col < x2.col;
	return x1.r > x2.r;
}
int n , k;
int l[maxn] , r[maxn];
priority_queue < col > q;
int out[maxn];
int ans;
bool cmp ( node x1 , node x2 ) {
	if ( x1.pos == x2.pos && x1.kind == x2.kind ) return x1.r < x2.r;
	if ( x1.pos == x2.pos ) return x1.kind < x2.kind;
	return x1.pos < x2.pos;
}
void clear () {
	while ( q.size() ) q.pop();
	ans = 0;
	for ( int i = 1 ; i <= n ; i++ ) out[i] = 0;
}
int st[100],top;
void write(int x)
{
	if(!x)putchar('0');
	else {
		top = 0;
		while ( x ) {
			st[++top] = x % 10;
			x =x / 10;
		}
		for ( int i = top ; i >= 1 ; i-- ) putchar ( st[i] + '0' );
	}
}
void work () {
	int i;
	col tmp;
	//scanf ( "%d%d" , &n , &k );
	read(n);read(k);
	clear ();
	for ( i = 1 ; i <= n ; i++ ) {
		//scanf ( "%d%d" , &l[i] , &r[i] );
		read(l[i]);read(r[i]);
		s[i*2-1].pos = l[i]; s[i*2-1].kind = 1; s[i*2-1].i = i; s[i*2-1].r = r[i];
		s[i*2].pos = r[i]; s[i*2].kind = 0; s[i*2].i = 0; s[i*2].r = 0;
	}
	sort ( s + 1 , s + 1 + n * 2 , cmp );
	for ( i = 1 ; i <= k ; i++ ) {
		tmp.r = -1;
		tmp.col = i;
		q.push(tmp);
	}
	ans = 0;
	for ( i = 1 ; i <= n*2 ; i++ ) {
		if ( q.top().r >= s[i].pos ) {
			ans += s[i].pos - s[i-1].pos;
		}
		//printf ( "%d %d %d %d\n" , q.top().r,q.top().col , i , s[i].pos );
		if ( s[i].kind == 1 ) {
			out[s[i].i] = q.top().col;
			if ( s[i].r > q.top().r) {
				tmp = q.top(); q.pop();
				tmp.r = max ( tmp.r , s[i].r );
				q.push(tmp);
			}
		}
	}
	//printf ( "%d\n" , ans );
	write(ans);puts("");
	for ( i = 1 ; i <= n ; i++ ) {
		write(out[i]);
		if ( i==n ) puts("");
		else putchar(' ');
	}
}
int main () {
	int t;
	read(t);
	//scanf ( "%d" , &t );
	while ( t-- ) work ();
	return 0;
}
