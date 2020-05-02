#include <bits/stdc++.h>
#define rep(i, l, r) for (register int i = l; i <= r; i++)
#define maxn 200020
#define maxb 23
#define ui unsigned int
#define gc getchar
#define fi first
#define se second
#define pii pair<int, int>
using namespace std;

int n, hd, tot;
static map<string, pii> tab;
char s[99]; int cs = 0;

struct Node
{
	int l, r, bg, ed, type;
	Node() {}
	Node(int l, int r, int bg, int ed, int type) : l(l), r(r), bg(bg), ed(ed), type(type) {}
}h[maxn];

void _alloc(const string &x, int y){
        assert(x.length()==4);
    assert(100 <= y);
    assert(y <= 100000);

	int d = 0;
	for (int i = hd; i; i = h[i].r)
		if (h[i].type == 0 && h[i].ed - h[i].bg + 1 >= y)
		{
			d = i;
			if (h[i].ed >= h[i].bg + y)
			{
				h[++ tot] = Node(i, h[i].r, h[i].bg + y, h[i].ed, 0);
				if (h[i].r) h[h[i].r].l = tot;
				h[i].r = tot;
			}
			h[i].ed = h[i].bg + y - 1, h[i].type = 1;
			break ;
		}
	tab[x] = pii(d, y);
}
void _free(const string &x){
        assert(x.length()==4);

	if (!tab.count(x)) return;
	int d = tab[x].fi, y = tab[x].se;
	if (d){
		h[d].type = 0;
		if (h[d].l && h[h[d].l].type == 0)
		{
			if (h[h[d].l].l)
				h[h[h[d].l].l].r = d;
			h[d].bg = h[h[d].l].bg;
			h[d].l = h[h[d].l].l;
		}
		if (h[d].r && h[h[d].r].type == 0)
		{
			if (h[h[d].r].r)
				h[h[h[d].r].r].l = d;
			h[d].ed = h[h[d].r].ed;
			h[d].r = h[h[d].r].r;
		}
        assert(h[h[d].l].type==1);
        if (h[d].r)
            assert(h[h[d].r].type==1);
	}
	tab[x].fi = 0;
}

void _output(const string &x){
    assert(x.length()==4);
	if (!tab.count(x)) printf("%d\n", 0);
	/*else*/ printf("%d\n", h[tab[x].fi].bg);
}

int main(){
	scanf("%d", &n);
	h[++ tot] = Node(0, 2, 0, 0, 1);
	hd = tot;
	h[++ tot] = Node(1, 0, 1, 100000, 0);
	rep(i, 1, n)
	{
        assert(h[hd].type == 1);
		scanf("%s", s);
		if (s[4] == '=')
		{
			string str;
			str.push_back(s[0]);
			str.push_back(s[1]);
			str.push_back(s[2]);
			str.push_back(s[3]);
			int y = 0;
			for (int i = 4; s[i]; i ++)
				if ('0' <= s[i] && s[i] <= '9')
					y = y * 10 + s[i] - '0';
			_alloc(str, y);
		}
		else if (s[0] == 'o')
		{
			string str;
			str.push_back(s[7]);
			str.push_back(s[8]);
			str.push_back(s[9]);
			str.push_back(s[10]);
			_output(str);
		}
		else
		{
			string str;
			str.push_back(s[5]);
			str.push_back(s[6]);
			str.push_back(s[7]);
			str.push_back(s[8]);
			_free(str);
		}
	}
	return 0;
}