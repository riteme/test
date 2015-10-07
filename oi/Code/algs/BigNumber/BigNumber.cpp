#include <cctype>
#include <deque>
#include <utility>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

typedef signed char DigitType;

DigitType ToDigit(const char c){
	return c-'0';
}

char ToChar(const DigitType d){
	return d+'0';
}

class BigNumber {
public:
	BigNumber():m_op(true) {}
	BigNumber(const string &data):m_op(true) {
		string::size_type left=0;

		if (data.size()<=left){
			return;
		}

		if (!isdigit(data[0])) {
			if (data[0]=='-') {
				m_op=false;
			}

			left++;
		}

		deque<DigitType> *current=&m_base;

		for(string::size_type i=left;i<data.size();i++){
			if (data[i]=='.') {
				current=&m_tail;
			}else{
				current->push_back(ToDigit(data[i]));
			}
		}
	}
	BigNumber(const BigNumber &lhs):m_op(lhs.m_op), m_base(lhs.m_base), m_tail(lhs.m_tail) {}
	BigNumber(BigNumber &&rhs):m_op(rhs.m_op), m_base(std::move(rhs.m_base)), m_tail(std::move(rhs.m_tail)) {}

	BigNumber &operator=(const BigNumber &lhs){
		m_op=lhs.m_op;
		m_base=lhs.m_base;
		m_tail=lhs.m_tail;

		return *this;
	}

	BigNumber &operator=(BigNumber &&rhs){
		m_op=rhs.m_op;
		m_base=std::move(rhs.m_base);
		m_tail=std::move(rhs.m_tail);

		return *this;
	}

	bool operator==(const BigNumber &lhs) const {
		return lhs.m_op==m_op && lhs.m_base==m_base && lhs.m_tail==m_tail;
	}
	bool operator!=(const BigNumber &lhs) const {
		return !((*this)==lhs);
	}
	bool operator<(const BigNumber &lhs) const {
		if (m_op==true && lhs.m_op==false) {
			return false;
		} else if (m_op==false && lhs.m_op==true) {
			return true;
		} else {
			bool result;
			int baseCmp=BaseCompare(lhs);
			int tailCmp=TailCompare(lhs);

			if (baseCmp>0) {
				result = false;
			}else if (baseCmp<0) {
				result = true;
			}else{
				if (tailCmp>=0) {
					result = false;
				}else{
					result = true;
				}
			}

			return !m_op?!result:result;
		}
	}
	bool operator>(const BigNumber &lhs) const {
		return !((*this)<lhs);
	}
	bool operator<=(const BigNumber &lhs) const {
		return (*this)<lhs || (*this) == lhs;
	}
	bool operator>=(const BigNumber &lhs) const {
		return !((*this)<=lhs);
	}

	BigNumber operator+() const {
		return *this;
	}

	BigNumber operator-() const {
		BigNumber tmp=*this;
		tmp.m_op=!tmp.m_op;

		return tmp;
	}

	BigNumber operator+(const BigNumber &lhs) const {
		BigNumber result;
		bool op=true;

		if (m_op==false && lhs.m_op==false) {
			op=false;
		}

		if (m_op!=lhs.m_op) {
			result=Abs(*this)-Abs(lhs);
		}else{
			DigitType upload=AddTail(m_tail,lhs.m_tail,result.m_tail);
			AddBase(m_base,lhs.m_base,result.m_base,upload);
		}

		result.m_op=op;

		result.Shrink();

		return result;
	}

	BigNumber operator-(const BigNumber &lhs) const {
		BigNumber result;
		bool op=true;

		if (*this<lhs){
			op=false;
		}

		if (lhs.m_op==false) {
			result=*this+(-lhs);
		}else{
			if (m_op!=lhs.m_op) {
				result=Abs(*this) + Abs(lhs);
			}else if (*this<lhs) {
				result=lhs-(*this);
			}else{
				auto maxSize=std::max(TailSize(),lhs.TailSize());

				auto tmpa=m_tail;
				auto tmpb=lhs.m_tail;

				tmpa.resize(maxSize);
				tmpb.resize(maxSize);

				DigitType upload=SubtractTail(tmpa,tmpb,result.m_tail);
				SubtractBase(m_base,lhs.m_base,result.m_base,upload);
			}
		}

		result.m_op=op;

		result.Shrink();

		return result;
	}

	BigNumber operator*(const BigNumber &lhs) const {
		// TODO
	}

	BigNumber operator/(const BigNumber &lhs) const {
		// TODO
	}

	BigNumber operator%(const BigNumber &lhs) const {
		// TODO
	}

	bool GetOperator() const {
		return m_op;
	}

	int BaseSize() const {
		return m_base.size();
	}

	int TailSize() const {
		return m_tail.size();
	}

	int Size() const {
		return m_base.size() + m_tail.size();
	}

