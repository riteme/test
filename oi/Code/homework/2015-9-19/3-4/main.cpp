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

void PrintPath(char from,char to){
	cout<<"Move "<<from<<" to "<<to<<"."<<endl;
}

void Move(int n,char a,char b,char c){
	if (n>0)
	{
		Move(n-1,a,c,b);
		PrintPath(a,c);
		Move(n-1,b,a,c);
	}
}

int main(int argc, char **argv) {
	auto io=StreamRedirect("hanoi.in","hanoi.out");

	int n;
	while (cin>>n) {
		Move(n,'a','b','c');
	} // while

	return 0;
}  // function main
