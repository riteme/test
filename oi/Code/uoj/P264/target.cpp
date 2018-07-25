#include<bits/stdc++.h>
using namespace std;
int n,m,p,u,v,t,T,tot1,tot2,tot3,key,j=1,k=1,l=1,before[120000],maxn[7001000],minn[7001000];double cut;
int read()
{
    char c;int x=0;
    c=getchar();
    while(c>'9'||c<'0')c=getchar();
    while(c<='9'&&c>='0')x=x*10+c-'0',c=getchar();
    return x;
}
void search()
{
    int o,i,now,w;
    tot1=n;
    key=-p;
    for(i=1;i<=m;i++)
    {
        key+=p;
        if(before[j]>maxn[k]&&j<=tot1)now=before[j],w=1;
        else if(k<=tot2)now=maxn[k],w=2;
        if(minn[l]>now&&l<=tot3)now=minn[l],w=3;
        now+=key;
        if(w==1)j++;
        else if(w==2)k++;
        else if(w==3)l++;
        if(i%t==0)printf("%d ",now);
        o=floor(now*cut);
        maxn[++tot2]=o-key-p;
        minn[++tot3]=now-o-key-p;
    }
}
bool cmp(int a,int b)
{
    return a>b;
}
int main()
{
    int i;
    n=read();m=read();p=read();u=read();v=read();t=read();//读入
    for(i=1;i<=n;i++)before[i]=read();
    cut=(double)((double)u/(double)v);//读入比例 
    sort(before+1,before+n+1,cmp);
    search();
    printf("\n");	
    minn[tot3+1]=-INT_MAX;
    maxn[tot2+1]=-INT_MAX;
    before[tot1+1]=-INT_MAX;
    for(i=1;i<=n+m;i++)//j,k,l指向的是还未被切的 
    {
        if(j<=tot1&&before[j]>maxn[k]&&before[j]>minn[l])
        {
            if(!(i%t))printf("%d ",before[j]+key+p);//莫名奇妙要+1 
            j++;
        } 
        else if(k<=tot2&&maxn[k]>before[j]&&maxn[k]>minn[l])
        {
            if(!(i%t))printf("%d ",maxn[k]+key+p);//貌似%优先级很低 
            k++;
        }
        else if(l<=tot3)
        {
            if(!(i%t))printf("%d ",minn[l]+key+p);//因为key初始值是-p，所以现在把p加回来 
            l++;
        }
    }
    //print();
    return 0;
} 
