#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long Int;

Int score=0;

void AddScore(Int points){
	score=(score+points)%1000;
}

#define loop(n,step) for(int __Loop__=1;__Loop__<=(n);__Loop__+=(step))


int main(int argc, char *argv[]) {
	ios::sync_with_stdio(false);

	Int n,p;
	vector<Int> d;

	cin>>n>>p;

	d.reserve(n);
	Int tmp;
	loop(n,1){
		cin>>tmp;
		d.push_back(tmp);
	}

	std::sort(d.begin(),d.end());

	Int last=-1;
	for(Int i=0;i<n;i++){
		AddScore(d[i]*(i+1));

		if (d[i]==last) {
		    AddScore(p);
		}

		last=d[i];
	}

	cout<<score;

	return 0;
}  // function main
