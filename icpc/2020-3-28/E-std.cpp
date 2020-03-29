#include <cstdio>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const long long  inf = -1LL<<60;

long long a[100010],b[100010];
int xa,xb,ya,yb;
int n;

int main()
{
    int i,j,k;
    long long max;
    while (scanf("%d",&n) != EOF)
    {
          max = inf;

          xa = xb = ya = yb = 0;
          for (i = 1; i <= n; i++)
          {
             scanf("%lld",&a[i]);
             if (a[i] <= 0)
                ya ++;
             else xa ++;
          }
          for (i = 1; i <= n; i++)
          {
              scanf("%lld",&b[i]);
              if (b[i] <= 0)
                 yb ++;
              else xb ++;
          }
          sort(a+1,a+1+n);
          sort(b+1,b+1+n);
          //a，b全为正
          if ((xa == n && xb == n) ||(xa == 0 && xb == 0))
          {
                  for (i = 1; i <= n; i++)
                      if (max < a[i]*b[n-i+1])
                         max = a[i]*b[n-i+1];
                  printf("%lld\n",max);
                  continue;
          }
          //a，b一正一负
          if ((xa == n && xb == 0) || (xa == 0 && xb == n))
          {
                  for (i = 1; i <= n; i++)
                      if (max < a[i]*b[i])
                         max = a[i]*b[i];
                  printf("%lld\n",max);
                  continue;
          }
          //a全为正
          if (xa == n)
          {
                 for (i = 1; i <= xb;i++)
                     if (max < a[i]*b[n-i+1])
                       max = a[i]*b[n-i+1];
                 printf("%lld\n",max);
                 continue;
          }
          //a全为负
          if (xa == 0)
          {
                 for (i = 1; i <= yb; i++)
                     if (max < a[n-i+1]*b[i])
                        max = a[n-i+1]*b[i];
                printf("%lld\n",max);
                continue;
          }
           //b全为正
          if (xb == n)
          {
                 for (i = 1; i <= xa;i++)
                     if (max < b[i]*a[n-i+1])
                       max = b[i]*a[n-i+1];
                 printf("%lld\n",max);
                 continue;
          }
          //b全为负
          if (xb == 0)
          {
                 for (i = 1; i <= ya; i++)
                     if (max < b[n-i+1]*a[i])
                        max = b[n-i+1]*a[i];
                printf("%lld\n",max);
                continue;
          }
          //a的正==b的负
          if (xa == yb)
          {
                 for (i = 1; i <= ya; i++)
                     if (max < a[i]*b[yb+i])
                        max = a[i]*b[yb+i];
                 for (i = 1; i <= yb; i++)
                     if(max < b[i]*a[ya+i])
                            max = b[i]*b[yb+i];
                 printf("%lld\n",max);
                 continue;
          }
          //a的正 》b的负，余下全为正
          if (xa > yb)
          {
                 for (i = ya+1,j = n - ya; i <= n-yb; i++,j--)
                     if (max <a[i]*b[j])
                        max = a[i]*b[j];
                 printf("%lld\n",max);
                 continue;
          }
          //a的正小于b的负，余下全为负
          if (xa < yb)
          {
                 for (i = xb+1,j = n- xb; i <= n - xa; i++,j--)
                     if (max < a[i]*b[j])
                        max = a[i]*b[j];
                 printf("%lld\n",max);
                 continue;
          }
    }
    return 0;
}