#include <iostream>
#include <cmath>

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
	auto io=StreamRedirect("","daffodil.out");

	for (int num=100;
	     num<=999;
	     num++) {
	    int a=num/100;
		int b=(num%100)/10;
		int c=num%10;

		if(num==pow(a,3)+pow(b,3)+pow(c,3)) cout<<num<<' ';
	}  // for

	return 0;
}