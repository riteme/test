#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <stack>
#include <string>
#include <random>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

// #define SEED 20000926
#define SEED random_device()()

struct MyRandom {
    MyRandom() {
        srand(SEED);
    }

    int operator()() const {
        return rand();
    }
};  // struct MyRandom

static MyRandom randint;

template <typename TKey, typename TValue>
struct Node {
    typedef TKey KeyType;
    typedef TValue ValueType;

    Node(int _key = 0, int _value = 0, Node *_left = NULL,
         Node *_right = NULL) {
        key = _key;
        value = _value;
        left = _left;
        right = _right;
        size = 1;
        weight = randint();
    }

    ~Node() {
        if (!left)
            delete left;
        if (!right)
            delete right;
    }

    void update() {
        size = 1 + (left == NULL ? 0 : left->size) +
               (right == NULL ? 0 : right->size);
    }

    KeyType key;
    ValueType value;
    int weight;
    size_t size;
    Node *left;
    Node *right;

    std::string to_string() {
        stringstream buffer;
        buffer << this << ": {key = " << this->key << ", size = " << this->size
               << ", left = " << this->left << ", right = " << this->right
               << "}";

        return buffer.str();
    }

    std::string to_dot_code() {
        stringstream buffer;

        buffer << key;
        buffer << "[label=\"" << key << ": " << value << "\"]";
        buffer << ";";

        if (left != nullptr) {
            buffer << key << ":sw -> " << left->key << ";";
        }

        if (right != nullptr) {
            buffer << key << ":se -> " << right->key << ";";
        }

        return buffer.str();
    }
};  // struct Node

typedef Node<int, int> TreapNode;
typedef TreapNode *Treap;
typedef pair<Treap, Treap> TreapPair;
typedef pair<int, int> NodeData;

static Treap tree;

static void _print(Treap h) {
    if (h == NULL)
        return;

    _print(h->left);
    cout << h->to_string() << endl;
    _print(h->right);
}

static void print(Treap h) {
    cout << "Printing " << h << "..." << endl;
    _print(h);
}

static void _show(Treap h, stringstream &buffer) {
    if (!h)
        return;

    buffer << h->to_dot_code();
    _show(h->left, buffer);
    _show(h->right, buffer);
}

static void show(Treap h) {
    stringstream buffer;

    buffer << "digraph{node[shape=circle]";
    _show(h, buffer);
    buffer << "}";

    fstream file("/tmp/tree.tmp.dot", ios::trunc | ios::out);
    file << buffer.str();
    file.close();
    system("showdot /tmp/tree.tmp.dot");
}

/**
 * 由已知数据重建Treap
 * @param  data 数据
 * @return      返回重建后的Treap
 */
Treap rebuild(vector<NodeData> &data);

/**
 * 合并两个Treap
 * @param  a Treap A
 * @param  b Treap B
 * @return   返回合并后的Treap
 * @remark
 *     Treap A的最大值必须小于Treap B的最小值
 */
Treap merge(Treap a, Treap b);

/**
 * 分割Treap
 * @param  h 要被分割的Treap
 * @param  k 从第几位开始分割
 * @return   返回分割后的两个Treap
 * @remark
 *     第k小的节点会属于分割出的第一个Treap
 */
TreapPair split(Treap h, int k);

/**
 * 获取某个键在Treap中的排名
 * @param  h   目标Treap
 * @param  key 指定的键
 * @return     返回排名
 * @remark
 *     排名从小到大
 */
int rank_key(Treap h, int key);

/**
 * 查询节点
 * @param  h   目标Treap
 * @param  key 查询的键
 * @return     返回命中的节点
 * @remark
 *     如果没有命中，则返回NULL
 */
Treap query(Treap h, int key);

/**
 * 插入节点
 * @param  h     目标Treap
 * @param  key   键
 * @param  value 值
 * @return       返回插入完成后的Treap
 */
Treap insert(Treap h, int key, int value);

/**
 * 删除节点
 * @param  h   目标Treap
 * @param  key 键
 * @return     返回删除完成后的Treap
 */
Treap remove(Treap h, int key);

/**
 * 查询第k小的节点
 * @param  h 目标Treap
 * @param  k 排名值
 * @return   返回第k小的节点
 */
Treap get_kth(Treap h, int k);

/**
 * 截取一段区间，并通过`show`函数展示出来
 * @param h     目标Treap
 * @param left  左端点
 * @param right 右端点
 * @remark
 *     左右端点为排名序号。
 *     输出的区间为闭区间：[left, right]
 *     此操作不会对目标Treap产生影响
 */
