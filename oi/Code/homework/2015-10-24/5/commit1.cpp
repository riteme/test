#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define DOLLAR_TO_MARK 1
#define MARK_TO_DOLLAR 2

struct Conversation {
    int Value = 0;
    int Date = 0;
    int ShouldBe = 0;

    float ToMark(float dollar) const { return dollar * Value; }
    float ToDollar(float mark) const { return mark / Value; }
};  // struct Conversation

int main(/*int argc, char *argv[]*/) {
    // ios::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<Conversation> con(n);
    int cnt = 1;
    for (auto &e : con) {
        cin >> e.Value;
        e.Date = cnt++;
    }  // foreach in con

    vector<Conversation *> tmp(n);
    for (int i = 0; i < tmp.size(); i++) { tmp[i] = &con[i]; }  // for

    std::sort(tmp.begin(), tmp.end(),
              [](const Conversation *a, const Conversation *b) {
                  return a->Value < b->Value;
              });

    int bound = n / 2;
    for (int i = 0; i < bound; i++) {
        tmp[i]->ShouldBe = MARK_TO_DOLLAR;
        tmp[tmp.size() - i - 1]->ShouldBe = DOLLAR_TO_MARK;
    }  // for

    float money = 100.0f;
    for (int i = 0; i < con.size(); i++) {
        if (con[i].ShouldBe == DOLLAR_TO_MARK) {
            float m = money;
            m = con[i].ToMark(money);

            int next = -1;
            int min = INT_MAX;
            for (int j = i + 1;
                 con[j].ShouldBe != DOLLAR_TO_MARK && j < con.size();
                 j++) {
                if (con[j].ShouldBe == MARK_TO_DOLLAR && con[i].Value < min) {
                    min = con[i].Value;
                    next = j;
                }
            }  // for

            if (next != -1) {
                money = con[next].ToDollar(m);
            } else if (i == con.size() - 2 && con[i + 1].ShouldBe == 0) {
                money = con[i + 1].ToDollar(m);
            }
        }
    }  // for

    printf("%.2f\n", money);

    return 0;
}  // function main
