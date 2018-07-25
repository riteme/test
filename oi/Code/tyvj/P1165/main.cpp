#include <iostream>
#include <cstdlib>
#include <deque>

using namespace std;

int GetDigit(const char c){
	switch(c){
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
	}
}

char GetChar(const int c){
	switch(c){
		case 0: return '0';
		case 1: return '1';
		case 2: return '2';
		case 3: return '3';
		case 4: return '4';
		case 5: return '5';
		case 6: return '6';
		case 7: return '7';
		case 8: return '8';
		case 9: return '9';
	}
}

template <typename TContainer>
void ParseData(
    const string &data,
    TContainer &base,
    TContainer &tail
    ){
    TContainer *current=&base;
    
    for(auto c:data){
    	if(c=='.'){
    		current=&tail;
    		continue;
    	}
    	
    	current->push_back(GetDigit(c));
    }
}

template <typename TIteratable>
string GenerateString(
    const TIteratable &base,
    const TIteratable &tail
    ){
    string tmp;
    
    for(auto &e:base){
    	tmp+=GetChar(e);
    }
    
    if(!tail.empty()){
    	tmp+='.';
    	
    	for(auto &e:tail){
    		tmp+=GetChar(e);
    	}
    }
    
    return tmp;
}

template <typename TResizable>
void Shrink(
    TResizable &base,
    TResizable &tail
   ){
    while(base.size()>1 &&
          base.front()==0
         ){
         base.pop_front();
    }
    
    while(tail.size()>0 &&
          tail.back()==0
         ){
         tail.pop_back();
    }
}

int main(){
	deque<int> base;
	deque<int> tail;
	string numData;
	
	while(cin>>numData){
		base.clear();
		tail.clear();
		
		bool baseOp=true;
		
		if(numData.front()=='-'){
			numData.erase(0,1);
		    baseOp=false;
		}
		
		ParseData(numData,base,tail);
		
		Shrink(base,tail);
		
		if(base.size()==1 &&
		   base.front()==0 &&
		   tail.empty()
		  ){
		    cout<<0<<endl;
		    continue;
		}
		
		bool nOp=true;
		int n=0;
		
		if(base.size()==1 &&
		   base.front()==0
		  ){
		    nOp=false;
	    }
	    
	    if(nOp){
	    	while(base.size()>1){
	    		tail.push_front(base.back());
	    		base.pop_back();
	    		n++;
	    	}
	    }else{
	    	while(base[0]==0){
	    		base[0]=tail.front();
	    		tail.pop_front();
	    		n++;
	    	}
	    }
	    
	    Shrink(base,tail);
	    
	    if(!baseOp){
	    	cout<<'-';
	    }
	    
	    bool notEqOne=false;
	    if(!(base.size()==1 &&
	       base[0]==1 &&
	       tail.empty()
	      )){
	        cout<<GenerateString(base,tail);
	        notEqOne=true;
	    }else if(n==0){
	    	cout<<1<<endl;
	    	continue;
	    }
	    
	    if(notEqOne && n!=0){
	    	cout<<'*';
	    }
	    
	    if(n!=0){
	    	cout<<10;
	    	
	    	if(n!=1){
	    		cout<<'^';
	    		cout<<(nOp?"":"(-");
	    		cout<<n;
	    		cout<<(nOp?"":")");
	    	}
	    }
	    
	    cout<<endl;
	}
	
	return EXIT_SUCCESS;
}






















