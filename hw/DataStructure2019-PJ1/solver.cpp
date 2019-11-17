#include <iostream>
using namespace std;

int main() {
	int n;
	//read array length
	cin >> n;
	for (int i = 100000; i --; ){
		//print x and y. 1 <= x, y <= n and x != y
		cout << "1 3\n";
		//flush stdout. you can also use { cout << endl; } to instead { cout << "\n"; cout << flush; }
		cout << flush;
		int t1;
		//get comparison result of a[x] and a[y]
		cin >> t1;
	}
	//print 0 0 and flush to terminate ask
	cout << "0 0" << endl;
	//print swap times m and flush
	cout << 2 << endl;
	//print x, y to swap a[x] and a[y] and flush. 1 <= x, y <= n and x != y
	cout << "3 4" << endl << "3 5" << endl;
	int result;
	//!!!IMPORTANT!!! you should read the final score
	//without this judger may get "reached EOF" error.
	cin >> result;
	return 0;
}