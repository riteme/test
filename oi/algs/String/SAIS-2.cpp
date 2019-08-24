#include <cstdio>
#include <cstring>

#define NMAX 300

#define L true
#define S false

static int sbuc[NMAX + 10], lbuc[NMAX + 10], sa[NMAX + 10];
static int stil[NMAX + 10], ltil[NMAX + 10];

void induced_sort(int *str, bool *type, int *scnt, int *lcnt, int s) {
    // L 型桶在前，S 型桶在后

    memcpy(ltil + 1, lcnt, s << 2);
    for (int c = 1; c <= s; c++) {
        for (int i = lcnt[c - 1]; i < ltil[c]; i++) {
            if (type[lbuc[i] - 1])
                lbuc[ltil[str[lbuc[i] - 1]]++] = lbuc[i] - 1;
        }

        for (int i = scnt[c - 1]; i < stil[c]; i++) {
            if (type[sbuc[i] - 1])
                lbuc[ltil[str[sbuc[i] - 1]]++] = sbuc[i] - 1;
        }
    }

    memcpy(stil + 1, scnt + 1, s << 2);
    for (int c = s; c >= 1; c--) {
        for (int i = scnt[c] - 1; i >= stil[c]; i--) {
            if (sbuc[i] > 1 && !type[sbuc[i] - 1])
                sbuc[--stil[str[sbuc[i] - 1]]] = sbuc[i] - 1;
        }

        for (int i = lcnt[c] - 1; i >= lcnt[c - 1]; i--) {
            if (lbuc[i] > 1 && !type[lbuc[i] - 1])
                sbuc[--stil[str[lbuc[i] - 1]]] = lbuc[i] - 1;
        }
    }
}

// 字符串下标从 1 开始，字符集是 {1, 2, ..., s}
// bucket 下标从 0 开始
void _sais(int *str, int n, int s) {
    bool type[n + 1];
    int scnt[s + 1], lcnt[s + 1], nxt[n + 1], ptr[n + 1], name[n + 1];
    memset(scnt, 0, sizeof(scnt));
    memset(lcnt, 0, sizeof(lcnt));
    memset(name, 0, sizeof(name));

    scnt[str[n]] = 1;
    type[0] = type[n] = S;
    for (int i = n - 1; i > 0; i--) {
        type[i] = str[i] == str[i + 1] ? type[i + 1] : str[i] > str[i + 1];

        if (type[i])
            lcnt[str[i]]++;
        else
            scnt[str[i]]++;
    }

    for (int i = 2; i <= s; i++) {
        scnt[i] += scnt[i - 1];
        lcnt[i] += lcnt[i - 1];
    }

    int last = n, cnt = 0;
    memcpy(stil + 1, scnt, s << 2);
    for (int i = n; i > 0; i--) {
        nxt[i] = last;
        if (type[i - 1] && !type[i]) {
            sbuc[stil[str[i]]++] = last = i;
            ptr[++cnt] = i;
        }
    }

    induced_sort(str, type, scnt, lcnt, s);

    int ncnt = last = 0;
    for (int i = 0; i < scnt[s]; i++) {
        int x = sbuc[i];
        if (x == 1 || !type[x - 1] || type[x])
            continue;
        if (!last || last - nxt[last] != x - nxt[x] ||
            memcmp(str + last, str + x, (nxt[x] - x + 1) << 2) ||
            memcmp(type + last, type + x, nxt[x] - x + 1))
            ncnt++;
        last = x;
        name[x] = ncnt;
    }

    if (ncnt < cnt) {
        int nstr[cnt + 1];
        for (int i = 1; i <= cnt; i++) {
            nstr[cnt - i + 1] = name[ptr[i]];
        }

        _sais(nstr, cnt, ncnt);

        memcpy(stil + 1, scnt, s << 2);
        for (int i = 0; i < cnt; i++) {
            int x = ptr[cnt - sa[i] + 1];
            sbuc[stil[str[x]]++] = x;
        }
    } else {
        memcpy(stil + 1, scnt, s << 2);
        for (int i = 0; i < scnt[s]; i++) {
            int x = sbuc[i];
            if (name[x])
                sbuc[stil[str[x]]++] = x;
        }
    }

    induced_sort(str, type, scnt, lcnt, s);

    int pos = 0;
    for (int c = 1; c <= s; c++) {
        for (int i = lcnt[c - 1]; i < lcnt[c]; i++)
            sa[pos++] = lbuc[i];
        for (int i = scnt[c - 1]; i < scnt[c]; i++)
            sa[pos++] = sbuc[i];
    }
}

void sais(const char *str, int n) {
    int s[n + 1];
    for (int i = 0; i < n; i++) {
        s[i + 1] = str[i];
    }

    _sais(s, n, 255);
}

static int n;
static char str[NMAX + 10];

int main() {
    scanf("%s", str);
    n = strlen(str);

    str[n] = '$';
    sais(str, n + 1);
    for (int i = 1; i <= n; i++) {
        printf("%d ", sa[i]);
    }
    putchar('\n');

    return 0;
}
