#include <iostream>
#include <deque>

using namespace std;

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

char GetChar(const int c){
	switch (c) {
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
	}  // switch to c
	return '?';
}

struct Number {
    deque<int> base;
    deque<int> tail;

    Number(const string &str){
    	// 构造函数
    	deque<int> *current=&base;

    	for (auto c : str) {
    	    if (c=='.') {
    	        current=&tail;
    	        continue;
    	    }

    	    current->push_back(GetDigit(c));
    	}  // foreach in str
    }

    void Append(Number &lhs){
    	// 先计算小数部分
    	// 得到进位后计算前面的部分
    	ComputeBase(lhs,ComputeTail(lhs));
    }

    // 没卵用
    bool HasDot() const {
    	return tail.size()!=0;
    }

    // 将左右两边多余的0去掉
    void Shrink(){
    	// 注意：应先进行边界检查在对成员进行访问！防止Segfault!!!!!
    	while (base.size()>1 && base.front()==0) {
    		base.pop_front();
    	}   // while

    	while (!tail.empty() && tail.back()==0) {
    		tail.pop_back();
    	}   // while
    }

    // 这个没什么卵用
    string ToString(){
    	string tmp;

    	for (auto i : base) {
    	    tmp+=GetChar(i);
    	}  // foreach in base

    	if (tail.size()>0) {
    	    tmp+='.';

    	    for (auto i : tail) {
    	        tmp+=GetChar(i);
    	    }  // foreach in tail
    	}

    	return tmp;
    }

 private:
 	int ComputeTail(Number &lhs){
 		deque<int> &m=lhs.tail.size()<=tail.size()?tail:lhs.tail;  // 位数较大的二进制
 		deque<int> &n=lhs.tail.size()>tail.size()?tail:lhs.tail;  // 位数较小的

 		int upload=0;  // 进位
 		for (int i=n.size()-1;
 		     i>=0;
 		     i--) {
 		    int sum=m[i]+n[i]+upload;
 			int digit=sum%2;

 			upload=sum/2;

 			m[i]=digit;  // 用位数大的数来存储结果
 		}  // for

 		tail=m;  // 将结果转给自己

 		return upload;  // 给前半部分进位
 	}

 	void ComputeBase(Number &lhs,int upload=0){
 		// 与上面类似
 		deque<int> &m=lhs.base.size()<=base.size()?base:lhs.base;
 		deque<int> &n=lhs.base.size()>base.size()?base:lhs.base;

 		for (int i=m.size()-1;
 		     i>=int(m.size()-n.size());  // 警告，size_type是无符号类型，与int进行比较时，int会变成unsigned，产生令人目瞪口呆的结果...
 		     i--) {
 		    int sum=m[i]+n[i-m.size()+n.size()]+upload;
 			int digit=sum%2;

 			upload=sum/2;

 			m[i]=digit;
 		}  // for

 		// 处理进位
 		for (int i=m.size()-n.size()-1;
 		     i>=0 && upload!=0;
 		     i--) {
	        int sum=m[i]+upload;
	    	int digit=sum%2;

	    	upload=sum/2;

	    	m[i]=digit;
 		}  // for

 		// 如果到最后还有进位，直接新增一位
 		if (upload!=0) {
 		    m.push_front(upload);
 		}

 		base=m;
 	}
};  // struct Number

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);

	string a,b;
	cin>>a>>b;

	Number na(a),nb(b);

	na.Append(nb);
	na.Shrink();

	deque<int> pos;
	for (int i=na.base.size();
	     i>0;
	     i--) {
	    if (na.base[i-1]==1) {
	        pos.push_front(na.base.size()-i+1);
	    }
	}  // for

	for (int i=1;
	     i<=na.tail.size();
	     i++) {
	    if (na.tail[i-1]==1) {
	        pos.push_back(-i);
	    }
	}  // for

	for (auto i : pos) {
	    cout<<i<<' ';
	}  // foreach in pos
	cout<<endl;

	return 0;
}