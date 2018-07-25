#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>

#define ins(xxx, yyy, www)                                    \
    tree[xxx].ne.push_back(yyy), tree[yyy].ne.push_back(xxx), \
        tree[xxx].w.push_back(www), tree[yyy].w.push_back(www)

using namespace std;

#define MAX (1000000 + 5)

bool prime[MAX] = { 0 };
int num[MAX] = { 0 }, n;
bool reach[MAX] = { 0 };

struct node {
    vector<int> ne;
    vector<int> w;
    vector<int> xo;
};
node tree[MAX];

void sieve() {
    int i = 0, a = 0, j = 0, k = 0;

    for (a = 2; a < MAX; a++) {
        while (prime[a])
            a++;
        // printf("%d ",a);
        num[a] = a;
        for (j = 2; j * a < MAX; j++) {
            prime[j * a] = 1;
            // printf("num[%d]=%d\n",j*a,num[j*a]);
            for (k = j * a; k % a == 0; k = k / a) /*printf("%d ",a),*/
                num[j * a] ^= a;
            // printf("\nnum[%d]=%d\n",j*a,num[j*a]);
        }
    }

    //  for(i=2;i<50;i++) printf("xor[%d]:%d\n",i,num[i]);
}

int start() {
    int i = 0, n = 0, ta = 0, tb = 0, tc = 0, ma = -1;

    scanf("%d", &n);
    for (i = 1; i < n; i++) {
        scanf("%d%d%d", &ta, &tb, &tc);
        ins(ta, tb, tc);
        if (ta > ma)
            ma = ta;
        if (tb > ma)
            ma = tb;
    }

    return ma;
}

void spj(int start) {
    int now = start, i = 0, j = 0, p = 0, flag = 0;
    queue<int> q;

    q.push(start);

    while (!q.empty()) {
        now = q.front();
        q.pop();

        reach[now] = 1;
        tree[now].xo.push_back(1);

        for (i = 0; i < tree[now].ne.size(); i++) {
            p = tree[now].ne[i];  // p:正在处理的邻接点

            if (!reach[p]) {
                q.push(p);
                // printf("From %d to %d:w=%d\n",now,p,tree[now].w[i]);

                for (j = 0; j < tree[now].xo.size(); j++)  //现在要发出的xor
                {
                    //   printf("->%d*%d=%d\n",                      \
                    tree[now].xo[j],tree[now].w[i],             \
                    tree[now].xo[j]*tree[now].w[i]);            \

                    tree[p].xo.push_back(tree[now].xo[j] * tree[now].w[i]);

                    if (num[tree[now].xo[j] * tree[now].w[i]] == 0)
                        flag++;
                }

                //        printf("\n");
            }
        }
    }

    printf("%d\n", flag * 2);
}

int find_dist() {
    int find[10000] = { 0 };
    int now = 1, i = 0, flag = 0;

    queue<int> q;

    q.push(1);

    while (!q.empty()) {
        now = q.front();
        q.pop();

        for (i = 0; i < tree[now].ne.size(); i++)
            if (find[tree[now].ne[i]] == 0)
                find[tree[now].ne[i]] = find[now] + 1, q.push(tree[now].ne[i]);
    }

finish:
    // printf("now=%d.find[now]=%d.\n",now,find[now]);

    return now;
}

int main() {
    sieve();
    start();
    int i;

    spj(find_dist());

}
