#include <bits/stdc++.h>
int n, to[3][3] = {0, 1, 1, 1, 2, 1, 1, 1, 1}, cnt = 0;
struct interval{
    int type;
    long long l, r;
}A[200005], B[200005], C[200005];
void solve(){
    scanf("%d", &n);    long long lstr = -1; cnt = 0;
    for(int i = 1; i <= n; ++i){
        long long l, r;
        scanf("%lld%lld", &l, &r);
        if(lstr + 1ll < l) C[++cnt] = (interval){0, lstr + 1ll, l - 1ll};
        C[++cnt] = (interval){1, l, r};
        lstr = r;
    }C[++cnt] = (interval){0, lstr + 1ll, (1ll << 60) - 1ll};
    for(int w = 59; w >= 0; --w){
        long long a = 1ll << w; int c1 = 0, c2 = 0;
        for(int i = 1; i <= cnt; ++i)
            if(C[i].r < a) A[++c1] = C[i];
            else if(C[i].l >= a) B[++c2] = C[i];
            else A[++c1] = (interval){C[i].type, C[i].l, a - 1ll}, B[++c2] = (interval){C[i].type, a, C[i].r};
        cnt = 0;
        int n1 = 1, n2 = 1; long long hav = -1;
        while(true){
            ++hav;
            if(A[n1].r < hav) ++n1;
            if(B[n2].r - a < hav) ++n2;
            if(n1 > c1 || n2 > c2) break;
            C[++cnt] = (interval){to[A[n1].type][B[n2].type], hav, std::min(A[n1].r, B[n2].r - a)};//
            hav = std::min(A[n1].r, B[n2].r - a);
        }
    }
    if(C[1].type == 1) printf("Takahashi\n");
    else printf("Aoki\n");
    return ;
}
int main(){
    //freopen("02_small_01.txt", "r", stdin);

    int T = 1;
    scanf("%d", &T);
    while(T--) solve();
    return 0;
}
