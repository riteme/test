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
    auto io=StreamRedirect("decimal.in","decimal.out");

	int a,b,c;
	while (cin>>a>>b>>c) {
		cout<<a/b<<'.';
		for (int i=1;
		     i<=c;
		     i++) {
		    float tmp=a/static_cast<float>(b);
			int digit=static_cast<int>(tmp*10.0f)%10;
			a=(a*10)%b;

			if(i!=c){
				cout<<digit;
			}else{
				int next_digit=static_cast<int>(tmp*10.0f)%10;
				cout<<digit+(next_digit>=5?1:0);
			}
		}  // for
		cout<<endl;
	} // while

    return 0;
}  // function main
