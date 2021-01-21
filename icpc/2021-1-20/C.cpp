#include <cstdio>

int n;

void dfs(int k) {
	if (n <= 0)
		return; 
	if (k > 20)
		return;
	dfs(k + 1);
	if (n <= 0)
		return; 
	printf("%d ", k);
	n--;
	dfs(k + 1);
}

int main() {
	scanf("%d", &n);
	dfs(1);
	puts("");
	return 0;
}
