#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair <int,int> pii;

#define pb push_back
#define fi first
#define sc second

const int MAXM=100005;

struct Query
{
	int l,r,v,id,qid;
}q[MAXM],tmp[MAXM];

int n,nc,num[MAXM*2],ans[MAXM],C[MAXM],lst[MAXM];
pii a[MAXM];

bool cmp(const Query &a,const Query &b)
{
	return a.id<b.id;
}

void clear(int x)
{
	for (;x<=n;x+=x&-x)
		C[x]=0;
}

void add(int x,int d)
{
	for (;x<=n;x+=x&-x)
		C[x]+=d;
}

int sum(int x)
{
	int ret=0;
	for (;x;x-=x&-x)
		ret+=C[x];
	return ret;
}

void solve(int al,int ar,int ql,int qr)
{
	if (ql>qr)
		return;
	if (al==ar)
	{
		for (int j=ql;j<=qr;j++)
			if (q[j].r)
				ans[q[j].qid]=num[al-1];
	}
	else
	{
		int am=al+ar>>1,lc=ql,rc=qr;
		for (int j=lower_bound(a,a+n,make_pair(al,0))-a;j<n&&a[j].fi<=am;j++)
			add(a[j].sc,1);
		sort(q+ql,q+qr+1,cmp);
		//printf("%d\n",sum(4)-sum(1));
		for (int j=ql;j<=qr;j++)
			if (q[j].r==0)
			{
				if (q[j].qid>=al&&q[j].qid<=am)
					add(q[j].l,-1);
				//printf("%d %d\n",q[j].l,q[j].v);
				if (q[j].v<=am)
				{
					add(q[j].l,1);
					tmp[lc++]=q[j];
				}
				else
					tmp[rc--]=q[j];
			}
			else
			{
				int k=sum(q[j].r)-sum(q[j].l-1);
				//printf("%d %d %d\n",al,am,k);
				if (k>=q[j].v)
					tmp[lc++]=q[j];
				else
				{
					q[j].v-=k;
					tmp[rc--]=q[j];
				}
			}
		for (int j=ql;j<=qr;j++)
			q[j]=tmp[j];
		for (int j=lower_bound(a,a+n,make_pair(al,0))-a;j<n&&a[j].fi<=am;j++)
			clear(a[j].sc);
		for (int j=ql;j<=qr;j++)
			if (q[j].r==0&&q[j].v<=am)
				clear(q[j].l);
		solve(al,am,ql,rc);
		solve(am+1,ar,lc,qr);
	}
}

void solve()
{
	nc=0;
	for (int i=0;i<n;i++)
	{
		scanf("%d",&a[i].fi);
		num[nc++]=a[i].fi;
		a[i].sc=i+1;
	}
	int m,qc=0;
	scanf("%d",&m);
	for (int i=0;i<m;i++)
	{
		int op;
		scanf("%d",&op);
		if (op==1)
		{
			scanf("%d%d",&q[i].l,&q[i].v);
			q[i].r=0;
			num[nc++]=q[i].v;
		}
		else
		{
			scanf("%d%d%d",&q[i].l,&q[i].r,&q[i].v);
			q[i].qid=qc++;
		}
		q[i].id=i;
	}
	sort(num,num+nc);
	nc=unique(num,num+nc)-num;
	for (int i=0;i<n;i++)
	{
		a[i].fi=upper_bound(num,num+nc,a[i].fi)-num;
		lst[i+1]=a[i].fi;
	}
	sort(a,a+n);
	for (int i=0;i<m;i++)
		if (q[i].r==0)
		{
			q[i].v=upper_bound(num,num+nc,q[i].v)-num;
			q[i].qid=lst[q[i].l];
			lst[q[i].l]=q[i].v;
			//printf("%d %d\n",q[i].v,q[i].qid);
		}
	solve(1,nc,0,m-1);
	for (int i=0;i<qc;i++)
		printf("%d\n",ans[i]);
}

int main()
{
	#ifdef KeyID
		freopen("read.txt","r",stdin);
	#endif
	while (scanf("%d",&n)!=EOF) solve();
	return 0;
}