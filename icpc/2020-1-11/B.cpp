#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

#define NMAX 1000

struct Team {
    Team() : swapped(false), cnt(0) {}

    string offense;
    string defense;
    bool swapped;
    int cnt;
};

int n, m;
queue<string> q;
string s;
Team t[NMAX + 10];

template <typename T>
void push(T &&name) {
    q.push(std::forward<string>(name));
}

string pop() {
    string name = q.front();
    q.pop();
    return name;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) {
        string name;
        cin >> name;
        q.push(std::move(name));
    }
    cin >> s;

    Team T[2];
    T[0].offense = pop();
    T[1].offense = pop();
    T[0].defense = pop();
    T[1].defense = pop();
    for (char c : s) {
        int i = c == 'W' ? 0 : 1;
        swap(T[i].offense, T[i].defense);
        T[i].swapped ^= 1;
        T[i].cnt++;
        t[++m] = T[i^1];
        push(T[i^1].defense);
        T[i^1].defense = T[i^1].offense;
        T[i^1].offense = pop();
        T[i^1].swapped = true;
        T[i^1].cnt = 0;
    }

    if (T[0].cnt)
        t[++m] = T[0];
    if (T[1].cnt)
        t[++m] = T[1];

    int mx = 0;
    for (int i = 1; i <= m; i++)
        mx = max(mx, t[i].cnt);

    for (int i = 1; i <= m; i++) if (t[i].cnt == mx) {
        if (t[i].swapped)
            cout << t[i].defense << " " << t[i].offense << "\n";
        else
            cout << t[i].offense << " " << t[i].defense << "\n";
    }

    return 0;
}