#include <cstdio>
#include <queue>
using namespace std;

int road[2005][2005];
int map[2005][2005];
int pre[2005][2005];
int dist[2005];
bool exi[2005];
int n, m;
queue<int> men;

void SPFA(int u, int v)
{
	int i, j, k;
	int x, y;
	for(i = 1; i <= n; i++)
	dist[i] = 500000;
	dist[u] = 0;
	for(i = 1; i <= n; i++)
	for(j = 1; j <= n; j++)
	pre[i][j] = u;
	exi[u] = true;
	men.push(u);
	while(!men.empty())
	{
		k = men.front();
		exi[k] = false;
		men.pop();
		for(i = 1; i <= n; i++)
		{
			if(dist[k] + road[k][i] < dist[i])
			{
				dist[i] = dist[k] + road[k][i];
				x = i;
				y = k;
				while(x != u)
				{
					pre[i][x] = y;
					x = y;
					y = pre[k][y];
				}
				if(!exi[i])
				{
					exi[i] = true;
					men.push(i);
				}
			}
		}
	}
}

int main()
{
	freopen("campus.in", "r", stdin);
	freopen("campus.out", "w", stdout);
	int a, b, w;
	int u, v;
	int i, j, k;
	int x;
	int sum, max;
	scanf("%d%d", &n, &m);
	for(i = 1; i <= n; i++)
	for(j = 1; j <= n; j++)
	road[i][j]= 500000;
	for(i = 1; i < n; i++)
	{
		scanf("%d%d%d", &a, &b, &w);
		road[a][b] = 1;
		road[b][a] = 1;
		map[a][b] = w;
		map[b][a] = w;
	}
	for(i = 1; i <= m; i++)
	{
		scanf("%d%d", &u, &v);
		SPFA(u, v);
		if(dist[v] == 0) printf("0\n");
		else
		{
			max = -5000000;
			sum = 0;
			x = v;
			while(x != u)
			{
				sum += map[x][pre[v][x]];
				if(sum > max) max = sum;
				if(sum < 0) sum = 0;
				x = pre[v][x];
			}
			printf("%1.1d\n", max);
		}
	}
	fclose(stdin);
	fclose(stdout);
}
