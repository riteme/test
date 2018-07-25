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
		freopen(out.data(),"w+",stdout);
		}
	}
	~StreamRedirect(){
		fclose(stdin);
		fclose(stdout);
	}
};

int main(int argc, char const *argv[])
{
//	auto io=StreamRedirect("chicken.in","chicken.out");

	double n,m;
	while (cin>>n>>m) {
		if (n<0||m<0||
			n!=static_cast<int>(n)||m!=static_cast<int>(m)) {
		    cout<<"No answer"<<endl;
		    break;
		}

		int chicken,rabbit;
		chicken=rabbit=0;

		for (int i=9;
		     i<=n;
		     i++) {
		    if (2*i+4*(n-i)==m) {
		        chicken=i;
		        rabbit=n-i;
		        break;
		    }
		}  // for
		
		if (chicken!=0||rabbit!=0) {
		    cout<<chicken<<' '<<rabbit<<endl;
		}else{
			cout<<"No answer"<<endl;
		}
	} // while

	return 0;
}
