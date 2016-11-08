#include <cstdio>
#include <cstring>

#define A 1
#define C2 2
#define C3 3
#define C4 4
#define C5 5
#define C6 6
#define C7 7
#define C8 8
#define C9 9
#define C10 10
#define J 11
#define Q 12
#define K 13
#define SG 14
#define BG 15

inline int get_type(int x, int c) {
    if (x == 0 && c == 1)
        return SG;
    if (x == 0 && c == 2)
        return BG;
    return x;
}

class GreedySolver {
 public:
    void reset() {
        memset(cnt, 0, sizeof(cnt));
        answer = 0;
    }

    void add(int x, int c) {
        cnt[get_type(x, c)]++;
    }

    int solve() {
        put_seq(C3, J, 3, 4, 2);
        put_seq(C3, J, 3, 3, 1);
        put_seq(C3, J, 3, 2, 1);
        put_seq(C3, C9, 5, 1, 1);
        put_4_with_2();
        put_3_with_1();
        put_kings();
        put_directly();

        return answer;
    }

 private:
    void put_seq(int s, int t,
                 int minlen, int limit, int score) {
        for (int i = s; i <= t; i++) {
            int j = i;
            while (j <= K && cnt[j] >= limit)
                j++;

            if (j - i >= minlen) {
                answer += score;
                for (int k = i; k < j; k++)
                    cnt[k] -= limit;
            }
        }
    }

    bool take_1(int except, int num) {
        for (int i = A; i <= K; i++) {
            if (i == except)
                continue;

            if (cnt[i] == num) {
                cnt[i] = 0;
                return true;
            }
        }

        return false;
    }

    bool take_2(int except, int num) {
        int a = 0;
        for (int i = A; i <= K; i++) {
            if (i == except)
                continue;

            if (cnt[i] == num) {
                if (a == 0)
                    a = i;
                else {
                    cnt[a] = cnt[i] = 0;
                    return true;
                }
            }
        }

        return false;
    }

    bool take_kings() {
        if (cnt[SG] == 1 && cnt[BG] == 1) {
            cnt[SG] = cnt[BG] = 0;
            return true;
        }

        return false;
    }

    void put_4_with_2() {
        for (int i = A; i <= K; i++) {
            if (cnt[i] == 4) {
                if (take_2(i, 1) || take_2(i, 2) || take_1(i, 2) || take_kings()) {
                    answer++;
                    cnt[i] = 0;
                }
            }
        }
    }

    void put_3_with_1() {
        for (int i = A; i <= K; i++) {
            if (cnt[i] == 3) {
                if (take_1(i, 1) || take_1(i, 2)) {
                    answer++;
                    cnt[i] = 0;
                }
            }
        }
    }

    void put_kings() {
        if (cnt[SG] == 1 && cnt[BG] == 1) {
            answer++;
            cnt[SG] = cnt[BG] = 0;

            // Since we didn't consider put 3 with two kings,
            // here we do it
            if (take_2(0, 3))
                answer++;
        } else if (cnt[SG] == 1 || cnt[BG] == 1) {
            answer++;
            take_1(0, 3);
        }
    }

    void put_directly() {
        for (int i = A; i <= K; i++)
            if (cnt[i])
                answer++;
    }

    int answer;
    int cnt[16];
};

int main() {
    int T, n;
    scanf("%d%d", &T, &n);

    GreedySolver solver;
    while (T--) {
        solver.reset();

        for (int i = 0; i < n; i++) {
            int x, c;
            scanf("%d%d", &x, &c);

            solver.add(x, c);
        }

        printf("%d\n", solver.solve());
    }
}
