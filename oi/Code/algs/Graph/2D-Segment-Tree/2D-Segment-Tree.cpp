//
// Copyright 2015 riteme
//

#include <sstream>
#include <iostream>

using namespace std;

struct Rectangle {
    Rectangle() : left(0), right(0), top(0), bottom(0) {}
    Rectangle(int l, int r, int t, int b) {
        if (l > r or t > b) {
            left = right = top = bottom = 0;
        } else {
            left = l;
            right = r;
            top = t;
            bottom = b;
        }
    }

    Rectangle(const Rectangle &a) = default;
    Rectangle &operator=(const Rectangle &a) = default;
    Rectangle(Rectangle &&a) = default;
    Rectangle &operator=(Rectangle &&a) = default;

    int left;
    int right;
    int top;
    int bottom;

    bool IsEmpty() const {
        return left == 0 and right == 0 and top == 0 and bottom == 0;
    }

    bool IsUnit() const {
        return left == right and top == bottom;
    }

    auto ToString() const -> std::string {
        ostringstream ss;
        ss << "Rectangle: {left = " << left << ", right = " << right
           << ", top = " << top << ", bottom = " << bottom << "}";

        return ss.str();
    }
};  // struct Rectangle

struct RemoteData {
    RemoteData() = default;
    RemoteData(const RemoteData &a) = default;
    RemoteData &operator=(const RemoteData &a) = default;
    RemoteData(RemoteData &&a) = default;
    RemoteData &operator=(RemoteData &&a) = default;

    auto ToString() const -> std::string {
        return "<Nothing>";
    }
};  // struct RemoteData

struct Node {
    Node() {
        child[0] = nullptr;
        child[1] = nullptr;
        child[2] = nullptr;
        child[3] = nullptr;
        parent = nullptr;
    }

    Node(const Node &a) = default;
    Node &operator=(const Node &a) = default;
    Node(Node &&a) = default;
    Node &operator=(Node &&a) = default;

    Rectangle range;
    RemoteData data;
    Node *child[4];
    Node *parent;

    auto ToString() const -> std::string {
        ostringstream ss;
        ss << "Node at " << hex << this << ": {range = " << range.ToString()
           << ", data = " << data.ToString() << ", child[4] = {" << child[0]
           << ", " << child[1] << ", " << child[2] << ", " << child[3]
           << "}, parent = " << parent << "}";

        return ss.str();
    }
};  // struct Node

inline bool IsContain(const Rectangle &rect1, const Rectangle &rect2) {
    return rect1.left <= rect2.left and rect1.right >= rect2.right and
           rect1.top <= rect2.top and rect1.bottom >= rect2.bottom;
}

inline auto Intersect(const Rectangle &rect1, const Rectangle &rect2)
    -> Rectangle {
    int nleft = max(rect1.left, rect2.left);
    int nright = min(rect1.right, rect2.right);
    int ntop = max(rect1.top, rect2.top);
    int nbottom = min(rect1.bottom, rect2.bottom);

    return Rectangle(nleft, nright, ntop, nbottom);
}

inline void Split(const Rectangle &rect, Rectangle *dest) {
    int midx = (rect.left + rect.right) / 2;
    int midy = (rect.top + rect.bottom) / 2;

    dest[0] = Rectangle(rect.left, midx, rect.top, midy);
    dest[1] = Rectangle(midx + 1, rect.right, rect.top, midy);
    dest[2] = Rectangle(rect.left, midx, midy + 1, rect.bottom);
    dest[3] = Rectangle(midx + 1, rect.right, midy + 1, rect.bottom);
}

void PrintTree(Node *x);
Node *BuildTree(const Rectangle range);

static Node *tree;

int main() {
    ios::sync_with_stdio(false);

    int left, right, top, bottom;
    cout << "Enter a rectangle: (left, right, top, bottom)" << endl;
    cin >> left >> right >> top >> bottom;

    Rectangle r = Rectangle(left, right, top, bottom);

    // Rectangle subrect[4];
    // Split(r, subrect);

    // for (auto &e : subrect) {
    // cout << e.ToString() << endl;
    // }  // foreach in subrect

    tree = BuildTree(r);
    PrintTree(tree);

    return 0;
}  // function main

void PrintTree(Node *x) {
    if (x == nullptr)
        return;

    cout << x->ToString() << endl;

    for (auto &child : x->child) {
        PrintTree(child);
    }  // foreach in x->child
}

Node *BuildTree(const Rectangle range) {
    if (range.IsEmpty()) {
        return nullptr;
    }

    Node *x = new Node();
    x->range = range;

    if (range.IsUnit()) {
        return x;
    }

    Rectangle subrect[4];
    Split(range, subrect);

    Node **ptr = &(x->child[0]);
    for (auto &rect : subrect) {
        // cout << rect.ToString() << endl;
        *ptr = BuildTree(rect);

        if (*ptr != nullptr)
            (*ptr)->parent = x;

        ptr++;
    }  // foreach in subrect

    // cout << x->ToString() << endl;

    return x;
}
