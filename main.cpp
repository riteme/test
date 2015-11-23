#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
struct ms
{
	
	int father,data,left,right;
};
ms k[10000];
int n;
int ans;
int m;
int P,road;
int Ans_Road(int Point_1,int Point_2,int Road,bool map[])
{
	//cout<<Point_1<<" "<<Road<<endl;
	map[Point_1]=true;
	if (Point_1==Point_2)
 	{
 		P=true;
 		road=Road;
		return 0;
	 }
	  if (P==true) return 0;
      if (k[Point_1].father!=0 && map[k[Point_1].father]==false)
      {
     

    	int ans=Ans_Road(k[Point_1].father,Point_2,Road+1,map);
    	
      }
           if (P==true) return 0;
      if (k[Point_1].left!=0 && map[k[Point_1].left]==false)
      {
		int ans=Ans_Road(k[Point_1].left,Point_2,Road+1,map);
		
      }
  if (P==true) return 0;
      if (k[Point_1].right!=0 && map[k[Point_1].right]==false)
      {
     
       int ans=Ans_Road(k[Point_1].right,Point_2,Road+1,map);
       
      }
     if (P==true) return 0;
}
int Road(int Point_1,int Point_2)
{
	bool map[102];
	memset(map,false,sizeof(map));
    P=false;
    Ans_Road(Point_1,Point_2,0,map);
    return road;
}
int main()
{
	
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>k[i].data>>k[i].left>>k[i].right;
		k[k[i].left].father=i;
		k[k[i].right].father=i;
	//    cout<<k[i].left<<" "<<k[i].right<<endl;
	}
	int min=9999999;
	for (int i=1;i<=n;i++)
	{
	ans=0;
	for (int j=1;j<=n;j++)
	{
		
		if (i!=j)
		{
			int x=Road(i,j);
			ans=ans+k[j].data*x;
			//cout<<endl;
			//printf("\0");
			//cout<<"";
			
		}
			
	}

			cout<<"ans: "<<ans<<'\n';
	if (min>ans) min=ans;
    }
    printf("%d",min);
}
