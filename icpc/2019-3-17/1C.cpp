#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000

static int n, m;
static int mat[NMAX + 10][NMAX + 10];
static int seq[NMAX + 10];
static int lt[NMAX + 10][NMAX + 10], gt[NMAX + 10][NMAX + 10];

inline void chkmax(int &a, int b) {
	if (b > a) a = b;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)
		scanf("%d", &mat[i][j]);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) seq[j] = j;
		sort(seq + 1, seq + m + 1, [i](int x, int y) {
			return mat[i][x] < mat[i][y];
		});
		int c = 1, a = 0;
		for (int k = 2; k <= m; k++)
			if (mat[i][seq[k]] != mat[i][seq[k - 1]]) c++;
		for (int l = 1, r = 1; l <= m; l = r + 1, a++) {
			for (r = l;
				 r < m && mat[i][seq[r]] == mat[i][seq[r + 1]]; r++) ;
			for (int k = l; k <= r; k++) {
				chkmax(lt[i][seq[k]], a);
				chkmax(gt[i][seq[k]], c - a - 1);
			}
		}
	}
	for (int j = 1; j <= m; j++) {
		for (int i = 1; i <= n; i++) seq[i] = i;
		sort(seq + 1, seq + n + 1, [j](int x, int y) {
			return mat[x][j] < mat[y][j];
		});
		int c = 1, a = 0;
		for (int k = 2; k <= n; k++)
			if (mat[seq[k]][j] != mat[seq[k - 1]][j]) c++;
		for (int l = 1, r = 1; l <= n; l = r + 1, a++) {
			for (r = l;
				 r < n && mat[seq[r]][j] == mat[seq[r + 1]][j]; r++) ;
			for (int k = l; k <= r; k++) {
				chkmax(lt[seq[k]][j], a);
				chkmax(gt[seq[k]][j], c - a - 1);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) printf("%d ", lt[i][j] + gt[i][j] + 1);
		puts("");
	}

	return 0;
}
