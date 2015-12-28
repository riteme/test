// NOIP2010 关押罪犯

#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 20000
#define MMAX 100000

typedef int ntype;

struct Edge{
    Edge():u(0),v(0),w(0) {}

    ntype u;
    ntype v;
    ntype w;

    ntype another(const ntype x){
	return x==u?v:u;
    }
};

static ntype n,m;
static vector<Edge *> G[NMAX+10];
static vector<Edge *> MST[NMAX+10];
static Edge E[MMAX+10]; 
static Edge *pE[MMAX+10];
static ntype data[NMAX+10];
static ntype rank[NMAX+10];
static bool marked[NMAX+10]; 
static bool MARKED=true,UNMARKED=false;

inline ntype read(){
    ntype x=0;
    char c=getchar();
    while(c<'0' or c>'9')c=getchar();
    while('0'<=c and c<='9') x=x*10+(c-'0'),c=getchar();

    return x;
}

void initiailize();
void quit();
void compute_mst();
ntype bfs(const ntype root);

inline bool compare(const Edge *a,const Edge *b){
    return a->w<b->w;
}

inline void make_set(const ntype n){
    memset(rank,0,sizeof(ntype)*(n+10));
    for(int i=1;i<=n;i++){
	data[i]=i;
    }
}

inline ntype find_set(const ntype x){
    if(x!=data[x]) data[x]=find_set(data[x]);

    return data[x];
}

inline ntype union_set(const ntype x,const ntype y){
    if(rank[x]==rank[y]){
	data[x]=y;
	rank[y]++;
    }else if(rank[x]<rank[y])
	data[x]=y;
    else
	data[y]=x;
}

int main() {
    initiailize();

    // TODO

    quit();
    return 0;
}  // function main

ntype bfs(const ntype root){
    ntype result=INT_MAX;
    queue<ntype> q;
    q.push(root);
    
    while(!q.empty()){
	ntype u=q.front();

	for(ntype i=0;i<G[u].size();i++){
	    ntype v=e->another(u);

	    if(marked[v]==UNMARKED){
		marked[v]=MARKED;

		q.push(v);
		if(e->w<result){
		    result=e->w;
		}
	    }
	}
    }

    return result;
}

void compute_mst(){
    make_set(n);

    ntype ecnt=1;
    ntype mstcnt=0;
    while(ecnt<=m and mstcnt<n-1){
	Edge *e=pE[ecnt++];

	if(find_set(e->u)!=find_set(e->v)){
	    union_set(e->u,e->v);
	    MST[e->u].push_back(e);
	    MST[e->v].push_back(e);
	}
    }
}

void initialize(){
    n=read();
    m=read();

    for(int cnt=1;cnt<=m;cnt++){
	ntype a=read(),b=read(),c=read();

	E[cnt].u=a;
	E[cnt].v=b;
	E[cnt].w=c;
	pE[cnt]=&E[cnt];
	G[a].push_back(&E[cnt]);
	G[b].push_back(&E[cnt]);
    }

    sort(&pE[1],&pE[m+1],compare);

    compute_mst();
}

void quit();
