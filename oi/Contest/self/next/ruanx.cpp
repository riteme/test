#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

int n,t,to=1;
int ans[1500005]={0};
bool flag[1500005]={0};

struct com
{
    char opt;
    int id,a,b;
};
vector <com> c[1500005];

void inp()
{
    int v,i,a,b;
    char cmd[10];
    com tmp;

    scanf("%d%d",&n,&t);

    for(i=1;i<=t;i++)
    {
        scanf("%s",cmd);

        tmp.id=i;

        if(cmd[0]=='A')
            scanf("%d%d%d",&v,&tmp.a,&tmp.b),
            tmp.opt='A',c[v].push_back(tmp);

        if(cmd[0]=='Q')
            scanf("%d%d%d",&v,&tmp.a,&tmp.b),
            tmp.opt='Q',c[v].push_back(tmp);

        if(cmd[0]=='C')
            scanf("%d",&v),
            tmp.opt='C',tmp.a=v,tmp.b=++to,c[v].push_back(tmp);
    }
}

void debug()
{
    int i,j;
    for(i=1;i<=to;i++)
    {
        printf("Node [%d]:\n",i);
        for(j=0;j<c[i].size();j++)
            printf("- [%c] (%d,%d)\n",c[i][j].opt,c[i][j].a,c[i][j].b);
    }
}

struct TA
{
    #define MAX 1048580
    int bin[MAX+5]={0};

    #define lowbit(x) (x)&-(x);

    void ins(int key,int value)
    {
        int x=key;

        while(x<=MAX)
        {
            bin[x]+=value;
            x+=lowbit(x);
        }
    }
    int sum(int l,int r)
    {
        int i,A=0,B=0;

        l--;
        while(l)
        {
            A+=bin[l];
            l-=lowbit(l);
        }
        while(r)
        {
            B+=bin[r];
            r-=lowbit(r);
        }
        return B-A;
    }
};
TA T;

void ask(int id,int l,int r)
{
    ans[id]=T.sum(l,r);
    // printf("Ask [%d,%d] ans=%d\n",l,r,ans[id]);
    flag[id]=1;
}

void dfs(int x)
{
    int i,j,ans=0;
    com tmp;

    for(i=0;i<c[x].size();i++)
    {
        // printf("[%c] (%d,%d)\n",c[x][i].opt,c[x][i].a,c[x][i].b);
        if(c[x][i].opt=='C') dfs(c[x][i].b);
        if(c[x][i].opt=='A') T.ins(c[x][i].a,c[x][i].b);

        if(c[x][i].opt=='Q')
            ask(c[x][i].id,c[x][i].a,c[x][i].b);
    }
    for(i=0;i<c[x].size();i++)
        if(c[x][i].opt=='A') T.ins(c[x][i].a,-c[x][i].b);
}

void out()
{
    int i;
    for(i=1;i<=t;i++)
        if(flag[i]) printf("%d\n",ans[i]);
}

int main(void)
{
    inp();
    dfs(1);
    out();

    return 0;
}
