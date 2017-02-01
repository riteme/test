/* This is sample grader for the contestant */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cassert>
#include <set>
#include <map>
#include <vector>
#include "isomorphism.h"
using namespace std;

bool proposed;
graph graph_a, graph_b;
bool result[6 + 1];

const int P = 1000000007;

void quit_msg(const char *s)
{
	cout << s << endl;
	exit(0);
}

void print_graph(graph g)
{
	cout << g.n << " " << g.e.size() << endl;
	for (int i = 0; i < (int)g.e.size(); i++)
		cout << g.e[i].first << " " << g.e[i].second << endl;
}
void print_vector(vector<int> v)
{
	cout << v.size() << endl;
	for (int i = 0; i < (int)v.size(); i++)
		cout << v[i] << " ";
	cout << endl;
}

bool validate_graph(graph g)
{
	if (g.n < 1 || g.n > 50)
		return false;
	vector<int> bel;
	for (int v = 0; v < g.n; v++)
		bel.push_back(v);
	set< pair<int, int> > es;
	for (int i = 0; i < (int)g.e.size(); i++)
	{
		if (1 > g.e[i].first || g.e[i].first > g.n)
			return false;
		if (1 > g.e[i].second || g.e[i].second > g.n)
			return false;
		if (g.e[i].first == g.e[i].second)
			return false;
		if (es.count(g.e[i]) || es.count(make_pair(g.e[i].second, g.e[i].first)))
			return false;
		es.insert(g.e[i]);

		if (bel[g.e[i].first - 1] != bel[g.e[i].second - 1])
		{
			int b = bel[g.e[i].first - 1];
			for (int v = 0; v < g.n; v++)
				if (bel[v] == b)
					bel[v] = bel[g.e[i].second - 1];
		}
	}
	for (int v = 0; v < g.n; v++)
		if (bel[v] != bel[0])
			return false;
	return true;
}

graph shuffled_graph(graph g)
{
	random_shuffle(g.e.begin(), g.e.end());
	vector<int> lab;
	for (int v = 1; v <= g.n; v++)
		lab.push_back(v);
	random_shuffle(lab.begin(), lab.end());
	for (int i = 0; i < (int)g.e.size(); i++)
	{
		if (rand() % 2 == 0)
			swap(g.e[i].first, g.e[i].second);
		g.e[i].first = lab[g.e[i].first - 1];
		g.e[i].second = lab[g.e[i].second - 1];
	}
	return g;
}

graph sorted_graph(graph g)
{
	for (int i = 0; i < (int)g.e.size(); i++)
		if (g.e[i].first > g.e[i].second)
			swap(g.e[i].first, g.e[i].second);
	sort(g.e.begin(), g.e.end());
	return g;
}

bool graph_equal(graph a, graph b)
{
	return a.n == b.n && a.e == b.e;
}

vector<vector<int> > nxn_matrix(int n)
{
	vector< vector<int> > a;
	for (int v = 0; v < n; v++)
	{
		a.push_back(vector<int>());
		for (int u = 0; u < n; u++)
			a[v].push_back(0);
	}
	return a;
}

vector<vector<int> > adjacency_matrix(graph g)
{
	vector< vector<int> > a = nxn_matrix(g.n);
	for (int i = 0; i < (int)g.e.size(); i++)
	{
		a[g.e[i].first - 1][g.e[i].second - 1] = 1;
		a[g.e[i].second - 1][g.e[i].first - 1] = 1;
	}
	return a;
}

