#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using namespace std;
inline long long read()
{
	long long x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
long long cas;
long long HP[2],ATK[2];
long long dmg[2],cnt[2];
char ans[2][100010];
bool check()
{
	for(long long i=1;i<=max(cnt[0],cnt[1]);i++)
		if(ans[0][i]!=ans[1][i])return ans[0][i]>ans[1][i];
	return 0;
}
int main()
{
	cas=read();
	while(cas--)
	{
		memset(dmg,0,sizeof(dmg));
		memset(cnt,0,sizeof(cnt));
		HP[0]=read(),HP[1]=read(),ATK[0]=read(),ATK[1]=read();
		long long tmp=0;long long t_id;
		while(tmp<HP[0])ans[0][++cnt[0]]='A',dmg[0]+=ATK[0]+ATK[1],tmp+=cnt[0];
		if(tmp>HP[0])ans[0][tmp-HP[0]]='B';tmp-=HP[0];t_id=tmp;
		while(tmp<HP[1])ans[0][++cnt[0]]='B',dmg[0]+=ATK[1],tmp+=cnt[0];
		if(tmp-HP[1]>=t_id)ans[0][t_id]='A';
 
		tmp=0;long long txp=0;
		while(tmp<HP[1])ans[1][++cnt[1]]='B',dmg[1]+=ATK[0]+ATK[1],tmp+=cnt[1];
		tmp-=HP[1];
		long long v;
		for(v=1;txp<tmp;v++)ans[1][v]='A',txp+=v;v--;
		txp-=tmp;if(txp)ans[1][txp]='B';t_id=txp;
		while(tmp<HP[0])ans[1][++cnt[1]]='A',dmg[1]+=ATK[0],tmp+=cnt[1];
		tmp-=HP[0];
		if(t_id)
		{
			v=std::min(0ll+v,t_id+tmp);
			swap(ans[1][t_id],ans[1][v]);
		}
 
 
		long long t;		
		if(dmg[0]<dmg[1])t=0;  
		else if(dmg[0]>dmg[1])t=1;
		else t=check();
		printf("%lld ",dmg[t]);puts(ans[t]+1);
		for(long long k=0;k<2;k++)for(long long i=0;i<=cnt[k];i++)ans[k][i]=0;
	}
}
