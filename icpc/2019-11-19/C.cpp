#include <stdio.h>
#include <algorithm>
#include <assert.h>
 
using namespace std;
 
//long long
struct frac {
	long long num , dom;
	frac (){num=dom=0;}
	frac ( long long a , long long b ) {
		num = a; dom = b;
	}
} tmp;
struct person {
	long long games , gamescore;
	long long matchs , matchscore;
	long long byes;
} p[120000];
long long n , m;
long long oppo[32000][30] , onum[120000];
long long ex[120000];
long long a[120];
void clear () {
	long long i;
	for ( i = 1 ; i <= n ; i++ ) {
		ex[i] = onum[i] = 0;
		p[i] = p[0];
	}
}
frac operator + ( frac x1 , frac x2 ) {
	long long t;
	frac y;
	y.num = x1.num*x2.dom+x1.dom*x2.num;
	assert ( x1.dom * x2.dom /x2.dom == x1.dom);
	y.dom = x1.dom*x2.dom;
	t = __gcd(y.num,y.dom);
	y.num /= t; y.dom /= t;
	return y;
}
frac getgw ( long long j ) {
	long long t;
	frac ret;
	ret.num = p[j].gamescore + p[j].byes * 6;
	ret.dom = p[j].games * 3 + p[j].byes * 6;
	if ( ret.num * 3 <= ret.dom ) {
		ret.num = 1; ret.dom = 3;
	}
	t = __gcd(ret.num,ret.dom);
	ret.num /= t; ret.dom /= t;
	return ret;
}
frac getmw ( long long j ) {
	long long t;
	frac ret;
	ret.num = p[j].matchscore + p[j].byes * 3;
	ret.dom = p[j].matchs * 3 + p[j].byes * 3;
	if ( ret.num * 3 <= ret.dom ) {
		ret.num = 1; ret.dom = 3;
	}
	t = __gcd(ret.num,ret.dom);
	ret.num /= t; ret.dom /= t;
	return ret;
}
frac getomw ( long long i ) {
	long long j , now , t;
	frac ret , th;
	ret.num = 0; ret.dom = 1;
	if ( onum[i] == 0 ) return frac(1,3);
	for ( j = 1 ; j <= onum[i] ; j++ ) {
		now = oppo[i][j];
		th = getmw ( now );
		ret = ret + th;
	}
	ret.dom = ret.dom * onum[i];
	t = __gcd(ret.num,ret.dom);
	ret.num /= t; ret.dom /= t;
	return ret;
}
frac getogw ( long long i ) {
	long long j , now , t;
	frac ret , th;
	ret.num = 0; ret.dom = 1;
	if ( onum[i] == 0 ) return frac(1,3);
	for ( j = 1 ; j <= onum[i] ; j++ ) {
		now = oppo[i][j];
		th = getgw ( now );
		ret = ret + th;
	}
	ret.dom = ret.dom * onum[i];
	t = __gcd(ret.num,ret.dom);
	ret.num /= t; ret.dom /= t;
	return ret;
}
void output ( frac x ) {
	long long t = __gcd(x.num,x.dom);
	printf ( "%lld/%lld" , x.num/t , x.dom/t );
}
void work () {
	long long i , j , p1 , p2 , w1 , w2 , d , x , y;
	scanf ( "%lld%lld" , &n , &m );
	for ( i = 1 ; i <= m ; i++ ) {
		scanf ( "%lld" , &a[i] );
	}
	for ( i = 1 ; i <= m ; i++ ) {
		printf ( "Round %lld\n" , i );
		for ( j = 1 ; j <= n ; j++ ) {
			ex[j] = 0;
		}
		for ( j = 1 ; j <= a[i] ; j++ ) {
			scanf ( "%lld%lld%lld%lld%lld" , &p1 , &p2 , &w1 , &w2 , &d );
			ex[p1] = ex[p2] = 1;
			p[p1].games += w1 + w2 + d;
			p[p1].gamescore += w1 * 3 + d;
			p[p1].matchs ++;
			if ( w1 > w2 ) p[p1].matchscore += 3;
			if ( w1 == w2 ) p[p1].matchscore += 1;
			p[p2].games += w1 + w2 + d;
			p[p2].gamescore += w2 * 3 + d;
			p[p2].matchs ++;
			if ( w1 < w2 ) p[p2].matchscore += 3;
			if ( w1 == w2 ) p[p2].matchscore += 1;
			oppo[p1][++onum[p1]] = p2;
			oppo[p2][++onum[p2]] = p1;
		}
		//for ( int k = 1 ; k <= n ; k++ ) printf ( "%lld %lld %lld %lld %lld\n" , p[k].byes,p[k].games,p[k].gamescore,p[k].matchs,p[k].matchscore);
		//printf ( "\n" );
		/*for ( j = 1 ; j <= n ; j++ ) {
			tmp = getmw ( j );
			printf ( "MW %lld " , j );
			output ( tmp );
			printf ( "\n" );
		}*/
		for ( j = 1 ; j <= n ; j++ ) {
			if ( !ex[j] ) {
				p[j].byes++;
			}
		}
		for ( j = 1 ; j <= n ; j++ ) {
			printf ( "%lld " , p[j].matchscore + 3 * p[j].byes );
			tmp = getomw ( j );
			output ( tmp );
			printf ( " " );
			tmp = getgw ( j );
			output ( tmp );
			printf ( " " );
			tmp = getogw ( j );
			output ( tmp );
			printf ( "\n" );
		}
	}
	clear ();
}
int main () {
	int t;
	scanf ( "%d" , &t );
	while ( t-- ) work ();
	return 0;
}
