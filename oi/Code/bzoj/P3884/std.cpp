#include <cstdio>  
#include <cstring>  
#include <iostream>  
#include <algorithm>  
#define M 10001000  
using namespace std;  
int phi[M],prime[1001001],tot;  
bool not_prime[M];  
int Phi(int x)  
{  
    int i,re=x;  
    for(i=2;i*i<=x;i++)  
        if(x%i==0)  
        {  
            re/=i;re*=i-1;  
            while(x%i==0)  
                x/=i;  
        }  
    if(x^1) re/=x,re*=x-1;  
    return re;  
}  
int Quick_Power(long long x,int y,int p)  
{  
    long long re=1;  
    while(y)  
    {  
        if(y&1) (re*=x)%=p;  
        (x*=x)%=p; y>>=1;  
    }  
    return re;  
}  
int Solve(int p)  
{  
    if(p==1) return 0;  
    int temp=0;  
    while(~p&1) p>>=1,++temp;  
    int phi_p=Phi(p);  
    int re=Solve(phi_p);  
    (re+=phi_p-temp%phi_p)%=phi_p;  
    re=Quick_Power(2,re,p)%p;  
    return re<<temp;  
}  
int main()  
{  
    int T,p;  
    for(cin>>T;T;T--)  
    {  
        scanf("%d",&p);  
        printf("%d\n",Solve(p));  
    }  
    return 0;  
}  
