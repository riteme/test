#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Food {
    int Weight;
    int Kind;

    bool operator<(const Food &lhs) const { return Weight < lhs.Weight; }
    bool operator>(const Food &lhs) const { return Weight > lhs.Weight; }
};  // struct Food

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n, m, k;
    cin >> n >> m >> k;

    vector<Food> foods(n);
    vector<int> max(k);

    for (int i = 0; i < k; i++) { cin >> max[i]; }  // for
    for (int i = 0; i < n; i++) {
        cin >> foods[i].Weight >> foods[i].Kind;
        foods[i].Kind--;
    }  // for

    std::sort(foods.begin(), foods.end(), std::greater<Food>());

    int sum = 0;
    int count = 0;
    vector<int> cnt(k);
    for (int i = 0; i < foods.size() && count < m; i++) {
        if (cnt[foods[i].Kind] < max[foods[i].Kind]) {
            cnt[foods[i].Kind]++;
            count++;
            sum += foods[i].Weight;
        }
    }  // for

    cout << sum;

    return 0;
}  // function main
