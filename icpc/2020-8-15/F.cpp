#include <bits/stdc++.h>
#define vi vector <int>
#define pb push_back
#define mp make_pair
#define mod 998244353
#define rep(i,j,n) for(int i=j;i<=n;i++)
#define per(i,j,k) for(int i=(int)(j);i>=(int)(k);i--)
#pragma optimize(3)
using namespace std;

int T,n,m;
const int N=50000;
const int M=500;
const long double eps = 1e-8;
const long double PI = acosl(-1.0);
int sgn(long double x)
{
    if(fabs(x) < eps)return 0;
    if(x < 0)return -1;
    else return 1;
}
struct point
{
    long double x,y;
    point() {}
    point(long double _x,long double _y)
    {
        x = _x;
        y = _y;
    }
    point operator -(const point &b)const
    {
        return point(x - b.x,y - b.y);
    }
//叉积
    long double operator ^(const point &b)const
    {
        return x*b.y - y*b.x;
    }
//点积
    long double operator *(const point &b)const
    {
        return x*b.x + y*b.y;
    }
//绕原点旋转角度B（弧度值），后x,y的变化
    void transXY(long double B)
    {
        long double tx = x,ty = y;
        x = tx*cos(B) - ty*sin(B);
        y = tx*sin(B) + ty*cos(B);
    }
    void input()
    {
        scanf("%Lf%Lf",&x,&y);
    }
}a[N+5],b[M+5];

int check(point x,point y,point z,point a)
{
    bool temp1 = 1, temp0 = 0;
    bool temp = (sgn((x-a)^(y-a)) < 0);
    temp1 &= temp;
    temp0 |= temp;
    temp = (sgn((y-a)^(z-a)) < 0);
    temp1 &= temp;
    temp0 |= temp;
    temp = (sgn((z-a)^(x-a)) < 0);
    temp1 &= temp;
    temp0 |= temp;
    return (temp1 == temp0);
}
long double temp0,temp1,temp2,temp3,ans = 1e30;
long double u0[N+5],u1[N+5],u2[N+5],u3[N+5];
inline void update(long double x)
{
    long double tmp = ((temp3*x + temp2)*x + temp1)*x + temp0;
    if(tmp < ans) ans = tmp;
}

int main()
{
    ios::sync_with_stdio(0);
    scanf("%d",&T);
    rep(t,1,T)
    {
        scanf("%d",&n);
        rep(i,1,n)
        {
            a[i].input();
        }

ans = 1e40;temp0=temp1=temp2=temp3=0;
        rep(i,1,n)
        {
            long double sx = a[i].x*a[i].x;
            long double sy = a[i].x*a[i].y;
            temp0 += (u0[i] = sx*sy);
            temp1 += (u1[i] = -3*sx*a[i].y);
            temp2 += (u2[i] = 3*sy);
            temp3 += (u3[i] = -a[i].y);
        }
        rep(i,1,n)
        {
            temp0 -= 2 * u0[i];
            temp1 -= 2 * u1[i];
            temp2 -= 2 * u2[i];
            temp3 -= 2 * u3[i];

            update(a[i].x);

            long double A = 3*temp3;
            //if(A<0) continue;

            long double b = 2*temp2;
            if(fabs(A)<eps && b<eps) continue;

            long double c = temp1;
            if(fabs(A)<eps)
            {
                long double tx = -c/b;
                if(tx>a[i].x && tx<a[i+1].x)
                    update(tx);
                continue;
            }

            if(b*b<4*A*c) continue;
            long double tx = (-b+sqrt(b*b-4*A*c))/A/2;
            if(tx>a[i].x && tx<a[i+1].x) update(tx);
            tx = (-b-sqrt(b*b-4*A*c))/A/2;
            if(tx>a[i].x && tx<a[i+1].x) update(tx);
        }

        printf("Case #%d: %.0Lf\n",t,(long double)(ans));
    }
}
