#include<iostream>
#include<cstring>
#include<cstdio>
#include<stack>
#include<vector>
using namespace std;
#define MAX 40000
#define Max 
#define mod
#define Fin(x) freopen(x,"r",stdin);
#define Fout(x) freopen(x,"w",stdout);
int read(){
	int x=0;
	int f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9'){
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
struct VALUE{
	double value_double;
	char value_char;
	bool value_is_char;
	bool value_is_double;
	VALUE(double value){
		value_double=value;
		value_is_double=true;
		value_is_char=false;	
	}
	VALUE(char value){
		value_char=value;
		value_is_double=false;	
		value_is_char=true;
	}
};
char c[MAX];
double p[100];
int n;
double dfs(int l,int r){
	stack<int> Stack;
	vector<VALUE> val;
	for (int i=l;i<=r;i++){
		if (c[i]=='(') { Stack.push(i); continue;}
		if (c[i]==')') { 
			if (Stack.size()==1)
				val.push_back(VALUE(dfs(Stack.top()+1,i-1))); 
			Stack.pop();
			continue;
		}
		if (Stack.empty())
			val.push_back(VALUE(c[i]));
	}
	double value=1.0; 
	vector<double> doublebox;
	for (size_t i=0;i<val.size();i++){
		if (val[i].value_is_char){
			if (val[i].value_char==',') {
				doublebox.push_back(value);
				value=1;
			}else {
				value*=p[val[i].value_char-'A'+1];
			}
		}else value*=val[i].value_double;		
		if (i==val.size()-1)
			doublebox.push_back(value);
	}
	if (doublebox.size()==1) return doublebox[0];
	double ans=1.0;
	for (size_t i=0;i<doublebox.size();i++){
		ans*=(1.0-doublebox[i]);
	}
	return 1.0-ans;
}
void Initalize(){
	cin>>n;
	scanf("%s",c);
	for (int i=1;i<=n;i++)
		cin>>p[i];
}
int main(){
	Fin("resistance.in");
	Fout("resistance.out");
	Initalize();
	printf("%.4lf\n",dfs(0,strlen(c)-1));
}
