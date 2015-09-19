#include <iostream>
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

vector<int> numbers;

int main(int argc, char **argv) {
    auto io=StreamRedirect("","arrange.out");

    for (int i=1;
         i<=9;
         i++) {
        for (int j=1;
             j<=9;
             j++) {
        	if(j!=i){
            for (int k=1;
                 k<=9;
                 k++) {
            	if (k!=i&&k!=j) {
                	numbers.push_back(i*100+j*10+k);
            	}
            }  // for
        }
        }  // for
    }  // for

    // cout<<numbers.size()<<endl;
    
    for (int i=0;
         i!=numbers.size();
         i++) {
        for (int j=0;
             j!=numbers.size();
             j++) {
        	if(j!=i){
            for (int k=0;
                 k!=numbers.size();
                 k++) {
            	if(k!=i&&k!=j){
                if (numbers[i]*2==numbers[j]&&numbers[i]*3==numbers[k]) {
                    cout<<numbers[i]<<' '<<numbers[j]<<' '<<numbers[k]<<endl;
                }
            }
            }  // for
        }
        }  // for
    }  // for

    return 0;
}  // function main
