#include "isomorphism.h"
using namespace std;

void hack()
{
	graph a, b;
	a.n = 2;
	a.e.push_back(make_pair(1, 2));

	b.n = 3;
	b.e.push_back(make_pair(1, 3));
	b.e.push_back(make_pair(1, 2));

	propose(a, b);
}

int identify(graph g)
{
	return g.n == 2 ? 1 : 2;
}
