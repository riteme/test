// #define NDEBUG

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <set>

using namespace std;

#define NMAX 30000
#define SQRTN 200

static int n, m;
static int B[NMAX + 10], P[NMAX + 10];
static vector<int> doge[NMAX + 10];
static int BLOCKSIZE;

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d%d", B + i, P + i);
        doge[B[i]].push_back(i);
    }  // for

    BLOCKSIZE = max(10, static_cast<int>(sqrt(n)));
}

inline int id(int h, int x) {
	return h * (n + 1) + x;
}

static int dist[SQRTN * NMAX + 10];

struct cmp {
	bool operator()(const int a, const int b) const  {
		return dist[a] < dist[b] || (dist[a] == dist[b] && a < b);
	}
};

static struct Heap {
	void push(int x) {
		s.insert(x);	
	}
	
	void pop(int x) {
		auto iter = s.find(x);
		
		assert(iter != s.end());
		s.erase(iter);
	}
	
	void pop() {
		s.erase(s.begin());	
	}
	
	int top() {
		return *s.begin();	
	}
	
	bool empty() {
		return s.empty();	
	}
	
	multiset<int, cmp> s;	
} q;

inline void relax(int u, int v, int d) {
    if (dist[u] + d < dist[v]) {
		q.pop(v);
        dist[v] = dist[u] + d;
		q.push(v);
    }
}

int main() {
    initialize();

    memset(dist, 0x3f, sizeof(dist));
    dist[id(0, B[0])] = 0;
	for (int i = 0; i <= BLOCKSIZE; i++) {
		for (int j = 1; j <= n; j++) {
			q.push(id(i, j));
		}  // for
	}  // for

    while (!q.empty()) {
        int u = q.top();
        int h = u / n, x = u % n;
        q.pop();

        if (h > 0) {
            if (x + h < n)
                relax(u, id(h, x + h), 1);
            if (x - h >= 0)
                relax(u, id(h, x - h), 1);
            relax(u, id(0, x), 0);
        } else {
            for (size_t i = 0; i < doge[x].size(); i++) {
                int dog = doge[x][i];
                int p = P[dog];

                if (p <= BLOCKSIZE)
                    relax(u, id(p, x), 0);
                else {
                    for (int k = 1; x + k * p < n; k++)
                        relax(u, id(0, x + k * p), k);
                    for (int k = 1; x - k * p >= 0; k++)
                        relax(u, id(0, x - k * p), k);
                }
            }  // for
        }
    }  // while

    if (dist[id(0, B[1])] < 0x3f3f3f3f)
        printf("%d\n", dist[id(0, B[1])]);
    else
        printf("-1\n");

    return 0;
}  // function main
