#include <cstdio>
#include <queue>
using namespace std;

struct road_type
{
	int l, r;
	int v;
	road_type *next;
}road[10007];
road_type *p1;

struct map_type
{
	int l, r;
	int v;
	map_type *next;
}map[10007];
map_type *p2;

struct pre_type
{
	int l, r;
	int v;
	pre_type *next;
}pre[10007];
pre_type *p3;

int hash(int x, int y)
{
	return (x + y) % 10007;
}

void givein_road(int x, int y, int v)
{
	p1 = new road_type;
	int k = hash(x, y);
	p1->l = x;
	p1->r = y;
	p1->v = v;
	p1->next =road[k].next;
	road[k].next = p1;
}

int out_road(int x, int y)
{
	int k = hash(x, y);
	p1 = road[k].next;
	while(p1)
	{
		if(p1->l == x && p1->r == y)
		{
			return p1->v;
		}
		if(p1->r == x && p1->l == y)
		{
			return p1->v;
		}
		p1 = p1->next;
	}
	return 5000000;
}

void givein_pre(int x, int y, int v)
{
	p3 = new pre_type;
	int k = hash(x, y);
	p3->l = x;
	p3->r = y;
	p3->v = v;
	p3->next =pre[k].next;
	pre[k].next = p3;
}

int out_pre(int x, int y)
{
	int k = hash(x, y);
	p3 = pre[k].next;
	while(p3)
	{
		if(p3->l == x && p3->r == y)
		{
			return p3->v;
		}
		if(p3->r == x && p3->l == y)
		{
			return p3->v;
		}
		p3 = p3->next;
	}
	return 5000000;
}

void givein_map(int x, int y, int v)
{
	p2 = new map_type;
	int k = hash(x, y);
	p2->l = x;
	p2->r = y;
	p2->v = v;
	p2->next =map[k].next;
	map[k].next = p2;
}

int out_map(int x, int y)
{
	int k = hash(x, y);
	p2 = map[k].next;
	while(p2)
	{
		if(p2->l == x && p2->r == y)
		{
			return p2->v;
		}
		if(p2->r == x && p2->l == y)
		{
			return p2->v;
		}
		p2 = p2->next;
	}
	return 5000000;
}

int dist[200005];
bool exi[200005];
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
	givein_pre(i, j, u);	
	exi[u] = true;
	men.push(u);
	while(!men.empty())
	{
		k = men.front();
		exi[k] = false;
		men.pop();
		for(i = 1; i <= n; i++)
		{
			if(dist[k] + out_road(k, i) < dist[i])
			{
				dist[i] = dist[k] + out_road(k, i);
				x = i;
				y = k;
				while(x != u)
				{
					givein_pre(i, x, y);
					x = y;
					y = out_pre(k, y);
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
	for(i = 1; i < n; i++)
	{
		scanf("%d%d%d", &a, &b, &w);
		givein_road(a, b, 1);
		givein_map(a, b, w);
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
				sum += out_map(x, out_pre(v, x));
				if(sum > max) max = sum;
				if(sum < 0) sum = 0;
				x = out_pre(v, x);
			}
			printf("%1.1d\n", max);
		}
	}
	fclose(stdin);
	fclose(stdout);
}
