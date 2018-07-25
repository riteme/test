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

long long mut(long long n,long long result=1){
	if (n<=1) {
	    return result;
	}
	result*=n;
	return mut(n-1,result);
}

int main(int argc, char **argv) {
    auto io=StreamRedirect("combination.in","combination.out");

	long long m,n;
	while (cin>>m>>n) {
		if(m>n){
			cout<<"No answer"<<endl;
			continue;
		}
		long long mmut=mut(m),nmut=mut(n),mnmut=mut(n-m);
		if(mmut*mnmut==0){
			cout<<"No answer"<<endl;
			continue;
		}
		cout<<nmut/(mmut*mnmut)<<endl;
	} // while

    return 0;
}  // function main
