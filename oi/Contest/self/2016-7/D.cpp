#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#define MAXN 1005
using namespace std;
inline int read()
{
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-')f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}
int n, m, p, f, l, t, leaf_num;
vector<int> son[MAXN];
vector<int> len[MAXN];
bool leaf[MAXN];
int Index=0;
int pos1[MAXN], pos2[MAXN];
int dis[MAXN];
int num[MAXN];
int w[MAXN];
int dp[50005];
int sum=0;

void DFS(int now)
{
	int sz = son[now].size();
	pos1[now] = ++Index;
	for(int j=0; j<sz; j++)
	{
		dis[son[now][j]] = dis[now]+len[now][j];
		DFS(son[now][j]);
	}
	pos2[now] = ++Index;
}

int main()
{
	n=read(); m=read();
	leaf_num = n;
	memset(leaf, true, sizeof(leaf));
	for(int i=1; i<n; i++)
	{
		p=read(); f=read(); l=read();
		son[f].push_back(p);
		len[f].push_back(l);
		if(leaf[f]) { leaf_num--; leaf[f] = false; }
	}
	dis[1]=0; DFS(1);
	for(int i=1; i<=leaf_num; i++)
	{
		num[i] = read();
        dis[num[i]] <<= 1;
		w[i] = read();
		sum += w[i];
	}
    while(m--)
    {
        for(int i=0; i<=5001; i++) dp[i] = 0;
        p=read(); t=read();
        for(int i=1; i<=leaf_num; i++)
        {
            if(pos1[num[i]]>pos1[p] && pos1[num[i]]<pos2[p]) continue;
            for(int j=t; j>=dis[num[i]]; j--)
                if(dp[j-dis[num[i]]]+w[i] > dp[j])
                    dp[j] = dp[j-dis[num[i]]]+w[i];
        }
        printf("%d\n",dp[t]);
    }
    fclose(stdin); fclose(stdout);
	return 0;
}
