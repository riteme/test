#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

namespace input
{
	const int BufferSize = 1 << 16 | 1;

	char buffer[BufferSize];
	char *head = buffer + BufferSize;
	const char *tail = head;

	inline char nextChar()
	{
		if (head == tail)
		{
			fread(buffer, 1, BufferSize, stdin);
			head = buffer;
		}
		return *head++;
	}

	inline int getint()
	{
		static char c;
		while ((c = nextChar()) < '0' || c > '9');

		int res = c - '0';
		while ((c = nextChar()) >= '0' && c <= '9')
			res = res * 10 + c - '0';
		return res;
	}
}
using input::nextChar;
using input::getint;

namespace output
{
	const int BufferSize = 3000005;

	char buffer[BufferSize];
	char *out_tail = buffer;

	char s[11], *t;
	inline void putint(int x)
	{
		if (!~x)
			*out_tail++ = '-', *out_tail++ = '1';
		else if (!x)
			*out_tail++ = '0';
		else
		{
			t = s;
			while (x > 0)
				*t++ = x % 10 + '0', x /= 10;
			while (t-- != s)
				*out_tail++ = *t;
		}
		*out_tail++ = '\n';
	}

	inline void putall()
	{
		fwrite(buffer, 1, out_tail - buffer, stdout);
	}
}

const int MaxN = 100005;
const int MaxM = 300005;
const int MaxNV = MaxN + MaxM;
const int INF = 0x3f3f3f3f;

int n, m;

int ufs[MaxN];

int ufs_find(const int &v)
{
	return ufs[v] ? ufs[v] = ufs_find(ufs[v]) : v;
}

struct edge
{
	int u, v, t, l;
};
edge allE[MaxM];

struct lct_node
{
	lct_node *lc, *rc, *fa;
	bool hasR;

	int idxE, minE;
	int totL;

	inline bool is_root() const
	{
		return !fa || (fa->lc != this && fa->rc != this);
	}

	inline void tag_rev()
	{
		hasR = !hasR;
		swap(lc, rc);
	}
	inline void tag_down()
	{
		if (hasR)
		{
			if (lc)
				lc->tag_rev();
			if (rc)
				rc->tag_rev();
			hasR = false;
		}
	}

	inline void update()
	{
		minE = idxE;
		totL = allE[idxE].l;
		if (lc)
		{
			totL += lc->totL;
			if (allE[lc->minE].t < allE[minE].t)
				minE = lc->minE;
		}
		if (rc)
		{
			totL += rc->totL;
			if (allE[rc->minE].t < allE[minE].t)
				minE = rc->minE;
		}
	}

	inline void rotate()
	{
		fa->tag_down(), tag_down();
		lct_node *x = this, *y = fa, *z = y->fa;
		lct_node *b = x == y->lc ? x->rc : x->lc;

		x->fa = z, y->fa = x;
		if (b)
			b->fa = y;

		if (z)
		{
			if (z->lc == y)
				z->lc = x;
			else if (z->rc == y)
				z->rc = x;
		}
		if (x == y->lc)
			x->rc = y, y->lc = b;
		else
			x->lc = y, y->rc = b;

		y->update();
	}

	inline void splay()
	{
		tag_down();
		while (!is_root())
		{
			if (!fa->is_root())
			{
				if ((fa->lc == this) == (fa->fa->lc == fa))
					fa->rotate();
				else
					rotate();
			}
			rotate();
		}
		update();
	}

	inline void cut()
	{
		splay();
		rc = NULL, update();
	}

	inline void access()
	{
		for (lct_node *p = this, *q = NULL; p; q = p, p = p->fa)
		{
			p->splay(), p->rc = q;
			p->update();
		}
	}

	inline void make_root()
	{
		access(), splay(), tag_rev();
	}
};
lct_node lct[MaxNV];

inline void lct_link(int idx)
{
	lct_node *x = lct + allE[idx].u;
	lct_node *y = lct + allE[idx].v;
	lct_node *p = lct + n + idx;
	p->idxE = idx, p->update();

	int fx = ufs_find(allE[idx].u);
	int fy = ufs_find(allE[idx].v);
	if (fx != fy)
	{
		p->make_root(), p->fa = x;
		p->make_root(), p->fa = y;
		ufs[fx] = fy;
	}
	else
	{
		x->make_root();
		y->access(), y->splay();
		if (allE[y->minE].t >= allE[idx].t)
			return;

		lct_node *q = lct + n + y->minE;
		lct_node *u = lct + allE[y->minE].u;
		lct_node *v = lct + allE[y->minE].v;
		u->cut(), v->cut(), q->cut();
		if (q->fa == v)
			q->fa = u->fa = NULL;
		else
			q->fa = v->fa = NULL;

	//	p->make_root(), p->fa = x;
		x->splay(), x->fa = p;
		p->make_root(), p->fa = y;
	}
}
inline int lct_query(int u, int v)
{
	if (ufs_find(u) != ufs_find(v))
		return -1;

	lct_node *x = lct + u;
	lct_node *y = lct + v;
	x->make_root(), y->access(), y->splay();
	return y->totL;
}
inline void lct_modify(int id)
{
	lct_node *x = lct + n + id;
	while (x->update(), !x->is_root())
		x = x->fa;
}

int main()
{
	allE[0].u = allE[0].v = 0;
	allE[0].t = INF;
	allE[0].l = 0;

	n = getint(), m = getint();
	while (m--)
	{
		static char op;
		while ((op = nextChar()) != 'f' && op != 'm' && op != 'c');

		if (op == 'f')
		{
			int idx = getint() + 1;
			allE[idx].u = getint() + 1;
			allE[idx].v = getint() + 1;
			allE[idx].t = getint(), allE[idx].l = getint();
			lct_link(idx);
		}
		else if (op == 'm')
		{
			int u = getint() + 1, v = getint() + 1;
			output::putint(lct_query(u, v));
		}
		else if (op == 'c')
		{
			int idx = getint() + 1;
			allE[idx].l = getint();
			lct_modify(idx);
		}
	}

	output::putall();
	return 0;
}
