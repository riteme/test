#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;


struct Skiplist {
    static constexpr int LEVMAX = 32;

    struct Node {
        Node(int _key = 0, int _cnt = 0)
            : key(_key), cnt(_cnt ? _cnt : randcnt()) {
            sum = new int[cnt];
            nxt = new Node*[cnt];
            memset(sum, 0, sizeof(int) * cnt);
            memset(nxt, 0, sizeof(Node*) * cnt);
        }

        int key, cnt, *sum;
        Node **nxt;
    };

    Skiplist() {
        head = new Node(0, LEVMAX);
    }

    static int lev;
    static Node *head, *last[LEVMAX];

    int sum(int i, Node *x, Node *y) {
        int r = 0;
        for (; x != y; x = x->nxt[i]) r += x->sum[i];
        return r;
    }

    void insert(int key) {
        auto x = head;
        int i = lev;
        do {
            while (x->nxt[i] && x->nxt[i]->key <= key) x = x->nxt[i];
            last[i] = x;
        } while (i-- && x->key < key);
        if (x->key == key) {
            for (int i = 0; i < x->cnt; i++) x->sum[i]++;
            for (int i = x->cnt; i <= lev; i++) last[i]->sum[i]++;
        } else {
            auto y = new Node(key);
            y->nxt[0] = x->nxt[0]; x->nxt[0] = y; y->sum[0] = 1;
            for (int i = 1; i < y->cnt && i <= lev; i++) {
                y->sum[i] = sum(i - 1, y, last[i]->nxt[i]);
                last[i]->sum[i] = sum(i - 1, last[i], y);
                y->nxt[i] = last[i]->nxt[i];
                last[i]->nxt[i] = y;
            }
            for (int i = y->cnt; i <= lev; i++) last[i]->sum[i]++;
            if (y->cnt > lev + 1) {
                head->cnt++;
                head->nxt[++lev] = y;
                head->sum[lev] = sum(lev - 1, head, y);
                y->sum[lev] = sum(lev - 1, y, nullptr);
            }
        }
    }

    void remove(int key) {
        auto x = head;
        int i = lev;
        do {
            while (x->nxt[i] && x->nxt[i]->key < key) x = x->nxt[i];
            last[i] = x;
        } while (i--);
        x = x->nxt[0];
        if (x->sum[0] > 1) {
            for (int i = 0; i < x->cnt; i++) x->sum[i]--;
            for (int i = x->cnt; i <= lev; i++) last[i]->sum[i]--;
        } else {
            for (int i = 0; i < x->cnt; i++) {
                last[i]->sum[i] += x->sum[i] - 1;
                last[i]->nxt[i] = x->nxt[i];
            }
            for (int i = x->cnt; i <= lev; i++) last[i]->sum--;
            for (; lev && !head->nxt[lev]; lev--, head->cnt--) ;
        }
    }

    int nxt(int key) {
        auto x = head;
        int i = lev;
        do {
            while (x->nxt[i] && x->nxt[i]->key <= key) x = x->nxt[i];
            last[i] = x;
        } while (i-- && x->key < key);
        return x->nxt[0] ? x->nxt[0]->key : -1;
    }

    int pre(int key) {
        auto x = head;
        int i = lev;
        do {
            while (x->nxt[i] && x->nxt[i]->key < key) x = x->nxt[i];
            last[i] = x;
        } while (i--);
        return x != head ? x->key : -1;
    }

    Node *kth(int k) {
        //for (auto x = head->nxt[0]; x; x = x->nxt[0])
        //    printf("%d ", x->key);
        //putchar('\n');
        auto x = head;
        int i = lev;
        do {
            while (x->nxt[i] && x->sum[i] < k) {
                k -= x->sum[i];
                x = x->nxt[i];
            }
        } while (i-- && k > x->sum[0]);
        return x;
    }

    int count(int key) {
        auto x = head;
        int i = lev, r = 0;
        do {
            while (x->nxt[i] && x->nxt[i]->key < key) {
                r += x->sum[i];
                x = x->nxt[i];
            }
        } while (i--);
        return r;
    }

    static int randcnt() {
        constexpr int BUFSIZE = 65536;
        static auto urandom = fopen("/dev/urandom", "r");
        static unsigned char buf[BUFSIZE], *p = buf + BUFSIZE;
        static size_t c;
        int r = 0;
        for (; r <= lev; r++) {
            if (c == sizeof(unsigned char)) p++;
            if (p == buf + BUFSIZE) fread(p = buf, 1, BUFSIZE, urandom);
            auto b = *p & 1;
            *p >>= 1; c++;
            if (b) break;
        }
        return r + 1;
    }
};

int Skiplist::lev;
Skiplist::Node *Skiplist::head, *Skiplist::last[LEVMAX];

int main() {
    int q;
    scanf("%d", &q);
    Skiplist li;
    while (q--) {
        int t, x;
        scanf("%d%d", &t, &x);
        switch (t) {
            case 0: li.insert(x); break;
            case 1: li.remove(x); break;
            case 2: printf("%d\n", li.kth(x)->key); break;
            case 3: printf("%d\n", li.count(x)); break;
            case 4: printf("%d\n", li.pre(x)); break;
            case 5: printf("%d\n", li.nxt(x)); break;
        }
    }

    return 0;
}
