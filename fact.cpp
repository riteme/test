#include <stdio.h>
#include <math.h>
 
int main()
{
    int i,b;
    long long int in;
/*采用64位整型，以便输入更大的数*/
    while(scanf("%lld",&in)!=EOF)
    {
        /*在F://1.txt中输入x个数N（N>=2）以换行符或空格符隔开，当没有输入时循环会自动结束*/
        b=0;/*用于标记是否是第一个质因数，第一个质因数在输出时前面不需要加空格*/
        for(i=2;in!=1;i++)
        {
            if(in%i==0)
            {
                in/=i;
                b?printf("%d",i):printf("%d",i),b=1;
                i--;
        /*i--和i++使得i的值不变，即能把N含有的所有的当前质因数除尽，例如：24会一直把2除尽再去除3*/
            }
        printf("\n");
        }
    }
    return 0;
 }