	string ToString() const {
		string result;

		if (m_op==false) {
			result+='-';
		}

		for(deque<DigitType>::size_type i=0;i<m_base.size();i++){
			result+=ToChar(m_base[i]);
		}

		if (!m_tail.empty()) {
			result+='.';

			for(deque<DigitType>::size_type i=0;i<m_tail.size();i++){
				result+=ToChar(m_tail[i]);
			}
		}

		return result;
	}
private:
	DigitType AddTail(const deque<DigitType> &a,const deque<DigitType> &b,deque<DigitType> &area) const {
		DigitType upload=0;

		auto &m=a.size()<=b.size()?b:a;
		auto &n=a.size()>b.size()?b:a;

		for(int i=n.size();i<m.size();i++){
			area.push_back(m[i]);
		}

		for(int i=n.size()-1;i>=0;i--){
			DigitType sum=m[i]+n[i]+upload;
			DigitType digit=sum%10;
			upload=sum/10;

			area.push_front(digit);
		}

		return upload;
	}

	void AddBase(const deque<DigitType> &a,const deque<DigitType> &b,deque<DigitType> &area,DigitType upload=0) const {
		auto i=a.rbegin();
		auto j=b.rbegin();

		while (i!=a.rend() || j!=b.rend()) {
			DigitType sum;

			if (i==a.rend()) {
				sum=*j+upload;
				j++;
			}else if(j==b.rend()){
				sum=*i+upload;
				i++;
			}else{
				sum=*i+*j+upload;
				i++;j++;
			}

			DigitType digit=sum%10;
			upload = sum/10;

			area.push_front(digit);
  		}   // while

  		if (upload>0) {
  			area.push_front(upload);
  		}
  	}

  	DigitType SubtractTail(const deque<DigitType> &a,const deque<DigitType> &b,deque<DigitType> &area) const {
  		DigitType upload=0;

  		for(int i=a.size()-1;i>=0;i--){
  			DigitType sum=a[i]-b[i]+upload;
  			DigitType digit=(10-(-sum%10))%10;
  			upload=sum/10;

  			area.push_front(digit);
  		}

  		return upload;
  	}

  	void SubtractBase(const deque<DigitType> &a,const deque<DigitType> &b,deque<DigitType> &area,DigitType upload=0) const {
  		auto i=a.rbegin();
  		auto j=b.rbegin();

  		while (i!=a.rend() || j!=b.rend()) {
  			DigitType sum;

  			if (i==a.rend()) {
  				sum=*j+upload;
  				j++;
  			}else if(j==b.rend()){
  				sum=*i+upload;
  				i++;
  			}else{
  				sum=*i-*j+upload;
  				i++;j++;
  			}

  			DigitType digit=(10-(-sum%10))%10;
  			
  			if (sum<0) {
  				upload=-1;
  			}else{
  				upload=0;
  			}

  			area.push_front(digit);
  		}   // while
  	}

  	int BaseCompare(const BigNumber &lhs) const {
  		if (BaseSize() < lhs.BaseSize()) {
  			return -1;
  		}else if (BaseSize() > lhs.BaseSize()) {
  			return 1;
  		}else{
  			for(int i=0;i<BaseSize();i++){
  				if (m_base[i]<lhs.m_base[i]) {
  					return -1;
  				}else if(m_base[i]>lhs.m_base[i]){
  					return 1;
  				}
  			}

  			return 0;
  		}
  	}

  	int TailCompare(const BigNumber &lhs) const {
  		if (m_tail.empty() && lhs.m_tail.empty()) {
  			return 0;
  		}else{
  			auto &m=TailSize()>=lhs.TailSize()?m_tail:lhs.m_tail;
  			auto &n=TailSize()<lhs.TailSize()?m_tail:lhs.m_tail;

  			for(int i=0;i<n.size();i++){
  				if (m_tail[i] < lhs.m_tail[i]) {
  					return -1;
  				}else if (m_tail[i]>lhs.m_tail[i]) {
  					return 1;
  				}
  			}

  			if (TailSize()>lhs.TailSize()) {
  				return 1;
  			}else if (TailSize()<lhs.TailSize()) {
  				return -1;
  			}else{
  				return 0; 
  			}
  		}
  	}

  	void Shrink(){
  		while (m_base.size()>1 && m_base.front()==0) {
  			m_base.pop_front();
		}   // while
		
		while (m_tail.size()>0 && m_tail.back()==0) {
			m_tail.pop_back();
		}   // while

		if (m_base.size()==1 && m_base[0] == 0 && m_tail.size() == 0) {
		    m_op=true;
		}
	}

	bool m_op;
	deque<DigitType> m_base;
	deque<DigitType> m_tail;

	friend BigNumber Abs(const BigNumber &bign);
};  // class BigNumber

BigNumber Abs(const BigNumber &bign){
	if (bign.m_op) {
		return bign;
	}

	BigNumber tmp;
	tmp=bign;

	if (!tmp.m_op) {
		tmp.m_op=true;
	}

	return tmp;
}

const BigNumber ZERO=BigNumber("0");
const BigNumber ONE=BigNumber("1");

int main() {
	ios::sync_with_stdio(false);

	string data1,data2;
	cin>>data1>>data2;

	BigNumber n(data1);
	BigNumber m(data2);

	cout<<n.ToString()<<" + "<<m.ToString()<<" = "<<(n + m).ToString()<<endl;
	cout<<n.ToString()<<" - "<<m.ToString()<<" = "<<(n - m).ToString()<<endl;

	return 0;
}  // function main