void slice(Treap h, int left, int right);  // [left, right]

int main() {
    string command;
    vector<NodeData> data;

    cout << "$ ";
    while (cin >> command) {
        if (command == "query") {
            int key;
            cin >> key;

            Treap node = query(tree, key);

            if (node == NULL)
                cout << "404 NOT FOUND" << endl;
            else
                cout << node->to_dot_code() << endl;
        } else if (command == "record") {
            int key, value;
            cin >> key >> value;

            data.push_back({ key, value });
        } else if (command == "build") {
            if (!tree)
                delete tree;

            tree = rebuild(data);
            data.clear();
        } else if (command == "insert") {
            int key, value;
            cin >> key >> value;

            tree = insert(tree, key, value);
        } else if (command == "remove") {
            int key;
            cin >> key;

            tree = remove(tree, key);
        } else if (command == "split") {
            int k;
            cin >> k;

            TreapPair p = split(tree, k);
            print(p.first);
            show(p.first);
            print(p.second);
            show(p.second);
            tree = merge(p.first, p.second);
        } else if (command == "rank") {
            int key;
            cin >> key;

            cout << rank_key(tree, key) << endl;
        } else if (command == "k") {
            int k;
            cin >> k;

            Treap node = get_kth(tree, k);
            cout << node->to_string() << endl;
        } else if (command == "slice") {
            int left, right;
            cin >> left >> right;

            slice(tree, left, right);
        } else if (command == "print")
            print(tree);
        else if (command == "show")
            show(tree);
        else {
            cout << "Command not found: " << command << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "$ ";
    }  // while

    return 0;
}  // function main

inline size_t size(Treap h) {
    if (!h)
        return 0;
    else
        return h->size;
}

Treap rebuild(vector<NodeData> &data) {
    sort(data.begin(), data.end());

    stack<Treap> s;

    for (auto &e : data) {
        int key = e.first;
        int value = e.second;
        Treap node = new TreapNode(key, value);

        while (!s.empty() && s.top()->weight >= node->weight) {
            s.top()->right = node->left;
            s.top()->update();
            node->left = s.top();
            s.pop();
        }

        node->update();
        if (!s.empty())
            s.top()->right = node;
        s.push(node);
    }  // foreach in data

    while (s.size() > 1)
        s.pop();

    return s.top();
}

Treap merge(Treap a, Treap b) {
    if (!a)
        return b;
    if (!b)
        return a;

    assert(a->key <= b->key);
    if (a->weight < b->weight) {
        a->right = merge(a->right, b);
        a->update();

        return a;
    } else {
        b->left = merge(a, b->left);
        b->update();

        return b;
    }
}

TreapPair split(Treap h, int k) {
    if (h == NULL)
        return TreapPair(NULL, NULL);

    TreapPair result;
    if (k <= size(h->left)) {
        result = split(h->left, k);
        h->left = result.second;
        h->update();
        result.second = h;
    } else {
        result = split(h->right, k - size(h->left) - 1);
        h->right = result.first;
        h->update();
        result.first = h;
    }

    return result;
}

int rank_key(Treap h, int key) {
    if (h == NULL)
        return 1;

    if (key < h->key)
        return rank_key(h->left, key);
    else if (key > h->key)
        return size(h->left) + 1 + rank_key(h->right, key);
    else
        return size(h->left) + 1;
}

Treap query(Treap h, int key) {
    if (h == NULL)
        return NULL;

    if (key < h->key)
        return query(h->left, key);
    else if (key > h->key)
        return query(h->right, key);
    else
        return h;
}

Treap insert(Treap h, int key, int value) {
    if (h == NULL)
        return new TreapNode(key, value);

    int k = rank_key(h, key);
    TreapPair a = split(h, k - 1);
    Treap node = new TreapNode(key, value);

    return merge(merge(a.first, node), a.second);
}

Treap remove(Treap h, int key) {
    int k = rank_key(h, key);

    TreapPair a = split(h, k - 1);
    TreapPair b = split(a.second, 1);
    delete b.first;

    return merge(a.first, b.second);
}

Treap get_kth(Treap h, int k) {
    TreapPair a = split(h, k);
    TreapPair b = split(a.first, k - 1);
    Treap node = b.second;

    merge(merge(b.first, b.second), a.second);

    return node;
}

void slice(Treap h, int left, int right) {
    TreapPair a = split(h, left - 1);
    TreapPair b = split(a.second, right - left + 1);

    show(b.first);
    merge(a.first, merge(b.first, b.second));
}
