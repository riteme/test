#include <cstdio>
#include <cstring>
int n,a[30010],b[30010];
const int Z=sizeof(int);
int min(int x,int y){return x<y?x:y;}
char s[300010];
int sa[300010],rank[600010],tmp[300010],next[300010],first[300010],second[300010],
	height[300010][19],log[300010];
void make_sa(){
	memset(first,-1,Z*(n>128?n:128));
	memset(second,-1,Z*n);
	memset(rank,0,Z*n<<1);
	int cnt=0,tot=0;
	for(int i=0;i<n;i++)next[i]=first[s[i]],first[s[i]]=i;
	for(int i=0,j;tot<n;first[i++]=-1)if(first[i]>-1)
		for(cnt++,j=first[i];j!=-1;j=next[j],tot++)rank[j]=cnt;
	for(int k=1;cnt<n;k<<=1){
		for(int i=tot=0,*p;i<n;i++)next[i]=*(p=second+rank[i+k]),*p=i;
		for(int i=cnt;i>=0;second[i--]=-1)if(second[i]>-1)
			for(int j=second[i],t,*p;j!=-1;j=t)t=next[j],next[j]=*(p=first+rank[j]),*p=j;
		for(int i=cnt=0;tot<n;first[i++]=-1)if(first[i]>-1)
			for(int j=first[i],l=-1,t;j!=-1;j=next[j],tot++)tmp[j]=(t=rank[j+k])>l?l=t,++cnt:cnt;
		memcpy(rank,tmp,Z*n);
	}
	for(int i=0;i<n;i++)sa[--rank[i]]=i;
	for(int i=0,l=log[1]=0;i<n;*height[rank[i++]]=l?l--:0)
		if(rank[i]+1<n)for(;s[i+l]==s[sa[rank[i]+1]+l];l++);
	for(int i=2;i<=n;i++)log[i]=log[i/2]+1;
	for(int k=1;k<=log[n];k++)for(int i=0;i<n;i++)
		height[i][k]=i+(1<<k-1)<n?min(height[i][k-1],height[i+(1<<k-1)][k-1]):height[i][k-1];
}
int lcp(int i,int j){
	int t=log[j-i];
	return min(height[i][t],height[j-(1<<t)][t]);
}
long long ans;
void update(int i,int j){
	j-=i;i=rank[i];
	int l=-1,r=i,p,m;
	while(r-l>1)lcp(m=l+r>>1,i)<j?l=m:r=m;
	p=r;l=i;r=n;
	while(r-l>1)lcp(i,m=l+r>>1)<j?r=m:l=m;
	if(1ll*j*(r-p)>ans)ans=1ll*j*(r-p);
}
char S[600010];
int r[600010];
void manacher(){
	int N=2;*S='#';S[1]='$';
	for(int i=0;i<n;i++)S[N++]=s[i],S[N++]='$';S[N]='%';
	for(int i=0;i<=N;i++)r[i]=1;
	int mr=1,c;
	for(int i=1,j;i<N;i++){
		if(i<mr)r[i]=min(r[c-i],mr-i);
		while(S[i-r[i]]==S[i+r[i]])r[i]++;
		if(i+r[i]>mr)for(j=mr+2,mr=i+r[i],c=i*2;j<=mr;j+=2)update(c-j>>1,j/2-1);
	}
}
int main(){
	gets(s);n=strlen(s);
	make_sa();
	manacher();
	printf("%lld\n",ans);
}
