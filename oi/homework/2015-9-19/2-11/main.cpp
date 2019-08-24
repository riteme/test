#include <iostream>
#include <cmath>
#include <cassert>	

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

int GetFirst(int n,int result=0){
	if (n==1) {
	    return 2*result+1;
	}
	result+=n;
	GetFirst(n-1,result);
}

int main(int argc, char const *argv[])
{
	auto io=StreamRedirect("nicomacheus.in","nicomacheus.out");

	int num,sum;
	while (cin>>num) {
		int cnt=1;
		for (int i =GetFirst(num);
		     cnt<=num;
		     i+=2,cnt++) {
		    sum+=i;
			cout<<i<<(cnt!=num?'+':' ');
		}  // for
		cout<<"= "<<pow(num,3)<<endl;
	} // while
	// assert(num==sum);

	return 0;
}