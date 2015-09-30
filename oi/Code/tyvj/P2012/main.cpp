#include <iostream>
// #include <vector>
// #include <unordered_map>
// #include <functional>

using namespace std;

typedef unsigned long ValueType;
typedef unsigned IndexType;
// typedef vector<vector<ValueType>> Matrix;
// typedef function<void(Matrix&,IndexType,IndexType)> CommandType;

constexpr char LINE_EXCHANGE='R';
constexpr char COLUMN_EXCHANGE='C';
constexpr char ELEMENT_ACCESS='A';

// unordered_map<char,CommandType> funcMap;

// void LineExchange(Matrix &m,IndexType x,IndexType y);
// void ColumnExchange(Matrix &m,IndexType x,IndexType y);
// void ELementAccess(Matrix &m,IndexType x,IndexType y);

void LineExchange(ValueType *m,IndexType x,IndexType y,IndexType n);
void ColumnExchange(ValueType *m,IndexType x,IndexType y,IndexType n);
void ELementAccess(ValueType *m,IndexType x,IndexType y,IndexType n);

int main()
{
	cout.sync_with_stdio(false);

	// funcMap[LINE_EXCHANGE]=LineExchange;
	// funcMap[COLUMN_EXCHANGE]=ColumnExchange;
	// funcMap[ELEMENT_ACCESS]=ELementAccess;

	IndexType n,k;
	cin>>n>>k;

	// Matrix mat;
	// mat.resize(n);
	// for (auto &line : mat) {
	//     line.resize(n);
	// }  // foreach in mat

	ValueType mat[n][n];

	for (IndexType i=0;
	     i<n;
	     i++) {
		for (IndexType j=0;
		     j<n;
		     j++) {
			ValueType tmp;
			cin>>tmp;
			mat[i][j]=tmp;
		}  // for
	}  // for

	for (IndexType cnt=1;
	     cnt<=k;
	     cnt++) {
	    char command;
		IndexType x,y;

		cin>>command>>x>>y;

		// funcMap[command](mat,x-1,y-1);
		switch (command) {
		    case LINE_EXCHANGE:
		    	LineExchange(&(mat[0][0]),x-1,y-1,n);
		    	break;
		    case COLUMN_EXCHANGE:
		    	ColumnExchange(&(mat[0][0]),x-1,y-1,n);
		    	break;
		    case ELEMENT_ACCESS:
		    	ELementAccess(&(mat[0][0]),x-1,y-1,n);
		    	break;
		}  // switch to command
	}  // for

	return 0;
}

// R
void LineExchange(ValueType *m,IndexType x,IndexType y,IndexType n){
	// IndexType n=m.size();

	for (IndexType i=0;
	     i<n;
	     i++) {
	    std::swap(*(m+n*x+i),*(m+n*y+i));
	}  // for
}

// C
void ColumnExchange(ValueType *m,IndexType x,IndexType y,IndexType n){
	// IndexType n=m.size();

	for (IndexType i=0;
	     i<n;
	     i++) {
	    std::swap(*(m+i*n+x),*(m+i*n+y));
	}  // for
}

// A
void ELementAccess(ValueType *m,IndexType x,IndexType y,IndexType n){
	cout<<*(m+x*n+y)<<endl;
}
