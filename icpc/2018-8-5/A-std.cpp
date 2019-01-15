#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> PI;
typedef long long LL;
typedef double D;
#define FI first
#define SE second
#define MP make_pair
#define PB push_back
#define R(I,N) for(int I=0;I<N;I++)
#define F(I,A,B) for(int I=A;I<B;I++)
#define FD(I,N) for(int I=N-1;I>=0;I--)
#define make(A) scanf("%d",&A)
#define make2(A,B) scanf("%d%d",&A,&B)
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
#define db if(1)printf
template<typename C> void MA(C& a,C b){if(a<b)a=b;}
template<typename C> void MI(C& a,C b){if(a>b)a=b;}
#define MAXn 5001
#define MAXd 201
#define MOD 1000007
const int P = 1e9 +7;
int n,d,m;
int t[MAXn][MAXd];
unsigned hh[MAXn];
unsigned pp[MAXd];
vector<int> g[MAXd][MAXn];
vector<int> hm[MOD];
int f[MAXn],il[MAXn];
int wyn;
int find(int nr){
  return f[nr] == nr ? nr : f[nr] = find(f[nr]);
}
void uni(int a,int b){
  a = find(a);
  b = find(b);
  if(a == b)return;
  wyn += 2 * il[a] * il[b];
  f[a] = b;
  il[b] += il[a];
}
bool spr(int a,int b){
  R(i,d)if(t[a][i] != t[b][i])return 0;
  return 1;
}
void us(int nr){
  int akh = hh[nr]%MOD;
  R(i,SZ(hm[akh])){
    if(hm[akh][i] == nr){
      hm[akh][i] = hm[akh].back();
      hm[akh].pop_back();
      return;
    }
  }
}
void dodaj(int nr){
  int akh = hh[nr]%MOD;
  R(i,SZ(hm[akh])){
    int ak = hm[akh][i];
    if(spr(nr,ak)){
      uni(nr,ak);
      return;
    }
  }
  hm[akh].PB(nr);
}
int main(){
  make(d);make(n);make(m);
  pp[0] = 1;
  R(i,d)pp[i+1] = pp[i] * P;
  R(i,n){
    f[i] = i;
    il[i] = 1;
    R(j,d){
      t[i][j] = i;
      g[j][i].PB(i);
      hh[i] += i * pp[j];
    }
    hm[hh[i]%MOD].PB(i);
  }
  wyn = n;
  R(i,m){
    int k,a,b;
    make(a);make(b);make(k);
    a--;b--;k--;
    a = t[a][k];
    b = t[b][k];
    if(a==b){
      printf("%d\n",wyn);
      continue;
    }
    if(SZ(g[k][a]) > SZ(g[k][b])) swap(a,b);
    R(j,SZ(g[k][a])){
      int ak = g[k][a][j];
      us(ak);
      hh[ak] -= a * pp[k];
      t[ak][k] = b;
      hh[ak] += b * pp[k];
      dodaj(ak);
      g[k][b].PB(ak);
    }
    g[k][a].clear();
    printf("%d\n",wyn);
  }
}
