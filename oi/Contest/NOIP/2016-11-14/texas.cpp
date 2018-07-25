#include <cctype>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

struct State {
    vector<int> cards;

    void sort() {
        std::sort(cards.begin(), cards.end());
    }

    bool empty() const {
        return cards.empty();
    }

    bool is_seq() const {
        const int seq[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 1, 10, 11, 12, 13};

        for (int i = 0; i <= 13; i++) {
            bool result = true;

            for (int j = 0; j < 5; j++)
                if (seq[i + j] != cards[j])
                    result = false;

            if (result)
                return true;
        }

        return false;
    }

    int type() const {
        if ((cards[0] == cards[1] && cards[0] == cards[2] && cards[0] == cards[3]) ||
            (cards[4] == cards[1] && cards[4] == cards[2] && cards[4] == cards[3]))
            return 1;
        else if ((cards[0] == cards[1] && cards[0] == cards[2] && cards[3] == cards[4]) ||
                 (cards[2] == cards[3] && cards[2] == cards[4] && cards[0] == cards[1]))
            return 2;
        else if (is_seq())
            return 3;
        else if ((cards[0] == cards[1] && cards[0] == cards[2]) || (cards[1] == cards[2] && cards[1] == cards[3]) ||
                 (cards[2] == cards[3] && cards[2] == cards[4]))
            return 4;
        else if ((cards[0] == cards[1] && cards[2] == cards[3]) || (cards[0] == cards[1] && cards[3] == cards[4]) ||
                 (cards[1] == cards[2] && cards[3] == cards[4]))
            return 5;
        else if (cards[0] == cards[1] || cards[1] == cards[2] || cards[2] == cards[3] || cards[3] == cards[4])
            return 6;
        return 7;
    }

    bool operator<(const State &b) const {
        if (empty())
            return true;
        if (b.empty())
            return false;

        int mytype = type();
        int btype = b.type();

        if (mytype < btype)
            return false;
        else if (mytype > btype)
            return true;
        else {
            int myacnt = 0;
            int bacnt = 0;

            if (mytype != 3 || cards[1] != 2) {
                while (myacnt <= 4 && cards[myacnt] == 1)
                    myacnt++;
                while (bacnt <= 4 && b.cards[bacnt] == 1)
                    bacnt++;

                if (myacnt < bacnt)
                    return true;
                else if (myacnt > bacnt)
                    return false;
            }

            for (int i = 4; i >= myacnt; i--) {
                if (cards[i] == b.cards[i])
                    continue;
                return cards[i] < b.cards[i];
            }

            return false;
        }
    }
};

static char buffer[100][100];
static int code[100];

inline int convert(const char *str) {
    if (isdigit(str[0]))
        return atoi(str);
    if (str[0] == 'A')
        return 1;
    if (str[0] == 'J')
        return 11;
    if (str[0] == 'Q')
        return 12;
    if (str[0] == 'K')
        return 13;
    return 0;
}

int main() {
    freopen("texas.in", "r", stdin);
    freopen("texas.out", "w", stdout);

    scanf("%s%s%s%s%s%s%s", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6]);
    for (int i = 0; i < 7; i++)
        code[i] = convert(buffer[i]);
       
    vector<State> all;
    for (int n1=0; n1<2; n1++){
    for (int n2=0; n2<2; n2++){
    for (int n3=0; n3<2; n3++){
    for (int n4=0; n4<2; n4++){
    for (int n5=0; n5<2; n5++){
    for (int n6=0; n6<2; n6++){
    for (int n7=0; n7<2; n7++){
        if (n1 + n2 + n3 + n4 + n5 + n6 + n7 == 5) {
            State s;

            if (n1) s.cards.push_back(code[0]);
            if (n2) s.cards.push_back(code[1]);
            if (n3) s.cards.push_back(code[2]);
            if (n4) s.cards.push_back(code[3]);
            if (n5) s.cards.push_back(code[4]);
            if (n6) s.cards.push_back(code[5]);
            if (n7) s.cards.push_back(code[6]);
            s.sort();
            all.push_back(s);
        }
    }}}}}}}

    sort(all.begin(), all.end());
    State &best = *all.rbegin();
    if (best.type() == 3 && best.cards[0] == 1 && best.cards[1] == 2) {
        puts("5 4 3 2 A");
    } else {
        int acnt = 0;
        while (acnt <= 4 && best.cards[acnt] == 1)
            acnt++;
        for (int i = 0; i < acnt; i++)
            printf("A ");
        for (int i = 4; i >= acnt; i--) {
            int &c = best.cards[i];

            if (c == 11)
                printf("J ");
            else if (c == 12)
                printf("Q ");
            else if (c == 13)
                printf("K ");
            else
                printf("%d ", c);
        }
    }

    return 0;
}
