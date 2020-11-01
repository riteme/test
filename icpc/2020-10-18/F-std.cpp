#include <stdio.h>
#include <algorithm>

using namespace std;

struct tree {
    int u , v , c;
    tree *next;
} poolt[210000] , *g[210000];
struct node {
    int l , r , mn;
    node *ll , *rr;
} pooln[210000] , *t;
struct edge {
    int u , v , c , f;
} e[210000];
struct so {
    int v , c;
} s[220000];
int topt , topn;
int n , m;
int fa[210000] , siz[120000] , dep[120000] , son[120000] , top[120000] , w[1200000] , d[120000] , index;
int cntdel;
int noans[210000] , ans[120000] , tot;
bool cmp ( edge x1 , edge x2 ) {
    return x1.c > x2.c;
}
bool cmp2 ( so x1 , so x2 ) {
    return x1.c < x2.c;
}
void add ( int u , int v , int c ) {
    tree *tmp = &poolt[++topt];
    tmp -> v = v; tmp -> c = c; tmp -> next = g[u]; g[u] = tmp;
}
void dfs1 ( int i , int from ) {
    siz[i] = 1;
    for ( tree *j = g[i] ; j ; j = j -> next ) if ( j -> v != from ) {
        dep[j->v] = dep[i] + 1;
        fa[j->v] = i;
        dfs1 ( j -> v , i );
        siz[i] += siz[j->v];
        if ( siz[j->v] > siz[son[i]] ) son[i] = j -> v;
    }
}
void dfs2 ( int i , int from ) {
    w[i] = ++index;
    if ( son[i] ) {
        top[son[i]] = top[i];
        dfs2 ( son[i] , i );
    }
    for ( tree *j = g[i] ; j ; j = j -> next ) if ( j -> v != from && j -> v != son[i] ) {
        top[j->v] = j -> v;
        dfs2 ( j -> v , i );
    }
    for ( tree *j = g[i] ; j ; j = j -> next ) if ( j -> v != from ) {
        d[w[j->v]] = j -> c;
    }
}
void buildtree ( node *id , int l , int r ) {
    id -> l = l; id -> r = r;
    if ( l== r ) {
        id -> mn = d[l];
        return ;
    }
    int mid = (l+r)/2;
    id -> ll = &pooln[++topn];
    id -> rr = &pooln[++topn];
    buildtree ( id -> ll , l , mid );
    buildtree ( id -> rr , mid + 1 ,r );
    id -> mn = min ( id -> ll -> mn , id -> rr -> mn );
}
int querytree ( node *id , int l , int r ) {
    if ( id -> l == l && id -> r == r ) return id -> mn;
    int mid = (id->l+id->r)/2;
    if ( r <= mid ) return querytree ( id -> ll , l ,r );
    else {
        if ( l > mid ) return querytree ( id -> rr , l , r );
        else return min ( querytree ( id -> ll , l , mid ) , querytree ( id -> rr , mid + 1 ,r ) );
    }
}
int query ( int u , int v ) {
    int ret = 2147483647;
    while ( top[u] != top[v] ) {
        if ( dep[top[u]] < dep[top[v]] ) swap ( u , v );
        ret = min ( ret , querytree ( t , w[top[u]] , w[u] ) );
        u =fa[top[u]];
    }
    if ( u == v ) return ret;
    if ( dep[u] < dep[v] ) swap ( u , v );
    ret = min ( ret , querytree ( t , w[son[v]] , w[u] ) );
    return ret;
}
void getans ( int i , int from , int c ) {
    if ( noans[i] ) return ;
    noans[i] = 1;
    for ( tree *j = g[i] ; j ; j = j -> next ) if ( j -> v != from ) {
        if ( j -> c > c ) {
            getans ( j -> v , i , c );
        }
    }
}
void work () {
    int i;
    scanf ( "%d%d" , &n , &m );
    for ( i = 1 ; i <= m ; i++ ) {
        scanf ( "%d%d%d%d" , &e[i].f , &e[i].u , &e[i].v , &e[i].c );
        if ( e[i].f == 1 ) {
            add ( e[i].u , e[i].v , e[i].c );
            add ( e[i].v , e[i].u , e[i].c );
        }
    }
    dep[1] = 1;
    dfs1 ( 1 , -1 );
    top[1] = 1;
    dfs2 ( 1 , -1 );
    t = &pooln[++topn];
    buildtree ( t , 1 , n );
    /*for ( i = 1 ; i <= m ; i++ ) {
        if ( e[i].f == 0 ) change ( e[i].u , e[i].v , e[i].c );
    }
    for ( i = 1 ; i <= m ; i++ ) {
        if ( dep[e[i].u] < dep[e[i].v] ) swap ( e[i].u , e[i].v );
        if ( querytree ( t , w[e[i].u] ) > e[i].c ) {
            todel[++cntdel] = i;
        }
    }*/
    sort ( e + 1 , e + 1 + m , cmp );
    for ( i = 1 ; i <= m ; i++ ) {
        if ( e[i].u == e[i].v ) continue;
        int tmp = query ( e[i].u , e[i].v );
        if ( e[i].f == 0 && e[i].c > query ( e[i].u , e[i].v ) ) {
            //printf ( "%d %d %d\n" , e[todel[i]].u , e[todel[i]].v , e[todel[i]].c );
            s[++cntdel].v = e[i].v; s[cntdel].c = tmp;
            s[++cntdel].v = e[i].u; s[cntdel].c = tmp;
        }
    }
    sort ( s + 1 , s + 1 + cntdel , cmp2 );
    for ( i = 1 ; i <= cntdel ; i++ ) {
        getans ( s[i].v , -1 , s[i].c );
    }
    for ( i = 1 ; i <= n ; i++ ) {
        if ( noans[i] == 0 ) ans[++tot] = i;
    }
    printf ( "%d\n" , tot );
    for ( i = 1 ; i <= tot ; i++ ) {
        printf ( "%d%c" , ans[i] , i==tot?'\n':' ' );
    }
}
int main () {
    work ();
    return 0;
}