vector<vector<int> > matrix_mod_mult(vector< vector<int> > a, vector< vector<int> > b)
{
	int n = (int)a.size();
	vector< vector<int> > c = nxn_matrix(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				c[i][j] = (c[i][j] + (long long)a[i][k] * b[k][j]) % P;
	return c;
}

int hash_graph(graph g)
{
	vector< vector<int> > matA = adjacency_matrix(g);
	vector< vector<int> > matS = matA;

	vector<int> diag;
	for (int v = 0; v < g.n; v++)
		diag.push_back(0);
	for (int i = 0; i < g.n; i++)
	{
		matS = matrix_mod_mult(matS, matA);
		for (int v = 0; v < g.n; v++)
			diag[v] = ((long long)diag[v] * 13331 + 342605723 + matS[v][v]) % P;
	}

	sort(diag.begin(), diag.end());

	int code = 0;
	for (int v = 0; v < (int)diag.size(); v++)
		code = ((long long)code * 1324321 + 816334567 + diag[v]) % P;
	return code;
}

vector<int> sorted_vector(vector<int> v)
{
	sort(v.begin(), v.end());
	return v;
}

struct colored_graph
{
	graph g;
	vector< vector<int> > ncol;
	vector<int> col;

	void init_color()
	{
		ncol.clear();
		ncol.resize(g.n);
		col.clear();
		col.resize(g.n);
		for (int v = 0; v < g.n; v++)
		{
			ncol[v].push_back(0);
			col[v] = 0;
		}
	}

	void relabel(map<vector<int>, int> &m)
	{
		col.clear();
		col.resize(g.n);
		for (int v = 0; v < g.n; v++)
		{
			if (!m.count(ncol[v]))
				m[ncol[v]] = m.size();
			col[v] = m[ncol[v]];
			ncol[v].clear();
			ncol[v].push_back(col[v]);
		}
	}
	void push_neighbor()
	{
		ncol.clear();
		ncol.resize(g.n);
		for (int i = 0; i < (int)g.e.size(); i++)
		{
			ncol[g.e[i].first - 1].push_back(col[g.e[i].second - 1]);
			ncol[g.e[i].second - 1].push_back(col[g.e[i].first - 1]);
		}
		for (int v = 0; v < g.n; v++)
		{
			sort(ncol[v].begin(), ncol[v].end());
			ncol[v].push_back(col[v]);
		}
	}
	void push_distance()
	{
		ncol.clear();
		ncol.resize(g.n);

		vector< vector<int> > d = nxn_matrix(g.n);
		for (int v = 0; v < g.n; v++)
			for (int u = 0; u < g.n; u++)
				if (v != u)
					d[v][u] = g.n;
		for (int i = 0; i < (int)g.e.size(); i++)
		{
			d[g.e[i].first - 1][g.e[i].second - 1] = 1;
			d[g.e[i].second - 1][g.e[i].first - 1] = 1;
		}

		for (int k = 0; k < g.n; k++)
			for (int i = 0; i < g.n; i++)
				for (int j = 0; j < g.n; j++)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

		for (int v = 0; v < g.n; v++)
		{
			ncol[v] = sorted_vector(d[v]);
			ncol[v].push_back(col[v]);
		}
	}
};

void refine(colored_graph &a, colored_graph &b)
{
	vector<int> lastA, lastB;
	map<vector<int>, int> m;
	a.relabel(m);
	b.relabel(m);
	m.clear();
	while (a.col != lastA || b.col != lastB)
	{
		lastA = a.col;
		lastB = b.col;

		a.push_neighbor();
		b.push_neighbor();

		a.relabel(m);
		b.relabel(m);
		m.clear();
	}
}

bool task1(graph a, graph b)
{
	return a.n == b.n && a.e.size() == b.e.size();
}
bool task2(graph a, graph b)
{
	if (!result[1])
		return false;
	if (a.n <= 10)
	{
		b = sorted_graph(b);

		vector<int> lab;
		for (int v = 1; v <= a.n; v++)
			lab.push_back(v);
		do
		{
			graph g = a;
			for (int i = 0; i < (int)g.e.size(); i++)
			{
				g.e[i].first = lab[g.e[i].first - 1];
				g.e[i].second = lab[g.e[i].second - 1];
			}
			if (graph_equal(sorted_graph(g), b))
				return true;
		}
		while (std::next_permutation(lab.begin(), lab.end()));

		return false;
	}
	return true;
}
bool task3(graph a, graph b)
{
	colored_graph ga, gb;
	ga.g = a;
	gb.g = b;

	ga.init_color();
	gb.init_color();
	refine(ga, gb);

	return sorted_vector(ga.col) == sorted_vector(gb.col);
}
bool task4(graph a, graph b)
{
	colored_graph ga, gb;
	ga.g = a;
	gb.g = b;

	ga.init_color();
	gb.init_color();

	ga.push_distance();
	gb.push_distance();

	refine(ga, gb);

	return sorted_vector(ga.col) == sorted_vector(gb.col);
}
bool task5(graph a, graph b)
{
	for (int u = 0; u < a.n; u++)
	{
		colored_graph ga, gb;
		ga.g = a;
		gb.g = b;

		ga.init_color();
		gb.init_color();

		ga.ncol[0][0] = ga.col[0] = 1;
		gb.ncol[u][0] = ga.col[u] = 1;

		refine(ga, gb);

		if (sorted_vector(ga.col) == sorted_vector(gb.col))
			return true;
	}
	return false;
}
bool task6(graph a, graph b)
{
	if (!result[1])
		return false;
	return hash_graph(a) == hash_graph(b);
}

void propose(graph a, graph b)
{
	if (proposed)
		quit_msg("Duplicate proposals");
	proposed = true;

	if (!validate_graph(a))
		quit_msg("Invalid graph A");
	if (!validate_graph(b))
		quit_msg("Invalid graph B");

	for (int times = 0; times < 50; times++)
	{
		int w = rand() % 2;
		if (w == 0)
		{
			if (identify(shuffled_graph(a)) != 1)
				quit_msg("Failed to prove");
		}
		else
		{
			if (identify(shuffled_graph(b)) != 2)
				quit_msg("Failed to prove");
		}
	}

	graph_a = a;
	graph_b = b;

	result[1] = task1(a, b);
	result[2] = task2(a, b);
	result[3] = task3(a, b);
	result[4] = task4(a, b);
	result[5] = task5(a, b);
	result[6] = task6(a, b);
}

int main()
{
	srand(233);

	hack();

	if (!proposed)
		quit_msg("Nothing has been proposed");

	print_graph(graph_a);
	print_graph(graph_b);

	for (int i = 1; i <= 6; i++)
		cout << "task #" << i << ": " << (result[i] ? "ok" : "failed") << endl;

	return 0;
}
