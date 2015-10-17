#include <cmath>
#include <iostream>

using namespace std;

constexpr char NULL_CHAR='\0';

int strlen(const char *s){
	int i=0;

	for (;
	     s[i]!=NULL_CHAR;
	     i++) {}  // for

	return i;
}

int strcmp(const char *a,const char *b){
	int i=0;
	int op=0;
	bool isSame=true;

	for (;
	     a[i]!=NULL_CHAR && b[i]!=NULL_CHAR;
	     i++) {
	    if (a[i]!=b[i]) {
	        isSame=false;

	        if (a[i]<b[i]) {
	            op=-1;
	        }else{
	        	op=1;
	        }

	        break;
	    }
	}  // for

	int lenA=strlen(a);
	int lenB=strlen(b);

	if (isSame && lenA==lenB) {
	    return 0;
	}else{
	    if (op==0) {
	        if (lenA<lenB) {
	            op=-1;
	        }else{
	        	op=1;
	        }
	    }

	    return op * abs(a[i]-b[i]);
	}
}

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);

	string s1,s2;
	cin>>s1>>s2;
	cout<<strcmp(s1.c_str(),s2.c_str())<<'\n';

	return 0;
}