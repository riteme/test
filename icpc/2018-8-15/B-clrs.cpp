#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<ctype.h>
#include<math.h>
#include<set>
#include<map>
#include<vector>
#include<queue>
#include<bitset>
#include<algorithm>
#include<time.h>
using namespace std;
#define MS(x, y) memset(x, y, sizeof(x))
#define ls o<<1
#define rs o<<1|1
typedef long long LL;
typedef unsigned long long UL;
typedef unsigned int UI;
template <class T1, class T2>inline void gmax(T1 &a, T2 b) { if (b > a)a = b; }
template <class T1, class T2>inline void gmin(T1 &a, T2 b) { if (b < a)a = b; }
const int N = 0, M = 0, Z = 1e9 + 7, inf = 0x3f3f3f3f;
template <class T1, class T2>inline void gadd(T1 &a, T2 b) { a = (a + b) % Z; }
int casenum, casei;
int n;
char rtn[100];
void fwd()
{
    puts("forward");
    fflush(stdout);
    scanf("%s", rtn);
}
void rgt()
{
    puts("right");
    fflush(stdout);
}
void lft()
{
    puts("left");
    fflush(stdout);
}
void dig()
{
    puts("dig");
    fflush(stdout);
    exit(0);
}
bool BEST()
{
    fwd();
    if(strcmp(rtn, "closer") == 0)
    {
        return 0;
    }
    lft(); lft(); fwd();
    fwd();
    if(strcmp(rtn, "closer") == 0)
    {
        return 0;
    }
    lft(); lft(); fwd();
    lft(); fwd();
    if(strcmp(rtn, "closer") == 0)
    {
        return 0;
    }
    lft(); lft(); fwd();
    fwd();
    if(strcmp(rtn, "closer") == 0)
    {
        return 0;
    }
    lft(); lft(); fwd();
    return 1;
}
bool onlycheckBEST()
{
    bool flag = 1;
    fwd();
    if(strcmp(rtn, "closer") == 0)
    {
        flag = 0;
    }
    lft(); lft(); fwd(); lft(); lft();
    if(!flag)return 0;
     
    lft(); fwd();
    if(strcmp(rtn, "closer") == 0)
    {
        flag = 0;
    }
    lft(); lft(); fwd(); lft();
    if(!flag)return 0;
     
    rgt(); fwd();
    if(strcmp(rtn, "closer") == 0)
    {
        flag = 0;
    }
    lft(); lft(); fwd(); rgt();
    if(!flag)return 0;
     
    lft(); lft(); fwd();
    if(strcmp(rtn, "closer") == 0)
    {
        flag = 0;
    }
    lft(); lft(); fwd();
    if(!flag)return 0;
    return 1;
}
int main()
{
    while(!BEST());
    int clo = 0;
    int far = 0;
    while(1)
    {
        fwd();
        if(strcmp(rtn, "closer") == 0)
        {
            ++clo;
        }
        else if(strcmp(rtn, "farther") == 0)
        {
            ++far;
        }
        if(onlycheckBEST())
        {
            if(clo >= far)
            {
                dig();
            }
            else clo = far = 0;
        }
    }
    return 0;
}
