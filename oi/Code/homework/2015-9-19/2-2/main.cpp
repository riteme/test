#include <cmath>
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

double eval(double a,double b,double deta,bool posi=true){
	return ((-b) + (posi?sqrt(deta):-sqrt(deta))) / (2.0 * a);
}

int main(int argc, char const *argv[])
{
	auto io =StreamRedirect("equation.in","equation.out");

	int a,b,c;
	while (cin>>a>>b>>c) {
		int deta=b*b-4*a*c;

		if (a==0) {
		    cout<<(-c/static_cast<double>(b))<<endl;
		}
		else if (deta<0) {
		    cout<<"No answer"<<endl;
		}else if(deta>=0){
			cout<<eval(a,b,deta)<<' '<<eval(a,b,deta,false)<<endl;
		}

	} // while
	

	return 0;
}