#include <cstdio>
#include <vector>

using namespace std;

// 1011, 2386, 2488

static int n;
static vector<int> s;
static vector<bool> marked;

void dfs(int &cnt, int target, int sum, bool &status) {
    // if(status) return;
    // if (cnt > n) return;

    for (int i = 1; i <= n and !status; i++) {
        if (!marked[i] and sum + s[i] <= target) {
            marked[i] = true;
            cnt++;
            sum += s[i];

            if (sum == target) {
                // cout << "i: " << i << endl
                //      << "Searched." << endl;
                status = true;
                return;
            } else {
                // cout << "DFS: i: " << i << ", cnt: " << cnt << ", sum: " <<
                // sum
                //      << endl;
                dfs(cnt, target, sum, status);
            }

            if (status) return;

            sum -= s[i];
            marked[i] = false;
            cnt--;
        }
    }
}

bool dfs(int &cnt, int target) {
    // if (cnt == n) return true;

    static bool status;
    status = false;

    dfs(cnt, target, 0, status);

    return status;
}

int main() {
    while (true) {
        scanf("%d", &n);

        if (n == 0) { break; }

        s.resize(n + 1);
        marked.resize(n + 1);
        int m = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &s[i]);
            if (s[i] > m) m = s[i];
        }

        int result = 0;
        int cnt = 0;
        for (int j = m; j <= 50; j++) {
            for (int i = 1; i <= n; i++) marked[i] = false;
            bool flag = true;

            while (cnt < n) {
                // cout << "cnt: " << cnt << endl;
                // for (int i = 1; i <= n; i++) { cout << marked[i]; }  // for
                // cout << endl;

                if (!dfs(cnt, j)) {
                    flag = false;
                    break;
                }
            }

            if (flag) {
                result = j;
                break;
            }
        }

        printf("%d\n", result);
        // cout << result << endl;
    }

    return 0;
}  // function main
