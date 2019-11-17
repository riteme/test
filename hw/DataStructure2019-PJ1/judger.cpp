#include <bits/stdc++.h>
using namespace std; 

#define LOG

const int maxn = 10006; 

int n, m, k; 
int a[maxn]; 
FILE *f;
#ifdef LOG
FILE *log_file;
int log_status = 0;
#endif

bool check(int x, int y) {
	if (x <= 0 || x > n || y <= 0 || y > n) {
		fprintf(stderr, "x or y range error: %d %d", x, y); 
		printf("-1\n");
		fflush(stdout);
		return false; 
	}
	return true; 
}

bool get(int &x, int &y) {
	if (!(cin>>x>>y)) {
		fprintf(stderr, "reached EOF!"); 
		printf("-1\n");
		fflush(stdout);
		return false; 
	}
	#ifdef LOG
	fprintf(log_file, "%s%-8d%-8d    |", log_status ? "\n" : "", x, y);
	log_status = 1;
	#endif
	return true; 
}

void put(int x) {
	printf("%d\n", x);
	fflush(stdout);
	#ifdef LOG
	fprintf(log_file, "%s%d\n", log_status ? "" : "                    |", x);
	log_status = 0;
	#endif
}

int main(int argc, char **argv) {
	#ifdef LOG
	log_file = fopen("log.txt", "w");
	fprintf(log_file, "Solver              |Judger\n");
	#endif
	
	string inputfile = "data/0.in"; 

	if (argc > 2){
		fprintf(stderr, "Too many arguments! Should input 0 or 1 argument.");
		printf("-1\n");
		fflush(stdout);
		return 1;
	}
	else if (argc == 2){
		inputfile = argv[1];
		//fprintf(stderr, "|%s|", inputfile.c_str()); 
	}

	f = fopen(inputfile.c_str(), "r");
	fscanf(f, "%d%d", &n, &k); 
	for (int i = 1; i <= n; ++i) fscanf(f, "%d", &a[i]);
	std::ios::sync_with_stdio(false);
	/*
	n = 10000; 
	for (int i = 1; i <= n; ++i) a[i] = i; 
	k = 100; 
	for (int i = 1; i <= k; ++i) {
		int x = rand() % n + 1; 
		int y = rand() % n + 1; 
		swap(a[x], a[y]); 
	}
	*/
	put(n);
	int score = 0; 
	int x, y; 
	while (1) {
		if (!get(x,y)) return 1; 
		if (x == 0 && y == 0) break; 
		if (!check(x,y)) return 1; 
		/*
		if (x == y)	{
			fprintf(stderr, "x is same as y : %d %d\n", x, y); 
			return 1; 
		}
		*/
		put(a[x] < a[y]);
		score++; 
		if (score > 500000){
			fprintf(stderr, "Too many asks!"); 
			printf("-1\n");
			fflush(stdout);
			return 1; 
		}
	}
	cin>>m; 
	if (m > k) {
		fprintf(stderr, "Too many swaps!"); 
		printf("-1\n");
		fflush(stdout);
		return 1; 
	}
	while (m--) {
		if (!get(x,y)) return 1; 
		if (!check(x,y)) return 1; 
		swap(a[x], a[y]); 
	}
	for (int i = 1; i < n; ++i)
		if (a[i] > a[i+1]) {
			fprintf(stderr, "Array not in order!" ); 
			printf("-1\n");
			fflush(stdout);
			return 1;
		}
	printf("%d\n", score);
	fprintf(stderr, "Passed! Asks: %d", score); 
	fflush(stderr);
	return 0; 
}
