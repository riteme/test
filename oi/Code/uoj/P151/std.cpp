#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int N;
class poi {
public:
	int n;
	int cd[15];
	void a0() {
		memset(cd, 0, sizeof(cd));
	}
	void count() {
		n = 0;
		for (int i = 0; i <= 14; i++)
			n += cd[i];
	}
	void rin() {
		a0();
		n = N;
		int a, b;
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &a, &b);
			if (2 <= a && a <= 13)
				cd[a]++;
			else if (a == 1)
				cd[14]++;
			else {
				cd[b-1]++;
			}
		}
	}
	void get(int *nb) {
		for (int i = 0; i <= 14; i++)
			nb[cd[i]]++;
		nb[0] = 0;
		if (cd[0])
			nb[0]++;
		if (cd[1])
			nb[0]++;
	}
};
poi A;
int ans;
int sss[4] = {0, 5, 3, 2};
void DFS(poi a, int t) {
	if (t >= ans)
		return;
	a.count();
	if (a.n == 0) {
		ans = t;
		return;
	}
	poi c;
	int u;
	int xxx;
	//+++
	int nb[5] = {0};
	a.get(nb);
	u = 0;
	while (nb[4] && nb[2]>1) nb[4]--,nb[2]-=2,u++;
	while (nb[4] && nb[1]>1) nb[4]--,nb[1]-=2,u++;
	while (nb[4] && nb[3]) {
		nb[3]--;
		nb[2]++;
		nb[1]++;
		while (nb[4] && nb[2]>1) nb[4]--,nb[2]-=2,u++;
		while (nb[4] && nb[1]>1) nb[4]--,nb[1]-=2,u++;
		while (nb[3] && nb[2]) nb[3]--,nb[2]--,u++;
		while (nb[3] && nb[1]) nb[3]--,nb[1]--,u++;
	}
	while (nb[3] && nb[2]) nb[3]--,nb[2]--,u++;
	while (nb[3] && nb[1]) nb[3]--,nb[1]--,u++;
	while (nb[4]>1 && nb[3]>1) nb[4]-=2,nb[3]-=2,u+=2;
	while (nb[3]>1) {
		nb[3]--;
		nb[2]++;
		nb[1]++;
		while (nb[4] && nb[2]>1) nb[4]--,nb[2]-=2,u++;
		while (nb[4] && nb[1]>1) nb[4]--,nb[1]-=2,u++;
		while (nb[3] && nb[2]) nb[3]--,nb[2]--,u++;
		while (nb[3] && nb[1]) nb[3]--,nb[1]--,u++;
	}
	while (nb[4] && nb[2]) nb[4]--,nb[2]--,u++;
	while (nb[4]>1) nb[4]-=2,u++;
	u += nb[1] + nb[2] + nb[3] + nb[4];
	if (nb[0] == 2 && nb[1] >= 2)
		u--;
	ans = min(t+u, ans);
	//shun
	for (int kkk = 3; kkk >= 1; kkk--) {
		u = 0;
		xxx = sss[kkk];
		for (int i = 3; i <= 14; i++) {
			if (a.cd[i] >= kkk)
				u++;
			else {
				for (int j = u; j >= xxx; j--) {
					for (int k = i-u; k+j <= i; k++) {
						c = a;
						for (int ii = k+j-1; ii >= k; ii--)
							c.cd[ii] -= kkk;
						DFS(c, t+1);
					}
				}
				u = 0;
			}
		}
		for (int j = u; j >= xxx; j--) {
			for (int k = 15-u; k+j <= 15; k++) {
				c = a;
				for (int ii = k+j-1; ii >= k; ii--)
					c.cd[ii] -= kkk;
				DFS(c, t+1);
			}
		}
	}
}
void work() {
	A.rin();
	ans = N;
	DFS(A, 0);
	printf("%d\n", ans);
}
int main() {
	int T;
	scanf("%d %d", &T, &N);
	while (T--) {
		work();
	}
	return 0;
}
