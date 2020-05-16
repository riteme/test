#include<bits/stdc++.h>

using namespace std;

#define rep(i,j,n) for(int i=j;i<=n;i++)

char s[3000005],t[3000005];
int T;
const int mod = 1e9+7;

void print(int x)
{
    if(x>9)
    {
        print(x/10);
    }
    putchar(x%10+'0');
}

int main()
{
	//freopen ( "h.out" , "w" , stdout );
	scanf ( "%d" , &T );
    //cin>>T;
    //T = 1000000;
    assert(T <= 1000000);
    int sum = 0;
    while(T--)
    {
    	scanf ( "%s%s" , s , t );
        //cin>>s;
        /*for ( int i = 0 ; i < 2 ; i++ ) {
        	if ( i <= 80 ) s[i] = '0' + rand () % 2;
        	t[i] = '0' + rand () % 2;
        }*/
        //cin>>t;
        int lens=strlen(s)-1;
        int lent=strlen(t)-1;
        if(lens<lent)
        {
            swap(s,t);
            swap(lens,lent);
        }

        int temps=0,tempt=0;
        rep(i,0,lens-lent-1)
        {
            temps=(temps<<1)+s[i]-'0';
            if(temps>=mod)
                temps-=mod;
        }
        long long Lose=0, Draw=0, Win;
        rep(i,0,lent)
        {
            if((lent-i)%2==0)
            {
                Lose=(Lose + 1ll * (temps + (s[i+lens-lent]>'0'))* (tempt + (t[i]>'0'))) % mod;
                Draw=(Draw + 1ll * (temps + (s[i+lens-lent]>'0')) * tempt) %mod;
                Draw=(Draw + 1ll * temps * (tempt + (t[i]>'0'))) %mod;
            }
            temps=(temps<<1)+s[i+lens-lent]-'0';
            if(temps>=mod)
                temps-=mod;
            tempt=(tempt<<1)+t[i]-'0';
            if(tempt>=mod)
                tempt-=mod;
        }

        Win = 1ll * temps * tempt % mod;
        Win = (Win - Lose - Draw + mod + mod) % mod;
		print (Win);
        putchar(' ');
		print (Draw);
        putchar(' ');
		print (Lose);
        putchar('\n');
		//printf ( "%lld %lld %lld\n" , Win , Draw , Lose );
        //cout<<Win<<' '<<Draw<<' '<<Lose<<endl;
        sum += lens + lent;
        assert(sum <= 40000);

    }
}
