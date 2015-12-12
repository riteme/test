// 借教室

#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

#define NMAX 1000000
#define MMAX 1000000

typedef long long ntype;

struct Reservation {
    Reservation() : start(0), end(0), need(0) {}
    Reservation(ntype s, ntype t, ntype d) : start(s), end(t), need(d) {}

    ntype start;
    ntype end;
    ntype need;
};  // struct Reservation

struct Node{
	Node():l(0),r(0),left(NULL),right(NULL),sum(0){}
	Node(ntype _l,ntype _r):l(_l),r(_r),left(NULL),right(NULL),sum(0){{

	ntype l;
	ntype r;
	Node *left;
	Node *right;
	ntype sum;
};

static ntype n, m;
static ntype r[NMAX + 10];
static Reservation q[MMAX + 10];

Node *build_tree(ntype lb,ntype rb){
	Node *x=new Node(lb,rb);

	if(lb!=rb){
		ntype mid=(lb+rb)/2;
		x->left=build_tree(lb,mid);
		x->right=build_tree(mid+1,rb);
	}

	return x;
}

void insert(ntype s,ntype t,ntype value,Node *x){
	if(s==x->l and t==x->r)
		x->sum=value;

}

ntype query(ntype d,Node *x){

}

void initialize();
void quit();

int main() {
    ios::sync_with_stdio(false);
    initialize();

    quit();
    return 0;
}  // function main

void initialize() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) cin >> r[i];
    for (int i = 1; i <= m; i++) cin >> q[i].need >> q[i].start >> q[i].end;
}

void quit();
