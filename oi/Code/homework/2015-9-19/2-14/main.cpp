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
    auto io=StreamRedirect("pyramid.in","pyramid.out");

    int n;
    while (cin>>n) {
    	int width=2*n+1;
    	for (int i=1;
    	     i<=n;
    	     i++) {
    	    for (int cnt=0;
    	         cnt<=-(i-width/2)-1;
    	         cnt++) {
    	        cout<<' ';
    	    }  // for
    	    for (int cnt=0;
    	         cnt<=2*i-2;
    	         cnt++) {
    	        cout<<'#';
    	    }  // for   
    	    cout<<endl;	    
    	}  // for
    	
    } // while
    

    return 0;
}  // function main
