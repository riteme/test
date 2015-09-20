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

int main(int argc, char **argv) {
	auto io=StreamRedirect("hanoi.in","hanoi.out");

	int n;
	while (cin>>n) {
		// ...
	} // while

	return 0;
}  // function main
