#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<iostream>
 /*
若只有正数或负数就是小乘大即可
如果是正数负数都有，对于正数与负数一起时要小乘小
所以单独比较两个区间正负个数情况，对于有负有正只需要对正数的那方，取两者的较小值反向排序即可

-6 -5 -4 -3  1  2
-3  1  2  3  5  6

排完后
-6 -5 -4 -3  1  2   //由于另一边只有一个负数,只对2一个数排，没变化
-3  1  6  5  3  2   //由于min(1的负数,2的正数)=4 对最后4位排即可

然后两边相乘就好啦~
*/
using namespace std;
long long N=(long long)1<<63;
inline long long max(long long a,long long b)
{
    return a>b?a:b;
}
inline int min(int a,int b)
{
    return a<b?a:b;
}
int cmp(const void *p,const void *q)
{
    return *(int *)p-*(int *)q;
}
int cmp2(const void *p,const void *q)
{
    return -(*(int *)p-*(int *)q);
}
int main()
{
    int n,i,j,k,t;
    long long sum;
    int a[100002],b[100002];
    int a1,a2,b1,b2;
    while(scanf("%d",&n)!=EOF)
    {
        sum=-N;a1=a2=b1=b2=0;
        for(i=0;i<n;i++) {scanf("%d",a+i);if(a[i]<0) a1++;if(a[i]>0) a2++;}
        for(i=0;i<n;i++) {scanf("%d",b+i);if(b[i]<0) b1++;if(b[i]>0) b2++;}
        qsort(a,n,sizeof(a[0]),cmp);
        qsort(b,n,sizeof(b[0]),cmp);
        if(min(a2,b1)>1)
        qsort(a+n-min(a2,b1),min(a2,b1),sizeof(a[0]),cmp2);
        if(min(b2,a1)>1)
        qsort(b+n-min(b2,a1),min(b2,a1),sizeof(b[0]),cmp2);
        for(i=0;i<n;i++)
        sum=max(sum,(long long)a[i]*(long long)b[n-i-1]);
        cout<<sum<<endl;
    }
    return 0;
}