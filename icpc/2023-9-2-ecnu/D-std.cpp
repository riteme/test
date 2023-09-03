#include <bits/stdc++.h>
using namespace std;
struct node {
    int to[26];
    int len,fa;
    void clear() {
        memset(to,0,sizeof(to));
        len=0;
        fa=0;
    }
};
struct SAM {
    node po[500];
    int last=1,tot=1;
    void add(int c) {
        int np=++tot;
        int p=last;
        last=np;
        po[np].len=po[p].len+1;
        for (;p&&!po[p].to[c];p=po[p].fa)
            po[p].to[c]=np;
        if(!p) po[np].fa=1;
        else {
            int q=po[p].to[c];
//          cout<<"good"<<q<<endl;
            if(po[p].len+1==po[q].len) {
                po[np].fa=q;
            } else {
                int nq=++tot;
                po[nq]=po[q];
                po[np].fa=po[q].fa=nq;
                po[nq].len=po[p].len+1;
                for (;p&&po[p].to[c]==q;p=po[p].fa)
                    po[p].to[c]=nq;
            }
        }
    }
    void clear() {
        for (int i=1;i<=tot;++i)
            po[i].clear();
        tot=1;last=1;
    }
}sam;
int t,n,m,x;
char s[200];
bool f[155][155][305];
void dfs(int i,int j,int k) {
    if(i==m) return;
    for (int c=0;c<26;++c) {
        if(sam.po[k].to[c]) {
            if(f[i+1][j][sam.po[k].to[c]]) {
                printf("%c",c+'a');
                dfs(i+1,j,sam.po[k].to[c]);
                return;
            }
        } else if(sam.po[1].to[c]) {
            if(f[i+1][j+1][sam.po[1].to[c]]) {
                printf("%c",c+'a');
                dfs(i+1,j+1,sam.po[1].to[c]);
                return;
            }
        }
    }
}
void solve() {
    scanf("%d%d%d",&n,&m,&x);
    scanf("%s",s);
    sam.clear();
    for (int i=0;i<n;++i)
        sam.add(s[i]-'a');
//  for (int i=1;i<=sam.tot;++i)
//      cout<<sam.po[i].fa<<" ";
//  cout<<endl;
    for (int i=0;i<=m;++i)
        for (int j=0;j<=x;++j)
            for (int k=1;k<=sam.tot;++k)
                f[i][j][k]=0;
    for (int k=2;k<=sam.tot;++k)
        f[m][x-1][k]=1;
    for (int i=m-1;i;--i) {
        for (int j=x-1;j>=0;--j) {
            for (int k=2;k<=sam.tot;++k) {
                for (int c=0;c<26;++c) {
                    if(sam.po[k].to[c]) {
                        f[i][j][k]|=f[i+1][j][sam.po[k].to[c]];
                    } else if(sam.po[1].to[c]){
                        f[i][j][k]|=f[i+1][j+1][sam.po[1].to[c]];
                    }
                }
            }
        }
    }
    for (int c=0;c<26;++c) {
        if(sam.po[1].to[c]) {
            f[0][0][1]|=f[1][0][sam.po[1].to[c]];
        }
    }
    if(!f[0][0][1]) {
        printf("-1\n");
    } else {
        dfs(0,0,1);
        printf("\n");
    }
}
int main() {
    scanf("%d",&t);
    for (int o=1;o<=t;++o) {
        solve();
    }
}
