#include <iostream>
#include <algorithm>

using namespace std;

typedef FILE* FilePtr;

class StreamRedirect
{
public:
	StreamRedirect(const std::string &in,const std::string &out){
		if (!in.empty()) {    
		freopen(in.data(),"r",stdin);
		}
		if (!out.empty()) {
		freopen(out.data(),"w",stdout);
		}
	}
	~StreamRedirect(){
		fclose(stdin);
		fclose(stdout);
	}
};

int main(int argc, char const *argv[])
{
	 auto io = StreamRedirect("three.in","three.out");

	int a,b,c;
	while (cin>>a>>b>>c) {
		int arr[]={a,b,c};
		sort(begin(arr),end(arr),greater_equal<int>());

		for (auto &e : arr) {
		    cout<<e<<' ';
		}  // foreach in arr
		cout<<endl;
	} // while
	

	return 0;
}
