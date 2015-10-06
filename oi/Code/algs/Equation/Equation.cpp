#include <cctype>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <list>

using namespace std;

#define NULL_CHAR '\0'
#define EQUATION_SIZE 512

// 表示单项式
struct Element {
	Element():Const(1),Unknown(NULL_CHAR) {}
	Element(int c,char u):Const(c),Unknown(u) {}

	int Const;  // 单项式的系数
	char Unknown;  // 未知数，如果没有则为NULL
};  // struct Element

// 处理原始数据变为单项式
Element ProcessElementData(const string &data){
	Element e;
	string::size_type left=0, right=data.size();  // 左右边界，最终会收缩到只有数字的范围

	// 确定是否有未知数
	if (!isdigit(data[data.size()-1])) {
		e.Unknown=data[data.size()-1];
		right--;
	}

	int op=1;

	// 确定是否有正负号
	if (!isdigit(data[0])) {
		if (data[0]=='-') {
			op=-1;
			left++;
		}else if (data[0]=='+') {
			left++;
		}
	}

	// 如果有数字就转换
	if (right-left>=1) {
		e.Const=atoi(data.substr(left,right-left).c_str());
	}

	// 纠正系数负号
	e.Const*=op;

	return e;
}

// 处理表达式为一个单项式的链表
list<Element> ParseExpression(const string &in,const char delim='='){
	if (in.empty()) {
		return list<Element>();
	}

	list<Element> ast;

	string buffer;
	string::size_type pos=0;
	char c;
	c=in[pos++];

	bool finished=false;  // 表示处理是否完成
	while (!finished) {
		buffer+=c;

		if (pos<in.size()) {    
			c=in[pos++];
		}else{
			c=delim;  // 如果读取完毕，则将当前字符设为结尾符，方便后续判断
		}

		if (c=='+' || c=='-' || c==delim) {
		    ast.push_back(ProcessElementData(buffer));
		    buffer.clear();
		}

		if (pos>=in.size()) {
		    finished=true;

		    if (c!='+' && c!='-' && c!=delim) {	        
			    ast.push_back(ProcessElementData(buffer+c));
			    buffer.clear();
		    }
		}
	}   // while

	return ast;
}

int main() {
	char equationBuffer[EQUATION_SIZE];
	scanf("%s",equationBuffer);
	string equation=equationBuffer;

	// 找到方程中的等于号，方便切分左右的表达式
	string::size_type splitIndex=equation.find('=');

	// 分别处理左右两边的表达式
	list<Element> left=ParseExpression(equation.substr(0,splitIndex));
	list<Element> right=ParseExpression(equation.substr(splitIndex+1,equation.size()-splitIndex));

	int constSum=0;  // 常数项之和
	int unknownSum=0;  // 单项式系数之和
	char unknown=NULL_CHAR;  // 中途记录未知数是哪一个

	// 遍历左表达式
	for (list<Element>::iterator beg=left.begin();beg!=left.end();beg++){
		if (beg->Unknown!=NULL_CHAR) {
		    unknownSum+=beg->Const;
		    unknown=beg->Unknown;
		}else{
			constSum+=-beg->Const;
		}
	}

	// 遍历右表达式
	for (list<Element>::iterator beg=right.begin();beg!=right.end();beg++){
		if (beg->Unknown!=NULL_CHAR) {
		    unknownSum+=-beg->Const;
		    unknown=beg->Unknown;
		}else{
			constSum+=beg->Const;
		}
	}

	// 计算结果
	double result = double(constSum) / double(unknownSum);

	// 防止意外的负号，有时候结果为0，输出却会有个负号...
	if (result==0.0) {
	    result=0.0;
	}

	printf("%c=%.3f\n", unknown, result);

	return 0;
}  // function main
