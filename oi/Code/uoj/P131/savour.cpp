#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 300000
#define SIGMA 27
#define EOFCHAR 26

typedef long long int64;

static int n;
static char str[NMAX + 10];

struct Node;
struct Edge {
    Edge(int l, int r, Node *nxt) : left(l), right(r), next(nxt) {}

    int left, right;
    Node *next;

    int length() const {
        return right - left + 1;
    }
};  // struct Edge

struct Node {
    Node() : suffix_link(nullptr) {
        memset(trans, 0, sizeof(trans));
    }

    Node *suffix_link;
    Edge *trans[SIGMA];
};  // struct Node

struct BuildState {
    BuildState(Node *_root)
        : root(_root),
          active_point(_root),
          active_direction(-1),
          active_length(0),
          remainder(0),
          position(0) {}

    Node *root;
    Node *active_point;
    char active_direction;
    int active_length;
    int remainder;
    int position;
};  // struct BuildState

void append(char c, BuildState &state) {
    auto &active = state.active_point;
    auto &dir = state.active_direction;
    auto &len = state.active_length;
    auto &cnt = state.remainder;
    auto &size = state.position;

    cnt++;
    size++;
    Node *last = nullptr;
    while (cnt) {
        if (cnt - 1 <= len) {
            len = cnt - 1;
            dir = len ? str[size - len] : -1;
        }

        while (dir >= 0 && len >= active->trans[dir]->length()) {
            len -= active->trans[dir]->length();
            active = active->trans[dir]->next;
            dir = len ? str[size - len] : -1;
        }  // while

        if ((dir >= 0 && c == str[active->trans[dir]->left + len]) ||
            (dir < 0 && active->trans[c])) {
            if (dir < 0)
                dir = c;
            len++;

            if (last)
                last->suffix_link = active;

            return;
        }

        Node *x;
        if (dir < 0) {
            active->trans[c] = new Edge(size, n, new Node);
            x = active;
        } else {
            Edge *t = active->trans[dir];
            x = new Node;
            x->trans[c] = new Edge(size, n, new Node);
            x->trans[str[t->left + len]] =
                new Edge(t->left + len, t->right, t->next);
            t->right = t->left + len - 1;
            t->next = x;
        }

        if (last)
            last->suffix_link = x;
        last = x;
        active = active->suffix_link ? active->suffix_link : state.root;
        cnt--;
    }  // while
}

struct Info {
    Info() : count(0), max({INT_MIN, INT_MIN}), min({INT_MAX, INT_MAX}) {}

    int64 count;
    struct {
        int64 first;
        int64 second;
    } max;
    struct {
        int64 first;
        int64 second;
    } min;

    int64 count_pairs() const {
        return count * (count - 1) / 2;
    }

    int64 max_product() const {
        if (count >= 2)
            return std::max(max.first * max.second, min.first * min.second);
        return 0;
    }

    void update_max(int64 v) {
        if (v > max.first) {
            max.second = max.first;
            max.first = v;
        } else if (v > max.second)
            max.second = v;
    }

    void update_min(int64 v) {
        if (v < min.first) {
            min.second = min.first;
            min.first = v;
        } else if (v < min.second)
            min.second = v;
    }

    Info &operator+=(const Info &b) {
        count += b.count;
        update_max(b.max.first);
        update_max(b.max.second);
        update_min(b.min.first);
        update_min(b.min.second);

        return *this;
    }
};  // struct Info

static int64 w[NMAX + 10];
static Node *tree;
static int64 sum[NMAX + 10];
static int64 maxv[NMAX + 10];

Info dfs(Node *x, int depth = 0) {
    Info info;
    bool has_child = false;
    for (char c = 0; c < SIGMA; c++) {
        Edge *t = x->trans[c];

        if (!t)
            continue;

        has_child = true;
        auto data = dfs(t->next, depth + t->length());

        sum[depth] -= data.count_pairs();
        sum[depth + t->length()] += data.count_pairs();

        if (data.count >= 2)
            maxv[depth + t->length()] =
                max(maxv[depth + t->length()], data.max_product());

        info += data;
    }  // for

    if (!has_child) {
        info.count = 1;
        info.max.first = info.min.first = w[n - depth + 1];
    }

    return info;
}

void initialize() {
    scanf("%d%s", &n, str + 1);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", w + i);
        str[i] -= 'a';
    }  // for

    tree = new Node;
    BuildState state(tree);
    for (int i = 1; i <= n; i++) {
        append(str[i], state);
    }  // for
    append(EOFCHAR, state);
    tree->trans[EOFCHAR] = nullptr;

    for (int i = 0; i <= n + 2; i++) {
        maxv[i] = LLONG_MIN;
    }  // for
}

int main() {
    // freopen("ex_savour3.in", "r", stdin);

    initialize();

    Info r0 = dfs(tree);

    for (int i = n + 1; i > 0; i--) {
        sum[i] += sum[i + 1];
        maxv[i] = max(maxv[i], maxv[i + 1]);
    }  // for

    printf("%lld %lld\n", r0.count_pairs(), max(maxv[1], r0.max_product()));
    for (int r = 1; r < n; r++) {
        if (sum[r] == 0)
            maxv[r] = 0;

        printf("%lld %lld\n", sum[r], maxv[r]);
    }  // for

    return 0;
}  // function main
