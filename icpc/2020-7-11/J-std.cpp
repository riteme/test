
#include<cstdio>
#include<cstring>
#include<algorithm>

#define lson l,mid
#define rson mid+1,r
using namespace std;
typedef long long LL;
const int maxn = 1e5+5;
const int MX = 200*maxn;

int n,m,a[maxn],bit[20],top;
int lb[maxn],rb[maxn],pr[maxn];
int mc[maxn],hah;
int RT[maxn],Left[MX],Right[MX],D[MX],tot;
LL C[MX];

void init(){
    hah = tot = 0;
}
void copy(int k,int p){
    C[k] = C[p];D[k] = D[p];
    Left[k] = Left[p];Right[k] = Right[p];
}
void push_up(int root){
    C[root] = C[Left[root]]+C[Right[root]];
}
void push_down(int l,int r,int root){
    if(l == r||D[root]==0) return;
    int lrt,rrt,mid;
    mid = (l+r)>>1;
    lrt = tot++;rrt = tot++;
    copy(lrt,Left[root]);copy(rrt,Right[root]);
    Left[root] = lrt;Right[root] = rrt;
    D[lrt] += D[root];
    D[rrt] += D[root];
    C[lrt] += 1LL*(mid-l+1LL)*D[root];
    C[rrt] += 1LL*(r-mid)*D[root];
    D[root] = 0;
}
int build(int l,int r){
    int root = tot++;
    C[root] = 0;D[root] = 0;
    if(l == r) return root;
    int mid = (l+r)>>1;
    Left[root] = build(lson);
    Right[root] = build(rson);
    return root;
}
int update(int a,int b,int l,int r,int root){
    push_down(l,r,root);
    int newroot = tot++;
    copy(newroot,root);
    if(a<=l&&r<=b){
        C[newroot] = C[root] + (r-l+1);
        D[newroot] = 1;
        return newroot;
    }
    int mid = (l+r)>>1;
    if(b<=mid){
        Left[newroot] = update(a,b,lson,Left[root]);
    }else if(a>mid){
        Right[newroot] = update(a,b,rson,Right[root]);
    }else{
        Left[newroot] = update(a,b,lson,Left[root]);
        Right[newroot] = update(a,b,rson,Right[root]);
    }
    push_up(newroot);
    return newroot;
}
LL query(int a,int b,int l,int r,int root){
    push_down(l,r,root);
    if(a <= l&&r <= b) return C[root];
    if(l > b||r < a) return 0;
    int mid = (l+r)>>1;
    return query(a,b,lson,Left[root])+query(a,b,rson,Right[root]);
}
void preprocess(){
    int i,j;
    memset(pr,-1,(hah+1)*sizeof(int));
    lb[1] = 1;rb[1] = 0;
    pr[a[1]] = 1;
    RT[1] = RT[0] = build(1,n);
    for(i = 2;i <= n;i++){
        if(pr[a[i]]==-1){
            rb[i] = rb[i-1];
            lb[i] = lb[i-1];
        }else{
            if(pr[a[i]]>=rb[i-1]){
                rb[i] = pr[a[i]];
                lb[i] = rb[i-1]+1;
            }else{
                rb[i] = rb[i-1];
                lb[i] = max(lb[i-1],pr[a[i]]+1);
            }
        }
        pr[a[i]] = i;
        if(rb[i]){
            RT[i] = update(lb[i],rb[i],1,n,RT[i-1]);
        }else RT[i] = RT[i-1];
    }
}

int main(){
    int i,j;
    while(~scanf("%d%d",&n,&m)){
        init();
        for(i = 1;i <= n;i++){
            scanf("%d",&a[i]);
            top = 0;
            if(a[i]) for(;a[i];a[i]/=10) bit[top++]=a[i]%10;
            else bit[top++]=0;
            sort(bit,bit+top);
            for(j = top-1;j>=0;j--) a[i] = a[i]*10+bit[j];
            mc[hah++] = a[i];
        }
        sort(mc,mc+hah);
        hah = unique(mc,mc+hah)-mc;
        for(i = 1;i <= n;i++){
            a[i] = lower_bound(mc,mc+hah,a[i])-mc+1;
        }
        preprocess();
        LL l,r,tmp = 0;
        while(m--){
            scanf("%lld%lld",&l,&r);
            tmp = query((int)l,(int)r,1,n,RT[r]);//-query(l,r,1,n,RT[l-1]);
            printf("%lld\n",tmp);
        }
    }

    return 0;
}
