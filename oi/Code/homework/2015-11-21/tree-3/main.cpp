#include <cstring>
#include <cmath>
#include <iostream>

using namespace std;

#define TREE_MAX_HEIGHT 11
#define TREE_MAX_WIDTH 1024

#define F 'F'
#define B 'B'
#define I 'I'

static int n;
static string data;
static char tree[TREE_MAX_HEIGHT + 5][TREE_MAX_WIDTH + 5];

inline int left(int x) { return x * 2 - 1; }
inline int right(int x) { return x * 2; }
inline int parent(int x) { return x % 2 ? x / 2 + 1 : x / 2; }
inline char to_symbol(char x) { return x == '0' ? B : I; }

inline char combine(char x, char y) {
    if (x == F or y == F) return F;  // F + B = F + I = F + F = F
    if (x == y) return x;            // I + I = I, B + B = B
    return F;                        // B + I = I + B = F
}

char print_tree(int left, int right) {
    if (left + 1 == right) {
        char c = to_symbol(data[left]);
        cout << c;

        return c;
    }

    int mid = (left + right) / 2;
    char l = print_tree(left, mid);
    char r = print_tree(mid, right);
    char mixed = combine(l, r);

    cout << mixed;
    return mixed;
}

int main() {
    ios::sync_with_stdio(false);

    cin >> n;
    cin >> data;

    print_tree(0, data.size());

    return 0;
}  // function main
