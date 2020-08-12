#include <stdio.h>
#include <algorithm>

using namespace std;

int n , m;
int a[50][50];
int ask22[50][50] , ask23[50][50] , ask32[50][50];
void dfs ( int x , int y ) {
	if ( y == 2 && x != 1 && x != n ) {
		if ( ask22[x-1][y-1] + ask22[x][y-1] - ask32[x-1][y-1] == 1 )
			a[x][y-1] = a[x][y];
		else a[x][y-1] = 1 - a[x][y];
	}
	if ( (y == m - 1 && x != 1 && x != n) || (x==2&&y!=m-1) ) {
		if ( ask22[x-1][y] + ask22[x][y] - ask32[x-1][y] == 1 )
			a[x][y+1] = a[x][y];
		else a[x][y+1] = 1 - a[x][y];
		if ( x == 2 && y != m - 1 ) dfs ( x , y + 1 );
	}
	if ( x == 2 ) {
		if ( ask22[x-1][y-1] + ask22[x-1][y] - ask23[x-1][y] == 1 )
			a[x-1][y] = a[x][y];
		else a[x-1][y] = 1 - a[x][y];
	}
	if ( ask22[x][y-1] + ask22[x][y] - ask23[x-1][y] == 1 )
		a[x+1][y] = a[x][y];
	else a[x+1][y] = 1 - a[x][y];
	if ( x != n ) {
		dfs ( x + 1 , y );
	}
}
void work () {
	int i , j;
	scanf ( "%d%d" , &n , &m );
	printf ( "? 1 1\n" );
	fflush(stdout);
	scanf ( "%d" , &a[1][1] );
	printf ( "? 1 %d\n" , m );
	fflush(stdout);
	scanf ( "%d" , &a[1][m] );
	printf ( "? %d 1\n" , n );
	fflush(stdout);
	scanf ( "%d" , &a[n][1] );
	printf ( "? %d %d\n" , n , m );
	fflush(stdout);
	scanf ( "%d" , &a[n][m] );
	for ( i = 1 ; i < n ; i++ ) {
		for ( j = 1 ; j < m ; j++ ) {
			printf ( "? %d %d %d %d\n" , i , j , i + 1 , j + 1 );
			fflush(stdout);
			scanf ( "%d" , &ask22[i][j] );
		}
	}
	for ( i = 1 ; i < n ; i++ ) {
		for ( j = 1 ; j < m - 1 ; j++ ) {
			printf ( "? %d %d %d %d\n" , i , j , i + 1 , j + 2 );
			fflush(stdout);
			scanf ( "%d" , &ask23[i][j] );
		}
	}
	for ( i = 1 ; i <= 1 ; i++ ) {
		for ( j = 1 ; j < m ; j++ ) {
			printf ( "? %d %d %d %d\n" , i , j , i + 2 , j + 1 );
			fflush(stdout);
			scanf ( "%d" , &ask32[i][j] );
		}
	}
	for ( i = 2 ; i < n - 1 ; i++ ) {
			j = 1;
			printf ( "? %d %d %d %d\n" , i , j , i + 2 , j + 1 );
			fflush(stdout);
			scanf ( "%d" , &ask32[i][j] );
			j = m - 1;
			printf ( "? %d %d %d %d\n" , i , j , i + 2 , j + 1 );
			fflush(stdout);
			scanf ( "%d" , &ask32[i][j] );
	}
	printf ( "? 2 2\n" );
	fflush(stdout);
	scanf ( "%d" , &a[2][2] );
	dfs ( 2 , 2 );
	printf ( "!\n" );
	for ( i = 1 ; i <= n ; i++ ) {
		for ( j =1 ; j <= m ; j++ ) {
			printf ( "%d" , a[i][j] );
		}
		printf ( "\n" );
	}
	fflush(stdout);
}
int main () {
	work ();
	return 0;
}
