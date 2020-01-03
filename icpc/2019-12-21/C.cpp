
/**
 * title: 最小圆覆盖
 * category: 计算几何
 * description: /dev/null
 */

#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

#define T 4000

#define ACM_BEGIN
const int maxn = 200020;
struct point {
  double x , y;
} a[maxn] , c , tmp1 , tmp2;
int n;
double r;
double tmp;
double dis ( point x1 , point x2 ) {return sqrt ( (x1.x-x2.x)*(x1.x-x2.x) + (x1.y-x2.y)*(x1.y-x2.y) );}
double det ( point x1 , point x2 , point x3 ) {return (x2.x-x1.x) * (x3.y-x1.y) - (x3.x-x1.x) * (x2.y-x1.y);}
point getcen ( point x1 , point x2 , point x3 ) {
  double A , B , C , D , E , F;point ret;
  if ( x1.x == x2.x ) A = 0.0, B = 1.0, C = (x1.y+x2.y)/2.0;
  else {
    A = 1.0/((x1.y-x2.y) / (x1.x-x2.x));B = 1.0;
    C = -(x1.y+x2.y)/2.0 - A * (x1.x+x2.x)/2.0;
  }
  if ( x1.x == x3.x ) D = 0.0, E = 1.0, F = (x1.y+x3.y)/2.0;
  else {
    D = 1.0/((x1.y-x3.y) / (x1.x-x3.x));E = 1.0;
    F = -(x1.y+x3.y)/2.0 - D * (x1.x+x3.x)/2.0;
  }
  ret.x = (B * F - C * E) / (A * E - B * D);
  ret.y = (A * F - C * D) / (B * D - A * E);
  return ret;
}
void work () {
  int i , j , k;
  srand(67890);
  int m;
  scanf ( "%d" , &m );

  n = 0;
  for (int i = 1; i <= m; i++) {
      point p;
      double r;
      scanf("%lf%lf%lf", &p.x, &p.y, &r);
      double d = 2 * M_PI / T;
      double t = 0;
      for (int j = 0; j < T; j++) {
          a[++n] = {
              p.x + r * cos(t),
              p.y + r * sin(t)
            };
          t += d;
      }
  }

  random_shuffle ( a + 1 , a + 1 + n );
  if ( n == 2 ) {
    printf ( "%.3lf\n" , dis ( a[1] , a[2] ) / 2.0 );
    return ;
  }
  c.x = a[1].x;c.y = a[1].y;r = 0.0;
  for ( i = 2 ; i <= n ; i++ ) {
    if ( dis ( c , a[i] ) - r > 1e-9 ) {
      c.x = a[i].x;c.y = a[i].y;r = 0.0;
      for ( j = 1 ; j < i ; j++ ) {
        if ( dis ( c , a[j] ) - r > 1e-9 ) {
          c.x = (a[i].x + a[j].x) / 2.0;
          c.y = (a[i].y + a[j].y) / 2.0;
          r = dis ( a[i] , a[j] ) / 2.0;
          tmp = r; tmp1 = c;
          for ( k = 1 ; k <= j - 1 ; k++ ) {
            if ( dis ( tmp1 , a[k] ) - tmp > 1e-9 ) {
              if ( fabs(det ( a[i] , a[j] , a[k] )) < 1e-9 ) continue;
              tmp2 = getcen ( a[i] , a[j] , a[k] );
              tmp = dis ( tmp2 , a[i] );
              tmp1 = tmp2;
          }}
          c = tmp1; r = tmp;
  }}}}
  printf ( "%.8lf\n" , r );
}
#define ACM_END
int main () {
  work ();
  return 0;
}
