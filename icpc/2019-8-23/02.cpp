#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define maxn 150019
#define rep(i, l, r) for (register int i = l; i <= r; i++)
#define per(i, r, l) for (register int i = r; i >= l; i--)
#define srep(i, l, r) for (register int i = l; i < r; i++)
#define sper(i, r, l) for (register int i = r; i > l; i--)
using namespace std;

#define MEMSIZE 70000000
static unsigned char mem[MEMSIZE];
static size_t mem_pos;

inline void clear() {
  mem_pos = 0;
}

void *operator new(size_t cnt) {
  void *ptr = mem + mem_pos;
  mem_pos += cnt;
  return ptr;
}

#define BUFFERSIZE 65536
static size_t _pos = BUFFERSIZE;
static char _buf[BUFFERSIZE];

inline void _getc(char &c) {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buf, 1, BUFFERSIZE, stdin);
    }
    c = _buf[_pos++];
}

template <typename T>
inline void read(T &x) {
    x = 0;
    char c;
    do _getc(c); while (!isdigit(c));
    do {
        x = x * 10 + (c - '0');
        _getc(c);
    } while (isdigit(c));
}

int n, m;
int a[maxn];
set<int> *s[maxn << 1];
set<int> :: iterator it;
int qx, qy, qd;
void add(int l, int r, int o){
    if (qx <= l && r <= qy) {
        s[o]->insert(qd);
        return;
    }
    int mid = ((r - l) >> 1) + l;
    if (qx <= mid) add(l, mid, o << 1);
    if (qy > mid) add(mid + 1, r, o << 1 | 1);
}
int get(int l, int r, int o){
    it = s[o]->lower_bound(qd);
    int ans = n + 1;
    if (it != s[o]->end()) ans = *it;
    if (l == r) return ans;
    int mid = ((r - l) >> 1) + l;
    if (qx <= mid) ans = min(ans, get(l, mid, o << 1));
    else ans = min(ans, get(mid + 1, r, o << 1 | 1));
    return ans;
}
void init(int l, int r, int o){
    //s[o].clear();
    s[o] = new set<int>;
    if (l == r) return;
    int mid = ((r - l) >> 1) + l;
    init(l, mid, o << 1), init(mid + 1, r, o << 1 | 1);
}

bool vis[maxn];
int lastans = 0;
void recover(){
    clear();
    lastans = 0;
    init(1, n, 1);
    rep(i, 1, n) vis[i] = 0;
}

int main(){
    int T;
    //scanf("%d", &T);
    read(T);
    while (T--){
        //scanf("%d%d", &n, &m);
        read(n); read(m);
        recover();
        rep(i, 1, n) read(a[i]); //scanf("%d", &a[i]);
        rep(i, 1, n) {
            qx = 1, qy = i - 1, qd = a[i];
            if (qx <= qy) add(1, n, 1);
        }
        rep(i, 1, m){
            //scanf("%d", &qx);
            read(qx);
            if (qx == 1){
                //scanf("%d", &qx);
                read(qx);
                //qx ^= lastans;
                if (vis[qx]) continue;
                vis[qx] = 1;
                qy = n, qd = a[qx];
                add(1, n, 1);
            }
            else if (qx == 2){
                //scanf("%d%d", &qx, &qd);
                read(qx); read(qd);
                //qx ^= lastans, qd ^= lastans;
                printf("%d\n", lastans = get(1, n, 1));
            }
        }
    }
    return 0;
}
