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

int Convert(int n,int m,int result=0){
	if (n%m==0&&n>0) {
	    return result;
	}
	result=result*10+n%m;
	return Convert(n-m*10,m,result);
}

int main(int argc, char **argv) {
    // auto io=StreamRedirect("transformation.in","transformation.out");

    int n,m;
    while (cin>>n>>m) {
    	cout<<Convert(n,m)<<endl;
    } // while

    return 0;
}  // function main
