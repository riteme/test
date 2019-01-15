#include<bits/stdc++.h>
using namespace std;
int getint()
{
	int res=0,fh=1;char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
	if(ch=='-')fh=-1,ch=getchar();
	while(ch<='9'&&ch>='0')res=res*10+ch-'0',ch=getchar();
	return res*fh;
}
int n,m,ne,T,tot;
int head[1001],vis[1001],nxt[10001],to[10001],v[10001];
string s1,s2,s3;
map<string,int>mp;
int rk(string s)
{
	if(mp.find(s)==mp.end())mp[s]=++tot;
	return mp[s];
}
void link(int x,int y,int z)
{
	ne++;
	to[ne]=y;nxt[ne]=head[x];
	head[x]=ne;v[ne]=z;
}
void dfs(int x,int mx)
{
	for(int i=head[x];i;i=nxt[i])
	{
		if(v[i]<=mx&&vis[to[i]]<max(vis[x],v[i]))
		{
			vis[to[i]]=max(vis[x],v[i]);
			dfs(to[i],mx);
		}
	}
}
int main()
{
	n=getint();m=getint();
	for(int i=1;i<=n;i++)
	{
		cin>>s1>>s2>>s3;
		if(s2[0]=='i')link(rk(s1),rk(s3),1);
		else link(rk(s1),rk(s3),2);
	}
	for(int i=1;i<=m;i++)
	{
		cin>>s1>>s2>>s3;
		memset(vis,0,sizeof(vis));
		T=mp[s3];vis[mp[s1]]=1;
		if(s2[0]=='i')dfs(mp[s1],1);
		else dfs(mp[s1],2);
		if(vis[mp[s3]]==(s2[0]=='i'?1:2))printf("Query %d: true\n",i);
		else printf("Query %d: false\n",i);
	}
	return 0;
}
