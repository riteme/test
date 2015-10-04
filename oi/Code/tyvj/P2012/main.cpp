#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;

typedef unsigned long ValueType;
typedef unsigned IndexType;
typedef vector<vector<ValueType>> Matrix;
typedef function<void(IndexType,IndexType)> CommandType;

constexpr char LINE_EXCHANGE='R';
constexpr char COLUMN_EXCHANGE='C';
constexpr char ELEMENT_ACCESS='A';
constexpr char SHOW_MATRIX='S';

unordered_map<char,CommandType> funcMap;

void LineExchange(IndexType x,IndexType y);
void ColumnExchange(IndexType x,IndexType y);
void ELementAccess(IndexType x,IndexType y);
void ShowMatrix(IndexType x,IndexType y);

Matrix mat;
vector<IndexType> lines;
vector<IndexType> columns;

int main()
{
	ios::sync_with_stdio(false);

	funcMap[LINE_EXCHANGE]=LineExchange;
	funcMap[COLUMN_EXCHANGE]=ColumnExchange;
	funcMap[ELEMENT_ACCESS]=ELementAccess;
	funcMap[SHOW_MATRIX]=ShowMatrix;

	IndexType n,k;
	cin>>n>>k;

	mat.resize(n);
	for (auto &line : mat) {
	    line.resize(n);
	}  // foreach in mat

	lines.resize(n);
	columns.resize(n);
	for (int i=0;
	     i<n;
	     i++) {
	    lines[i]=i;
		columns[i]=i;
	}  // for

	for (int i=0;
	     i<n;
	     i++) {
	    for (int j=0;
	         j<n;
	         j++) {
	        cin>>mat[i][j];
	    }  // for
	}  // for

	for (IndexType cnt=1;
	     cnt<=k;
	     cnt++) {
	    char command;
		IndexType x,y;

		cin>>command>>x>>y;

		funcMap[command](x-1,y-1);
	}  // for

	return 0;
}

// R
void LineExchange(IndexType x,IndexType y){
	std::swap(lines[x],lines[y]);
}

// C
void ColumnExchange(IndexType x,IndexType y){
	std::swap(columns[x],columns[y]);
}

// A
void ELementAccess(IndexType x,IndexType y){
	cout<<mat[lines[x]][columns[y]]<<'\n';
}

void ShowMatrix(IndexType x,IndexType y){
	cout<<"====="<<'\n';
	for (auto i : lines) {
	    for (auto j : columns) {
	        cout<<mat[i][j]<<' ';
	    }  // foreach in columns
	    cout<<'\n';
	}  // foreach in lines
	cout<<"====="<<'\n';
}
