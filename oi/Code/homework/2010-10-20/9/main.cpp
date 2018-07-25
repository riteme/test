#include <cstring>
#include <iostream>
#include <bitset>
#include <list>

using namespace std;

#define N_QUESTION 10
#define N_SCORE 10

typedef bitset<N_QUESTION> AnswerType;

struct Paper {
    Paper() : Answer(), Score(-1) {}
    Paper(const string &answer, int score) : Answer(answer), Score(score) {}

    AnswerType Answer;
    int Score;
};  // struct Paper

int Check(const AnswerType &answer, const AnswerType &standard);

list<AnswerType> GetStandard(const Paper &s, const Paper &p1, const Paper &p2);
void Try(const Paper &s, const Paper &p1, const Paper &p2, int depth, int n,
         bool *marked, list<AnswerType> &result);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    Paper p1 = { "0010100100", 7 * N_SCORE };
    Paper p2 = { "0111010111", 5 * N_SCORE };
    Paper p3 = { "0111000101", 3 * N_SCORE };
    Paper p4 = { "0011100111", -1 };

    auto standards = GetStandard(p1, p2, p3);
    // auto standards = GetStandard(p2, p3, p1);
    // auto standards = GetStandard(p3, p1, p2);

    for (auto &e : standards) {
        cout << "Standard: " << e.to_string()
             << " / Score: " << Check(p4.Answer, e) << endl;
    }  // foreach in standards

    return 0;
}  // function main

int Check(const AnswerType &answer, const AnswerType &standard) {
    return (N_QUESTION - (answer ^ standard).count()) * N_SCORE;
}

list<AnswerType> GetStandard(const Paper &s, const Paper &p1, const Paper &p2) {
    int n = (N_QUESTION * N_SCORE - s.Score) / N_SCORE;
    bool marked[N_QUESTION];
    list<AnswerType> result;

    memset(marked, false, sizeof(bool) * N_QUESTION);

    Try(s, p1, p2, 0, n, marked, result);

    return result;
}

void Try(const Paper &s, const Paper &p1, const Paper &p2, int depth, int n,
         bool *marked, list<AnswerType> &result) {
    if (depth == n) {
        AnswerType tmp = s.Answer;

        for (int i = 0; i < N_QUESTION; i++) {
            if (marked[i]) { tmp.flip(i); }
        }  // for

        if (Check(p1.Answer, tmp) == p1.Score &&
            Check(p2.Answer, tmp) == p2.Score) {
            result.push_back(tmp);
        }
    }

    for (int i = 0; i < N_QUESTION; i++) {
        if (!marked[i]) {
            marked[i] = true;

            Try(s, p1, p2, depth + 1, n, marked, result);

            marked[i] = false;
        }
    }  // for
}
