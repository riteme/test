#include <bits/stdc++.h>
using namespace std;

int a, b, res1, res2, res3;

int main(){
	cin >> a >> b;
	res1 = a - (-b);
	res2 = (a & b) + (a | b);
	res3 = (a ^ b) + ((a & b) << 1);
	if (res1 != res2 || res2 != res3 || res3 != res1) return a + b;
	cout << res1 + res2 - res3 << '\n';
	return 0;
}
