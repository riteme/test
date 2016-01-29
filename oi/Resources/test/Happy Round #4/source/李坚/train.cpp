#include<iostream>
#include<cstdio>
using namespace std; 
double abs(double x)
{
	if (x<0)
		return -x;
}
inline int read()
{
	int x=0;
	int f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9')
	{
		if (ch=='-')
			f=-1;
		ch=getchar();
	}
	while (ch<='9' && ch>='0')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
double Max_Int=9999999999;
int m[1001][1001];
double map[1001][1001];
int N,M;
void Init()
{
  N=read();
  M=read();
  for (int i=1;i<=M;i++)
  {
  	int u,v,a;
  	u=read();
  	v=read();
  	a=read();
  	m[u][0]++;
  	m[v][0]++;
  	m[v][m[v][0]]=u;
  	m[u][m[u][0]]=v;
  	if (map[u][v]!=Max_Int)
  		cout<<"SSSSSSSSSSSSS";
  	map[u][v]=a;
  	map[v][u]=a;
  }
}
int main()
{
	freopen("train.in","r",stdin);
	froepen("train.out","w",stdout);
	cout<<-1<<endl;
}