#include <bits/stdc++.h>
typedef long double LD;
using namespace std;
inline int rd() {
    char ch=getchar(); int i=0,f=1;
    while(!isdigit(ch)) {if(ch=='-')f=-1; ch=getchar();}
    while(isdigit(ch)) {i=(i<<1)+(i<<3)+ch-'0'; ch=getchar();}
    return i*f;
}
const int N=1e6+50;
const LD PI=acos(-1.0);
const LD PI2=acos(-1.0)*2;
const LD rang=PI/2;
const LD eps=1e-8;
inline int sgn(LD x) {return (x>eps)-(x<-eps);}
inline LD fix(LD x) {
    while(x<-PI) x+=PI2;
    while(x>PI) x-=PI2;
    return x;
}
int n,tot,cont[N];
struct P {
    LD x,y;
    P(LD x=0,LD y=0):x(x),y(y){}
    friend inline P operator +(const P &a,const P &b) {return P(a.x+b.x,a.y+b.y);}
    friend inline P operator -(const P &a,const P &b) {return P(a.x-b.x,a.y-b.y);}
    friend inline LD operator *(const P &a,const P &b) {return a.x*b.y-a.y*b.x;}
    inline LD dis() {return sqrt(x*x+y*y);}
    inline P rev(LD o) {
        LD sn=sin(o), cs=cos(o);
        return P(x*cs-y*sn,x*sn+y*cs);
    }
    inline P set(LD R) {
        LD len=dis();
        return P(x/len*R,y/len*R);
    }
}p[N];
struct C {
    P a; LD R;
    friend inline LD dis(const C &a,const C &b) {return (b.a-a.a).dis();}
    friend inline bool operator <(const C &a,const C &b) {
        if(sgn(a.a.x-b.a.x)) return sgn(a.a.x-b.a.x)<0;
        else if(sgn(a.a.y-b.a.y)) return sgn(a.a.y-b.a.y)<0;
        else return a.R<b.R;
    }
    friend inline bool operator ==(const C &a,const C &b) {
        return !sgn(a.a.x-b.a.x) && !sgn(a.a.y-b.a.y) && !sgn(a.R-b.R);
    }
}cir[N];
inline bool in(C a,C b) {
    if(a.R<b.R) return false;
    LD dist=dis(a,b);
    if(dist>a.R) return false;
    return sgn(dist-a.R+b.R)<=0;
}
inline void calc_tangent_line(C a,C b) {
    if(a.R>b.R) swap(a,b);
    if(in(a,b)) return;
}
inline void calc_tangle_point(C a,C b) {
    if(a.R<b.R) swap(a,b);
    LD dist=dis(a,b);
    LD ang=fix(asin((a.R-b.R)/dist));
    if(ang>rang) ang=PI-ang;
    LD ang2=rang-ang;
    P tar=a.a-b.a,t;
    t=tar.rev(-ang-rang);
    p[++tot]=b.a+t.set(b.R);
    t=tar.rev(ang+rang);
    p[++tot]=b.a+t.set(b.R);
    tar=b.a-a.a;
    t=tar.rev(ang2);
    p[++tot]=a.a+t.set(a.R);
    t=tar.rev(-ang2);
    p[++tot]=a.a+t.set(a.R);
}
inline bool cmp(const P &a,const P &b) {
    LD t=(a-p[1])*(b-p[1]);
    if(sgn(t)) return sgn(t)>0;
    return (a-p[1]).dis()<(b-p[1]).dis();
}
inline int build_convex() {
    int c=1,t;
    for(int i=1;i<=tot;i++) 
        if(i==1 || sgn(p[i].x-p[t].x)<0 || (!sgn(p[i].x-p[t].x) && sgn(p[i].y-p[t].y)<0)) t=i;
    if(t!=1) swap(p[1],p[t]);
    sort(p+2,p+tot+1,cmp);
    for(int i=2;i<=tot;i++) {
        while(c>=2 && sgn((p[i]-p[c-1])*(p[c]-p[c-1]))>=0 ) --c;
        p[++c]=p[i];
    } 
    return c;
}
inline int same_cir(const P &a,const P &b) {
    for(int i=1;i<=n;i++) 
        if(!sgn((a-cir[i].a).dis()-cir[i].R) && !sgn((b-cir[i].a).dis()-cir[i].R)) return i;
    return 0;
}
inline LD on_cir(const P &a,const P &b,const C &c) {
    LD l=(b-a).dis();
    LD R=c.R;
    if(l>R) l-=eps;
    LD ang=fix(acos((2*R*R-l*l)/(2*R*R)));
    if(ang<0) ang=-ang;
    if((a-c.a)*(b-c.a)<0) ang=PI2-ang;
    return ang*R;
}
int main() {
    n=rd();
    for(int i=1;i<=n;i++) 
        cir[i].a.x=rd(), cir[i].a.y=rd(), cir[i].R=rd()/*+10*/;
    sort(cir+1,cir+n+1);
    n=unique(cir+1,cir+n+1)-cir-1;
    for(int i=1;i<=n;i++) 
        for(int j=1;j<=n;j++) 
            if(i!=j && in(cir[i],cir[j])) cont[j]=1;
    int t=n; n=0;
    for(int i=1;i<=t;i++) 
        if(!cont[i]) cir[++n]=cir[i];
        else cont[i]=0;
    if(n==1) {printf("%.7f",(double)(PI*2*cir[1].R));}
    else {
        for(int i=1;i<=n;i++)
            for(int j=i+1;j<=n;j++)
                calc_tangle_point(cir[i],cir[j]);
        for(int i=1;i<=tot;i++)
            for(int j=1;j<=n;j++)
                if(sgn((p[i]-cir[j].a).dis()-cir[j].R)<0) cont[i]=1;
        t=tot; tot=0;
        for(int i=1;i<=t;i++)
            if(!cont[i]) p[++tot]=p[i];
        tot=build_convex();
        p[tot+1]=p[1];
        LD rs=0;
        for(int i=1;i<=tot;i++) {
            int t=same_cir(p[i],p[i+1]);
            if(t) rs+=on_cir(p[i],p[i+1],cir[t]);
            else rs+=(p[i]-p[i+1]).dis();
        }
        printf("%.9f",(double)rs);
    }
}
