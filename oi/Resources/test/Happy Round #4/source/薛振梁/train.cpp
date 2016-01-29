#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#define NMAX 100000
#define MMAX 300000
#define INFTY 2000000000000.0

struct Edge {
    int u;
    int v;
    double w;

    int another(int x){
    	return x==u?v:u;
    }
};  // struct Edge

static int n;
static int m;
static Edge edges[MMAX+10];
static vector<Edge *> G[NMAX+10];
static bool marked[NMAX+10];
static int set[NMAX+10];
double result;

template <typename T>
inline T abs(const T &a){
	return a>0?a:-a;
}

inline void make_set(){
	for(int i=1;i<=n;i++){
		set[i]=i;
	}
}

inline int find_set(int x){
	return x==set[x]?x:set[x]=find_set(set[x]);
}

inline void union_set(int x,int y){
	set[find_set(x)]=find_set(y);
}

inline double length(double origin, int cnt){
	for(int i=0;i<cnt;i++){
		origin=abs(1/(1-origin));
	}

	return origin;
}

void initialize(){
	scanf("%d%d",&n,&m);

	make_set();
	for(int i=0;i<m;i++){
		int u,v;
		double a;
		scanf("%d%d%lf",&u,&v,&a);

		union_set(u,v);
		edges[i].u=u;
		edges[i].v=v;
		edges[i].w=a;
		G[u].push_back(&edges[i]);
		G[v].push_back(&edges[i]);
	}
}

void dfs(int x,double dist,int cnt){
	if(x==n){
		result=min(result,dist);
		return;
	}

	if(cnt==n-1){
		return;
	}

	marked[x]=true;
	for(int i=0;i<G[x].size();i++){
		Edge *e=G[x][i];
		int v=e->another(x);

		if (!marked[v]) {
		    double newdist=dist+length(e->w,cnt);

		    if (newdist<result) {   
			    dfs(v,newdist,cnt+1);
		    }
		}
	}
	marked[x]=false;
}

int main() {
	freopen("train.in","r",stdin);
	freopen("train.out","w",stdout);
    initialize();

    if(find_set(1)!=find_set(n)){
    	printf("-1");
    	return 0;
    }

    result=INFTY;
    dfs(1,0.0,0);
    printf("%.3lf",result);

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
