#include <cstdio>
#include <cstring>
#define mem(a) memset(a, 0, sizeof(a))
#define MAXN 2000007
#define maxn 1030302
#define lf(a) a *a *a
static int hash[MAXN + 5], next[maxn + 5];
static int sum[maxn + 5], i;
void insert(int num)  //插入一个数num
{
    int numm = num > 0 ? num : -num;
    int h = (numm % MAXN + numm / MAXN) % MAXN;  //哈希函数
    sum[i] = num;
    next[i] = hash[h];
    hash[h] = i++;
}
int is_find(int num) {
    int number = 0;
    int numm = num > 0 ? num : -num;
    int h = (numm % MAXN + numm / MAXN) % MAXN;
    int u = hash[h];
    while (u) {  //一条链要搜到尾，找到这个值的可行数
        if (sum[u] == num) number++;
        u = next[u];
    }
    return number;  //返回可行数
}
int main() {
    int a[5];
    while (~scanf("%d%d%d%d%d", &a[0], &a[1], &a[2], &a[3], &a[4])) {
        mem(sum);
        i = 1;
        mem(hash);
        mem(next);
        int i, j, k, count = 0;
        for (i = -50; i <= 50; i++)
            if (i != 0)
                for (j = -50; j <= 50; j++)
                    if (j != 0)
                        for (k = -50; k <= 50; k++)
                            if (k != 0)
                                insert(a[0] * lf(i) + a[1] * lf(j) +
                                       a[2] * lf(k));

        for (i = -50; i <= 50; i++)
            if (i != 0)
                for (j = -50; j <= 50; j++)
                    if (j != 0)
                        count += is_find((-a[3]) * lf(i) - a[4] * lf(j));
        printf("%d\n",count);
    }
    return 0;
}
