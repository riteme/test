#ifndef _ISOMORPHISM_H
#define _ISOMORPHISM_H

#include <vector>
#include <utility>

struct graph
{
	int n;
	std::vector< std::pair<int, int> > e;
};

void hack();
void propose(graph a, graph b);
int identify(graph g);

#endif
