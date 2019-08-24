#include <bits/stdc++.h>
#define down 0.996//徐徐降温 

using namespace std;

int n;
struct node{
int x;
int y;
int w;
}object[2005];//存下物体的坐标 
double ansx,ansy,answ;//最终答案 
double energy(double x,double y)//根据物理学知识,能量总和越小越稳定 
{
   double r=0,dx,dy;
   for (int a=1;a<=n;a++)
   {
      dx=x-object[a].x;
      dy=y-object[a].y;
      r+=sqrt(dx*dx+dy*dy)*object[a].w;
   }
      return r;
}
void sa()//模拟退火 
{
   double t=3000;//温度要足够高 
   while (t>1e-15)//略大于0 
   {
      double ex=ansx+(rand()*2-RAND_MAX)*t;//随机产生新的答案 
      double ey=ansy+(rand()*2-RAND_MAX)*t;
      double ew=energy(ex,ey);
      double de=ew-answ;
      if (de<0)//如果此答案更优，就接受 
      {
         ansx=ex;
         ansy=ey;
         answ=ew;
      }
      else if(exp(-de/t)*RAND_MAX>rand())//否则根据多项式概率接受 
      {
         ansx=ex;
         ansy=ey;
      }
      t*=down;
   }
}
void solve()//多跑几遍退火,增加得到最优解的概率 
{
   sa();
   sa();
   sa();
   sa();
}
int main() {
cin>>n;
for (int a=1;a<=n;a++)
{
   scanf("%d%d%d",&object[a].x,&object[a].y,&object[a].w);
   ansx+=object[a].x;
   ansy+=object[a].y;
}
ansx/=n;//以平均数作为初始答案 
ansy/=n;
answ=energy(ansx,ansy);
solve();
printf("%.3lf %.3lf\n",ansx,ansy);//华丽的输出 
    return 0;
}
