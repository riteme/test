#include <stdio.h>
#include <algorithm>
 
using namespace std;
 
long long n;
long long a[510000];
long long le[410000] , ri[410000];
long long st[410000] , tops;
long long s[410000];
long long ans;
void clear () {
    long long i;
    ans = 0;
    tops = 0;
    for ( i = 1 ; i <= n ; i++ ) {
        le[i] = ri[i] = 0;
        s[i] = 0;
    }
}
long long getl ( long long now , long long right , long long left , long long r ) {
    long long mid , l = left;
    if ( s[right] - s[l-1] < 2 * now ) return 0;
    if ( s[right] - s[r-1] >= 2 * now ) return (r-l+1);
    while ( l < r - 1 ) {
        mid = (l+r)/2;
        if ( s[right] - s[mid-1] < 2 * now ) r = mid;
        else l = mid;
    }
    return l - left + 1;
}
long long getr ( long long now , long long left , long long l , long long right ) {
    long long mid , r = right;
    if ( s[r] - s[left-1] < 2 * now ) return 0;
    if ( s[l] - s[left-1] >= 2 * now ) return (r-l+1);
    while ( l < r - 1 ) {
        mid = (l+r)/2;
        if ( s[mid] - s[left-1] < 2 * now ) l = mid;
        else r = mid;
    }
    return right - r + 1;
}
void work () {
    long long i , j;
    scanf ( "%lld" , &n );
    clear ();
    for ( i = 1 ; i <= n ; i++ ) {
        scanf ( "%lld" , &a[i] );
        s[i] = s[i-1] + a[i];
    }
    for ( i = 1 ; i <= n ; i++ ) {
        while ( tops && a[st[tops]] < a[i] ) {
            ri[st[tops]] = i;
            tops--;
        }
        le[i] = st[tops];
        st[++tops] = i;
    }
    for ( i = 1 ; i <= tops ; i++ ) {
        ri[st[i]] = n + 1;
    }
    for ( i = 1 ; i <= n ; i++ ) {
        le[i]++;
        ri[i]--;
    }
    /*for ( i = 1 ; i <= n ; i++ ) {
        printf ( "%lld " , le[i] );
    }
    printf ( "\n" );
    for ( i = 1 ; i <= n ; i++ ) {
        printf ( "%lld " , ri[i] );
    }
    printf ( "\n" );*/
    for ( i = 1 ; i <= n ; i++ ) {
        if ( ri[i] - i <= i - le[i] ) {
            for ( j = i ; j <= ri[i] ; j++ ) {
                ans += getl ( a[i] , j , le[i] , i );
            }
        }
        else {
            for ( j = le[i] ; j <= i ; j++ ) {
                ans += getr ( a[i] , j , i , ri[i] );
            }
        }
    }
    printf ( "%lld\n" , ans );
}
int main () {
    int t;
    scanf ( "%d" , &t );
    while ( t-- ) work ();
    return 0;
}
