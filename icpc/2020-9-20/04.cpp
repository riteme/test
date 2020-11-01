#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;

struct so {
    int x , i;
} s[1200000];
struct node {
    int v;
    node *next;
} pool[1200000] , *g[510000] , *rg[510000];
int top;
int n , m , R , B;
int w[510000];
int ok[510000] , out[510000] , poss[4][510000] , vis[510000];
int kind[510000];//kind[i]=0:need one edge, kind[i]=1:need all edges.
queue < int > q;
int ans[510000];
void clear () {
    int i;
    for ( i = 1 ; i <= n ; i++ ) {
        w[i] = ok[i] = out[i] = poss[0][i] = poss[1][i] = poss[2][i] = 0;
        ans[i] = kind[i] = vis[i] = 0;
        g[i] = rg[i] = NULL;
    }
    for ( i = 1 ; i <= top ; i++ ) pool[i] = pool[0];
    top = 0;
    while ( q.size () ) q.pop ();
}
bool cmp ( so x1 , so x2 ) {
    return x1.x < x2.x;
}
void add ( int u , int v ) {
    node *tmp = &pool[++top];
    tmp -> v = v; tmp -> next = g[u]; g[u] = tmp;
}
void addr ( int u , int v ) {
    node *tmp = &pool[++top];
    tmp -> v = v; tmp -> next = rg[u]; rg[u] = tmp;
}
void relax ( int k , int old , int now , int lim ) {
    for ( node *j = rg[k] ; j ; j = j -> next ) {
        if ( vis[j->v] ) {
            poss[old][j->v]--;
            poss[now][j->v]++;
            q.push ( j -> v );
        }
    }
}
void work () {
    int i , k , u , v , old , flag;
    scanf ( "%d%d%d%d" , &n , &m , &R , &B );
    for ( i = 1 ; i <= n ; i++ ) kind[i] = 0;
    for ( i = 1 ; i <= B ; i++ ) {
        scanf ( "%d" , &u );
        kind[u] = 1;
    }
    for ( i = 1 ; i <= n ; i++ ) {
        scanf ( "%d" , &w[i] );
        s[i].x = w[i];
        s[i].i = i;
    }
    for ( i = 1 ; i <= m ; i++ ) {
        scanf ( "%d%d" , &u , &v );
        add ( u , v ); addr ( v , u );
        out[u]++;
    }
    sort ( s + 1 , s + 1 + n , cmp );
    for ( i = 1 ; i <= n ; i++ ) {
        q.push ( s[i].i );
        while ( q.size () ) {
            k = q.front (); q.pop ();
            old = ok[k];
            flag = 0;
            if ( vis[k] == 0 ) {
                vis[k] = 1;
                for ( node *j = rg[k] ; j ; j = j -> next ) {
                    if ( k != j -> v && vis[j->v] ) poss[0][j->v]++;
                }
                for ( node *j = g[k] ; j ; j = j -> next ) {
                    if ( vis[j->v] ) poss[ok[j->v]][k]++;
                }
                flag = 1;
            }
            if ( ok[k] == 0 && kind[k] == 0 && (poss[0][k]||poss[1][k]||poss[2][k]) ) ok[k] = 1;
            if ( ok[k] == 0 && kind[k] == 1 && poss[0][k] + poss[1][k] + poss[2][k] == out[k] ) ok[k] = 1;
            if ( kind[k] == 0 && (poss[2][k]||poss[1][k]) ) ok[k] = 2;
            if ( kind[k] == 1 && (poss[2][k]+poss[1][k]) == out[k] ) ok[k] = 2;
            if ( old != 2 && ok[k] == 2 ) {
                ans[k] = s[i].x;
            }
            if ( flag || old != ok[k] ) relax ( k , old , ok[k] , s[i].x );
            //printf ( "k=%d i=%d %d %d %d %d\n" , k , i , poss[0][4] , poss[1][4] , poss[2][4] , ok[4] );
        }
    }
    for ( i = 1 ; i <= n ; i++ ) {
        printf ( "%d%c" , ans[i] , i==n?'\n':' ' );
        //if ( ans[i] == 0 ) while ( 1 );
    }
    clear ();
}
int main () {
    //freopen ( "04.in" , "r" , stdin );
    int t;
    scanf ( "%d" , &t );
    for ( int _ = 1 ; _ <= t ; _++ ) {
        printf ( "Case #%d:\n" , _ );
        work ();
    }
    return 0;
}
