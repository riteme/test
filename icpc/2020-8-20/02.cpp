#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;

struct edge {
    int u , v;
} e[12000] , ee[12000];
struct node {
    int v , f;
    node *next , *rev;
} pool[210000] , *g[120000];
int top;
int n , m;
int num , mnum;
int s , t;
int d[1200];
int lab[1200];
int level[120000];
void clear () {
    int i;
    for ( i = 1 ; i <= n ; i++ ) {
        d[i] = 0;
    }
}
void add ( int u , int v , int f ) {
    node *tmp1 = &pool[++top] , *tmp2 = &pool[++top];
    tmp1 -> v = v; tmp1 -> f = f; tmp1 -> next = g[u]; g[u] = tmp1; tmp1 -> rev = tmp2;
    tmp2 -> v = u; tmp2 -> f = 0; tmp2 -> next = g[v]; g[v] = tmp2; tmp2 -> rev = tmp1;
}
bool makelevel () {
    int i , k;
    queue < int > q;
    for ( i = 1 ; i <= t ; i++ ) level[i] = -1;
    level[s] = 1; q.push ( s );
    while ( q.size () ) {
        k = q.front (); q.pop ();
        for ( node *j = g[k] ; j ; j = j -> next )
            if ( j -> f && level[j->v] == -1 ) {
                level[j->v] = level[k] + 1;
                q.push ( j -> v );
                if ( j -> v == t ) return true;
            }
    }
    return false;
}
int find ( int k , int key ) {
    if ( k == t ) return key;
    int i = 0 , flow = 0;
    for ( node *j = g[k] ; j ; j = j -> next )
        if ( j -> f && level[j->v] == level[k] + 1 && flow < key ) {
            i = find ( j -> v , min ( key - flow , j -> f ) );
            j -> f -= i;
            j -> rev -> f += i;
            flow += i;
        }
    if ( flow == 0 ) level[k] = -1;
    return flow;
}
int dinic () {
    int ret = 0;
    while ( makelevel () == true ) ret += find ( s , 9999999 );
    //printf ( "dinic %d\n" , ret );
    return ret;
}
int test ( int x , int pos ) {
    int i , tot;
    for ( i = 1 ; i <= top ; i++ ) {
        pool[i] = pool[0];
    }
    for ( i = 1 ; i <= 1 + num + mnum + 1 ; i++ ) {
        g[i] = NULL;
    }
    top = 0;
    tot = mnum - x;
    for ( i = 1 ; i <= num ; i++ ) {
        if ( i != pos ) add ( 1 , 1 + i , x );
    }
    for ( i = 1 ; i <= mnum ; i++ ) {
        add ( 1 + ee[i].u , 1 + num + i , 9999999 );
        add ( 1 + ee[i].v , 1 + num + i , 9999999 );
        add ( 1 + num + i , 1 + num + mnum + 1 , 1 );
    }
    s = 1; t = 1 + num + mnum + 1;
    tot -= dinic ();
    //printf ( "%d %d\n" , x , tot );
    if ( tot <= -x ) return 1;
    return 0;
}
int check ( int x ) {
    int i;
    num = 0; mnum = 0;
    for ( i = 1 ; i <= n ; i++ ) {
        if ( d[i] > x ) {
            lab[i] = ++num;
        }
        else lab[i] = 0;
    }
    if ( num == 0 ) return 1;
    for ( i = 1 ; i <= m ; i++ ) {
        if ( lab[e[i].u] && lab[e[i].v] ) {
            ee[++mnum].u = lab[e[i].u];
            ee[mnum].v = lab[e[i].v];
        }
    }
    for ( i = 1 ; i <= num ; i++ ) {
        if ( test ( x , i ) == 0 ) return 0;
    }
    return 1;
}
void work () {
    int i , l , r , mid;
    scanf ( "%d%d" , &n , &m );
    for ( i = 1 ; i <= m ; i++ ) {
        scanf ( "%d%d" , &e[i].u , &e[i].v );
        d[e[i].u]++;
        d[e[i].v]++;
    }
    l = 0; r = 1000;
    while ( l < r - 1 ) {
        mid = (l+r)/2;
        if ( check ( mid ) ) r = mid;
        else l = mid;
    }
    printf ( "%d\n" , r );
    clear ();
}
int main () {
    int t;
    scanf ( "%d" , &t );
    while ( t-- ) work ();
    return 0;
}
