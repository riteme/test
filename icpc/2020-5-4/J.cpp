#include<bits/stdc++.h>

using namespace std;

#define rep(i,j,n) for(int i=j;i<=n;i++)

const double eps = 1e-4;
const double PI = acos(-1.0);
int sgn(double x)
{
    if(fabs(x) < eps)return 0;
    if(x < 0)return -1;
    else return 1;
}
struct point
{
    double x,y;
    point() {}
    point(double _x,double _y)
    {
        x = _x;
        y = _y;
    }
    point operator -(const point &b)const
    {
        return point(x - b.x,y - b.y);
    }
//Іж»э
    double operator ^(const point &b)const
    {
        return x*b.y - y*b.x;
    }
//µг»э
    double operator *(const point &b)const
    {
        return x*b.x + y*b.y;
    }
//ИЖФ­µгРэЧЄЅЗ¶ИBЈЁ»Ў¶ИЦµЈ©Ј¬єуx,yµД±д»Ї
    void transXY(double B)
    {
        double tx = x,ty = y;
        x = tx*cos(B) - ty*sin(B);
        y = tx*sin(B) + ty*cos(B);
    }
    void input()
    {
        scanf("%lf%lf",&x,&y);
    }
};

struct Line
{
    point s,e;
    Line() {}
    Line(point _s,point _e)
    {
        s = _s;
        e = _e;
    }
    pair<int,point> operator &(const Line &b)const
    {
        point res = s;
        if(sgn((s-e)^(b.s-b.e)) == 0)
        {
            if(sgn((s-b.e)^(b.s-b.e)) == 0)
                return make_pair(0,res);
            else return make_pair(1,res);
        }
        double t = ((s-b.s)^(b.s-b.e))/((s-e)^(b.s-b.e));
        res.x += (e.x-s.x)*t;
        res.y += (e.y-s.y)*t;
        return make_pair(2,res);
    }
};
double x,y,a;
double W,H,E;
double tempa,tempb,tempc,tempd;
int main()
{
    cin>>W>>H>>E;
    double mx,mi;

    mx=-1000,mi=1000;
    rep(i,1,7)
    rep(j,1,7)
    {
        printf("? %.8f %.8f\n",-W+eps*i,-H+eps*j);
        fflush(stdout);
        cin>>a;
        if(a<-135) a+=360;
        mx=max(mx,a);
        mi=min(mi,a);
    }
    tempa=(mx+mi)/2;

    mx=-1000,mi=1000;
    rep(i,1,7)
    rep(j,1,7)
    {
        printf("? %.8f %.8f\n",W-eps*i,-H+eps*j);
        fflush(stdout);
        cin>>a;
        if(a<-45) a+=360;
        mx=max(mx,a);
        mi=min(mi,a);
    }
    tempb=(mx+mi)/2;

    mx=-1000,mi=1000;
    rep(i,1,7)
    rep(j,1,7)
    {
        printf("? %.8f %.8f\n",-W+eps*i,H-eps*j);
        fflush(stdout);
        cin>>a;
        if(a>135) a-=360;
        mx=max(mx,a);
        mi=min(mi,a);
    }
    tempc=(mx+mi)/2;

    mx=-1000,mi=1000;
    rep(i,1,7)
    rep(j,1,7)
    {
        printf("? %.8f %.8f\n",W-eps*i,H-eps*j);
        fflush(stdout);
        cin>>a;
        if(a>45) a-=360;
        mx=max(mx,a);
        mi=min(mi,a);
    }
    tempd=(mx+mi)/2;

    point s1=point(-W,-H);
    point e1=point(-W+cos(tempa/180*PI), -H+sin(tempa/180*PI));
    point s2=point(W,-H);
    point e2=point(W+cos(tempb/180*PI), -H+sin(tempb/180*PI));
    point s3=point(W,H);
    point e3=point(W+cos(tempd/180*PI), H+sin(tempd/180*PI));
    point s4=point(-W,H);
    point e4=point(-W+cos(tempc/180*PI), H+sin(tempc/180*PI));

    pair<int,point> p1= Line(s1,e1) & Line(s2,e2);
    pair<int,point> p2= Line(s3,e3) & Line(s2,e2);
    pair<int,point> p3= Line(s3,e3) & Line(s4,e4);
    pair<int,point> p4= Line(s1,e1) & Line(s4,e4);

    point ans=point(0,0);
    double temp=0;
    if(p1.first==2 && p1.second.y>-H)
    {
        double temp0=(p1.second.y+H)/H;
        ans.x+=p1.second.x*temp0;
        ans.y+=p1.second.y*temp0;
        temp+=temp0;
    }
    if(p2.first==2 && p2.second.x<W)
    {
        double temp0=(W-p2.second.x)/W;
        ans.x+=p2.second.x*temp0;
        ans.y+=p2.second.y*temp0;
        temp+=temp0;
    }
    if(p3.first==2 && p3.second.y<H)
    {
        double temp0=(-p3.second.y+H)/H;
        ans.x+=p3.second.x*temp0;
        ans.y+=p3.second.y*temp0;
        temp+=temp0;
    }
    if(p4.first==2 && p4.second.x>-W)
    {
        double temp0=(p4.second.x+W)/W;
        ans.x+=p4.second.x*temp0;
        ans.y+=p4.second.y*temp0;
        temp+=temp0;
    }

    ans.x/=temp;
    ans.y/=temp;

    if(ans.x<-W) ans.x=-W;
    if(ans.x>W) ans.x=W;

    if(ans.y<-H) ans.y=-H;
    if(ans.y>H) ans.y=H;
    printf("! %.8f %.8f\n",ans.x,ans.y);
    /*cin>>x>>y;
    point s1 = point(x,y);
    cin>>a;
    //cout<<sin(a/180*PI)<<' '<<cos(a/180*PI)<<endl;
    point e1 = point(x+cos(a/180*PI),y+sin(a/180*PI));
    cin>>x>>y;
    point s2 = point(x,y);
    cin>>a;
    //cout<<sin(a/180*PI)<<' '<<cos(a/180*PI)<<endl;
    point e2 = point(x+cos(a/180*PI),y+sin(a/180*PI));
    pair<int,point> pp= Line(s1,e1) & Line(s2,e2);

    cout<<pp.second.x<<' '<<pp.second.y<<endl;*/
}
