#include<iostream>
#include<cstring>
#include <cctype>
#include<cstdio>
#include<vector>
using namespace std;

#define BUFFERSIZE 65536
size_t _pos = BUFFERSIZE, _sz = BUFFERSIZE;
char _buf[BUFFERSIZE+10];

char _getc() {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        _sz = fread(_buf, 1, BUFFERSIZE, stdin);
    }
    return _pos < _sz ? _buf[_pos++] : 0;
}

void readi(int &x) {
    char c;
    x = 0;
    do {
        c = _getc();
    } while (!isdigit(c));
    do {
        x = x * 10 + c - '0';
        c = _getc();
    } while (isdigit(c));
}

int num[503],rol[503],a[503][1004];
bool vis[503];
inline int read(){
    int X=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){X=X*10+ch-'0';ch=getchar();}
    return X*w;
}
int main()
{
	int T=0;
	while(1){
		T++;
		int n;
		// n=read();
        readi(n);
		int fir=0;
		if(n==0)break;
		for(int i=1;i<=n;i++){
			int tot=0;
			memset(vis,0,(n+2));
			for(int j=1;j<=n;j++){
				// a[i][2*j-1]=read();
                readi(a[i][2*j-1]);
				// a[i][2*j]=read();
				readi(a[i][2*j]);
				if(!vis[a[i][2*j-1]]){
					vis[a[i][2*j-1]]=true;
					tot++;
				}
			}
			rol[i]=tot;
			if(tot==1){
				if(a[i][1]==a[i][2]&&a[i][2]==a[i][3]){
					rol[i]=0;
					num[0]=a[i][1];
				}
			}
			if(rol[i]==1)fir=i;
		}
		for(int i=1;i<=n;i++){
			int temp=rol[i];
			num[temp]=a[fir][2*i];
		}
		printf("Case #%d:",T);
		for(int i=1;i<=n;i++){
			printf(" %d",num[i-1]);
		}
		printf("\n");
	}
}