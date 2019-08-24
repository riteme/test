#include<bits/stdc++.h>
#define pa pair<int,int>
#define CLR(a,x) memset(a,x,sizeof(a))
#define MP make_pair
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long double ld;
const int maxn=100000+100,maxm=5000000+100;

inline char gc(){
	return getchar();
	static const int maxs=1<<16;static char buf[maxs],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,maxs,stdin),p1==p2)?EOF:*p1++;
}
inline int rd(){
    int x=0;char c=gc();bool neg=0;
    while(c<'0'||c>'9'){if(c=='-') neg=1;c=gc();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+c-'0',c=gc();
    return neg?(~x+1):x;
}

int N,M,R,eg[maxm][3],egh[maxn],ect;
int ine[maxn],bel[maxn],tot,flag[maxn];

int main(){
    // freopen("dmst1.in","r",stdin);
    N=rd(),M=rd(),R=rd();
   	for(int i=1;i<=M;i++){
   		eg[i][0]=rd(),eg[i][1]=rd(),eg[i][2]=rd();
   	}
   	eg[0][2]=1e9;
   	int ans=0;
   	while(1){
   		CLR(ine,0);
   		for(int i=1;i<=M;i++){
   			int b=eg[i][1];if(eg[i][0]==b) continue;
   			if(b!=R&&eg[ine[b]][2]>eg[i][2]) ine[b]=i;
   		}
   		for(int i=1;i<=N;i++){
   			if(i!=R&&!ine[i]){puts("-1");return 0;}
   		}
   		memset(flag,0,4*N+4),memset(bel,0,4*N+4);tot=0;
   		flag[R]=-1;
   		for(int i=1;i<=N;i++){
   			if(flag[i]) continue;
   			int x=i;
   			while(!flag[x]) flag[x]=i,x=eg[ine[x]][0];
   			if(flag[x]==i){
   				++tot;int y=x;
   				do{
   					bel[x]=tot;
   					x=eg[ine[x]][0];
   				}while(x!=y);
   			}
   		}
   		for(int i=1;i<=N;i++){
   			if(!bel[i]) bel[i]=++tot;
   			if(i==R) continue;
   			ine[i]=eg[ine[i]][2];
   			ans+=ine[i];
   		}R=bel[R];
   		if(tot==N) break;
   		for(int i=1;i<=M;i++){
   			eg[i][2]-=ine[eg[i][1]];
   			eg[i][0]=bel[eg[i][0]],eg[i][1]=bel[eg[i][1]];
   		}
   		N=tot;
   	}
   	printf("%d\n",ans);
    return 0;
}
