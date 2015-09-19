#include <iostream>

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

int max(int upbounds){
	int sum=0;
	int i=2;
	for (;
	     sum+i*i<upbounds;
	     i+=2) {
	    sum+=i*i;
	}  // for
	return i-2;
}

int main(int argc, char const *argv[])
{
	auto io=StreamRedirect("","max.out");
	cout<<max(1500)<<endl;
	return 0;
}