#pragma GCC optimize(3)

#define NDEBUG

#define NAME "substr"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>

#include <queue>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 500000

#define SEED (577777777)
static struct MyRandom {
    MyRandom() {
	srand(SEED);
    }

    int operator()() const {
	return rand();
    }
} randint;

class Treap {
 public:
    Treap() : root(NULL) {}

    void insert(int key) {
	root = _insert(root, key);
    }

    void merge(Treap &t) {
	if (t.size() > size())
	    swap(root, t.root);
	root = _merge(root, t.root);
    }

    int query(int l, int r) {
	return _query(root, l, r);
    }

    int size() {
	return root ? root->size : 0;
    }

 private:
    struct Node {
	Node (int k) :
	    weight(randint()),
	    key(k),
	    size(1),
	    leftbound(k),
	    rightbound(k),
	    left(NULL), right(NULL) {}

	int weight;
	int key;
	int size;
	int leftbound;
	int rightbound;
	Node *left;
	Node *right;

	void update() {
	    size = 1 + (left ? left->size : 0) + (right ? right->size : 0);
	    leftbound = min(key, (left ? left->leftbound : key));
	    rightbound = max(key, (right ? right->rightbound : key));
	}

	Node *left_rotate() {
	    Node *y = left;
	    left = y->right;
	    y->right = this;

	    update();
	    y->update();

	    return y;
	}

	Node *right_rotate() {
	    Node *y = right;
	    right = y->left;
	    y->left = this;

	    update();
	    y->update();

	    return y;
	}
    };

    Node *root;

    Node *_insert(Node *x, int key) {
	if (!x)
	    return new Node(key);

	if (key < x->key) {
	    x->left = _insert(x->left, key);

	    if (x->left->weight < x->weight)
		return x->left_rotate();
	} else if (key > x->key) {
	    x->right = _insert(x->right, key);

	    if (x->right->weight < x->weight)
		return x->right_rotate();
	} else
	    return x;

	x->update();
	return x;
    }

    Node *_merge(Node *x, Node *y) {
	if (y) {
	    x = _insert(x, y->key);
	    x = _merge(x, y->left);
	    x = _merge(x, y->right);
	}
	
	return x;
    }

    int _query(Node *x, int l, int r) {
	if (!x)
	    return 0;
	if (l <= x->leftbound && x->rightbound <= r)
	    return x->size;
	
	int ans = (l <= x->key && x->key <= r ? 1 : 0);
	if (l < x->key)
	    ans += _query(x->left, l, r);
	if (r > x->key)
	    ans += _query(x->right, l, r);
	
	return ans;
    }
};

#define SIGMA 2

struct Request {
    Request(int _l, int _r) : l(_l), r(_r), answer(0), next(NULL) {}

    int l, r;
    int answer;
    Request *next;
};

struct Node {
    Node() : req(NULL), suffix_link(NULL) {
	memset(trans, 0, sizeof(trans));
    }

    void add_request(Request *r) {
	r->next = req;
	req = r;
    }

    Request *req;
    Node *trans[SIGMA];
    Node *suffix_link;
    vector<Node *> adj;
    vector<int> color;
    Treap tree;
};

static Node *root = new Node;

void insert(const char *s, Request *req) {
    Node *cur = root;
    for (size_t pos = 0; s[pos]; pos++) {
	char c = s[pos] - 'a';

	if (!cur->trans[c])
	    cur->trans[c] = new Node;
	
	cur = cur->trans[c];
    }

    cur->add_request(req);
}

void build_suffix_link() {
    queue<Node *> q;

    for (size_t i = 0; i < SIGMA; i++) {
	Node *v = root->trans[i];

	if (!v)
	    continue;

	v->suffix_link = root;
	root->adj.push_back(v);
	q.push(v);
    }

    while (!q.empty()) {
	Node *u = q.front();
	q.pop();

	for (int t = 0; t < SIGMA; t++) {
	    Node *v = u->trans[t];

	    if (!v)
		continue;

	    Node *x = u->suffix_link;
	    while (x != root && !x->trans[t])
		x = x->suffix_link;
	    if (x->trans[t])
		x = x->trans[t];
	    
	    x->adj.push_back(v);
	    v->suffix_link = x;
	    q.push(v);
	}
    }
}

void cover(const char *s, int id) {
    Node *cur = root;
    for (size_t pos = 0; s[pos]; pos++) {
	char c = s[pos] - 'a';
	cur->color.push_back(id);

	while (cur && !cur->trans[c])
	    cur = cur->suffix_link;

	if (!cur)
	    cur = root;
	else
	    cur = cur->trans[c];
    }

    cur->color.push_back(id);
}

void dfs(Node *x) {
    for (size_t i = 0; i < x->adj.size(); i++) {
	Node *v = x->adj[i];

	if (v) {
	    dfs(v);
	    x->tree.merge(v->tree);
	}
    }

    for (size_t i = 0; i < x->color.size(); i++) {
	x->tree.insert(x->color[i]);
    }

    for (Request *head = x->req; head; head = head->next) {
	head->answer = x->tree.query(head->l, head->r);
    }
}

static int n, q;
static Request *que[NMAX + 10];
static char buffer[NMAX + 10];
static vector<string> vec;

void initialize() {
    scanf("%d%d", &n, &q);

    for (int i = 1; i <= n; i++) {
	scanf("%s", buffer);
	vec.push_back(buffer);
    }

    for (int i = 1; i <= q; i++) {
	int l, r;
	scanf("%d%d%s", &l, &r, buffer);
	que[i] = new Request(l, r);
	insert(buffer, que[i]);
    }

    build_suffix_link();

    for (int i = 0; i < n; i++) {
	cover(vec[i].c_str(), i + 1);
    }
}

int main() {
#ifdef NDEBUG
    freopen(NAME ".in", "r", stdin);
    freopen(NAME ".out", "w", stdout);
#endif
    initialize();

    dfs(root);
    for (int i = 1; i <= q; i++) {
	printf("%d\n", que[i]->answer);
    }

    return 0;
}
