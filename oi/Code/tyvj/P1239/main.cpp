#include <iostream>
#include <list>
#include <set>

using namespace std;

struct vec4{
	int x;
	int y;
	int z;
	int w;
};

int main(){
	int n;
	
	cin>>n;
	
	list<vec4> solutions;
	
	for(int i=1;
	i<=n;
	i++){
		vec4 v;
		cin>>v.x>>v.y>>v.z>>v.w;
		solutions.push_back(v);
	}
	
	set<int> uniqueNum;
	int max=-1;
	
	for(auto first=solutions.begin();
	first!=solutions.end();
	first++){
		auto second=first;
		while(++second!=solutions.end()){
			auto third=second;
			while(++third!=solutions.end()){
				uniqueNum.clear();
				uniqueNum.insert({first->x,first->y,first->z});
				uniqueNum.insert({second->x,second->y,second->z});
				uniqueNum.insert({third->x,third->y,third->z});
				if(uniqueNum.size()<9){
					continue;
				}
				
				int score=first->w+second->w+third->w;
				if(score>max){
					max=score;
				}
			}
		}
	}
	
	if(max<0){
		cout<<"Impossible"<<endl;
	}else{
		cout<<max<<endl;
	}
	
	return 0;
}
