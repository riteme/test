#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long lint;
#define maxn (100010)
#define left lleft
#define right rright
#define log2 Log2
int a[maxn], left[maxn], right[maxn];
lint ans[maxn];
int log2[maxn], st[maxn][32];
void st_prepare(int arr[], int n)
{
    log2[1] = 0;
    for(int i = 2; i <= n; i++)
    {
        log2[i] = log2[i-1];
        if((1 << log2[i] + 1) == i)
            log2[i]++;
    }
    for(int i = n-1; i >= 0; i--)
    {
        st[i][0] = arr[i];
        for(int j = 1; i + (1 << j) - 1 < n; j++)
        {
            st[i][j] = max(st[i][j-1], st[i+(1<<j-1)][j-1]);
        }
    }
}
int st_query(int l, int r)
{
    int len = log2[r - l + 1];
    return max(st[l][len], st[r - (1 << len) + 1][len]);
}
#define stack Stack
pair<int, int> stack[maxn];
int top;
void push_stack(int id, int w, int val[], int mx)
{
    while(top > 0)
    {
        if(stack[top].first < w)
            break;
        top--;
    }
    if(!top) val[id] = mx;
    else val[id] = stack[top].second;
    stack[++top] = make_pair(w, id);
}
int main()
{
    int n;
    while(cin >> n)
    {
        for(int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        st_prepare(a + 1, n);
        top = 0;
        for(int i = 1; i <= n; i++)
        {
            push_stack(i, a[i], left, 0);
        }
        top = 0;
        for(int i = n; i >= 1; i--)
        {
            push_stack(i, a[i], right, n + 1);
        }
        for(int i = 0; i <= n; i++) ans[i] = -1;
        for(int i = 1, l, r, k; i <= n; i++)
        {
            l = left[i];
            r = right[i] - 2;
            k = st_query(l, r);
            ans[r - l + 1] = max(ans[r - l + 1], (lint)k * a[i]);
        }
        for(int i = n - 1; i >= 1; i--)
            ans[i] = max(ans[i], ans[i + 1]);
        for(int i = 1; i <= n; i++)
            printf("%lld\n", ans[i]);
    }

    return 0;
}
