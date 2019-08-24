#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

vector<long long> rock;
vector<bool> s;
vector<bool> step;
vector<long long> f;

int main() {
    ios::sync_with_stdio(false);

    long long L, S, T, M;
    cin >> L >> S >> T >> M;

    rock.resize(M);
    s.resize(L + 1);
    // memset(s,false,sizeof(bool)*(L+1));

    for (int i = 0; i < M; i++) {
        cin >> rock[i];
        s[rock[i]] = true;
    }

    f.resize(L + 1);
    step.resize(L + 1);
    // memset(step,false,sizeof(bool)*(L+1));
    // memset(f,0,sizeof(int)*(L+1));

    step[0] = true;
    for (int i = 0; i <= L; i++) {
        if (step[i]) {
            for (int j = S; j <= T && i + j <= L; j++) { step[i + j] = true; }
        }
    }

    for (int i = 1; i <= L; i++) {
        if (!step[i]) continue;

        long long min = LLONG_MAX;

        int j = i - T;
        if (j < 0) { j = 0; }

        for (; j <= i - S; j++) {
            if (f[j] < min && step[j]) { min = f[j]; }
        }

        if (min == INT_MAX) min = 0;

        f[i] = min + (s[i] ? 1 : 0);
    }

    // for(int i=0;i<=L;i++){
    //  cout<<f[i]<< ' ';
    //}
    // cout<<endl;

    // for(int i=0;i<=L;i++){
    //  cout<<step[i]<< ' ';
    //}
    // cout<<endl;

    cout << f[L];

    return 0;
}
