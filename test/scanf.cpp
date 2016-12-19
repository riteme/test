#include <cstdio>

int main() {
    int answer=0;
    int num;
    while(scanf("%d",&num)!=EOF){
	answer+=num;
    }
    printf("%d\n",answer);
}
