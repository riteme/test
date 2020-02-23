#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100

typedef vector<int> poly;

static int n;
static char ep[NMAX + 10][NMAX + 10];
static poly *p[NMAX + 10];
static int id[NMAX + 10];

void add(poly *&dst, poly *src) {
    if (!dst) {
        dst = src;
        return;
    }
    if (!src) return;
    if (dst->size() < src->size())
        dst = src;
    else {
        for (int i = 0; i < src->size() - 1; i++)
            (*dst)[i] = (*src)[i];
        (*dst)[src->size() - 1] += (*src)[src->size() - 1];
    }
}

void w(poly *&dst) {
    if (dst) {
        dst->push_back(1);
        for (int i = 0; i < dst->size() - 1; i++)
            (*dst)[i] = 0;
    }
}

poly *eval(char *s) {
    vector<poly*> stk;
    auto BR = new poly;
    for (int i = 0; s[i]; i++) {
        char c = s[i];
        if (c == '+') {
            auto p = new poly{1};
            if (!stk.empty() && stk.back() != BR) {
                add(stk.back(), p);
            } else stk.push_back(p);
        } else if (c == '[') {
            stk.push_back(BR);
        } else if (c == ']') {
            auto p = stk.back()== BR ? NULL : stk.back();
            while (stk.back() != BR)
                stk.pop_back();
            stk.pop_back();
            w(p);
            if (!stk.empty() && stk.back() != BR) {
                add(stk.back(), p);
            } else stk.push_back(p);
        }
    }
    return stk[0];
}

bool cmp(int i, int j) {
    auto a = p[i];
    auto b = p[j];
    if (!b) return false;
    if (!a) return true;
    if (a->size() == b->size()) {
        for (int i = a->size() - 1; i >= 0; i--)
        if ((*a)[i] != (*b)[i])
            return (*a)[i] < (*b)[i];
        return false;
    }
    return a->size() < b->size();
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", ep[i]);
        p[i] = eval(ep[i]);
        id[i] = i;
    }

    sort(id + 1, id + n + 1, cmp);
    for (int i = 1; i <= n; i++)
        puts(ep[id[i]]);

    return 0;
}