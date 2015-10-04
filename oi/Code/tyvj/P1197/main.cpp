#include <iostream>
#include <deque>

using namespace std;

struct Number {
    deque<int> base;
    deque<int> tail;
};  // struct Number

int GetDigit(const char c){
	switch (c) {
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
	}  // switch to c
	return -1;
}

Number ToNumber(const string &str){
	Number tmp;
	deque *current=&tmp.base;

	for (auto c : str) {
	    if (c=='.') {
	        current=&tmp.tail;
	        continue;
	    }

	    current->push_back()
	}  // foreach in str
}

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);



	return 0;
}