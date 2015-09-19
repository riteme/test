#include <iostream>
#include <cmath>
#include <vector>

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

bool IsPrime(int num){
	int sqrted=sqrt(num);

	for (int i=3;
	     i<=sqrted;
	     i+=2) {
	    if (num%i==0) {
	        return false;
	    }
	}  // for
	
	return true;
}

int main(int argc, char **argv) {
    auto io=StreamRedirect("goldbach.in","goldbach.out");

    int n;
    while (cin>>n) {
    	if(n<=6){
    		cout<<"Input error"<<endl;
    		continue;
    	}

    	vector<int> numbers;
    	for (int i=3;
    	     i<=n;
    	     i+=2) {
    	    if (IsPrime(i)) {
    	        numbers.push_back(i);
    	    }
    	}  // for
    	
    	int a,b;
    	a=b=0;
    	for (int i=0;
    	     i!=numbers.size();
    	     i++) {
    	    for (int j=i+1;
    	         j<=numbers.size();
    	         j++) {
    	        if (numbers[i]+numbers[j]==n) {
    	            a=numbers[i];
    	            b=numbers[j];
    	        }
    	    }  // for
    	}  // for
    	cout<<n<<'='<<a<<'+'<<b<<endl;
    } // while

    return 0;
}  // function main
