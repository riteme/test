#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;
set<int> country[10];
int n,t[10],k[10];
int main() {
    freopen("port.in", "r", stdin);
    freopen("port.out", "w", stdout);
    cin >> n;
    
    for(int i = 0; i <= n; i++) {
        cin >> t[i] >> k[i];

        for(int j = 0; j <= k[i-1]; j++) {
            int tempt;
            cin >> tempt;
            country[i].insert(tempt);
        }
    }

    for(int i = 1; i <= n; i++) {
        int temp = t[i] + 86400, j = i + 1;
        set<int> tem = country[i];

        while(t[j++] <= temp&&j<n) tem.insert(country[j].begin(), country[j].end());

        cout << tem.size() << endl;
    }

    return 0;
}
