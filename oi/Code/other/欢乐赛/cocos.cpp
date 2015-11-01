#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ntype;

#define TYPE_SUM 0
#define TYPE_MAX 1

struct Node{
	Node *left;
	Node *right;
	int type;
//	ntype cocos;
};

static int l=1;
static int r;

ntype DFS(ntype *d,Node *t){	
	if(r<l) return 0;
//	
	ntype lv,rv;
	
	if(t->type==TYPE_SUM){
		if(t->left==NULL){
			lv=d[r--];
		}else{
			lv=DFS(d,t->left);
		}
		
		if(t->right==NULL){
			rv=d[r--];
		}else{
			rv=DFS(d,t->right);
		}
		
//		printf("%d + %d = %d\n",lv,rv,lv+rv);
		return lv+rv;
	}else{
		if(t->left==NULL){
			lv=d[l++];
		}else{
			lv=DFS(d,t->left);
		}
		
		if(t->right==NULL){
			rv=d[l++];
		}else{
			rv=DFS(d,t->right);
		}
		
//		printf("max{%d, %d} = %d\n",lv,rv,std::max(lv,rv));
		return std::max(lv,rv);
	}
}

	int *father;
	int *type;
	ntype *cocos; 
	Node *tree;

int main(){
	freopen("cocos.in","r",stdin);
	freopen("cocos.out","w",stdout);
	
	int n;
	scanf("%d",&n);
	r=n;
	
//	int father[n-2+1];
//	int type[n-1+1];
//	ntype cocos[n+1];
//	Node tree[n-1+1];
	father=new int[n-2+1];
	type=new int[n-1+1];
	cocos=new ntype[n+1];
	tree=new Node[n-1+1];
	
	for(int i=1;i<=n-2;i++){
		scanf("%d",&father[i]);
	}
	for(int i=1;i<=n-1;i++){
		scanf("%d",&type[i]);
		
		Node tmp;
		tmp.left=NULL;
		tmp.right=NULL;
//		tmp.cocos=0;
		tmp.type=type[i];
		
		tree[i]=tmp;
	}
	for(int i=1;i<=n;i++){
		scanf("%lld",&cocos[i]);
	}
	
	std::sort(cocos+1,cocos+n+1);
	
//		for(int i=1;i<=n-2;i++){
//		printf("%d ",father[i]);
//	}
//	printf("\n");
//	for(int i=1;i<=n-1;i++){
//		printf("%d ",type[i]);
//	}
//	printf("\n");
//	for(int i=1;i<=n;i++){
//		printf("%lld ",cocos[i]);
//	}
//	printf("\n");
	
	for(int i=1;i<=n-2;i++){
		Node *fa=&tree[father[i]];
		
		if(fa->left==NULL){
			fa->left=&tree[i+1];
		}else{
			fa->right=&tree[i+1];
		}
	}
	
	printf("%lld",DFS(cocos,&tree[1]));
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
