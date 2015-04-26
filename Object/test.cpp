#include <iostream>
using namespace std;

class A;

class Object {
  public:
	virtual A GetA();
}; // class Object

class A: public Object {
  public:
	int i = 100;
	int GetInt() {
		return i;
	}
	virtual A GetA() {
		return *this;
	}
}; // class A:public Object

A Object::GetA() {
	return this->GetA();
}

int main(int argc, char *argv[]) {
	A a;
	Object obj;
	a.i = 101;
	obj = a;
	cout << obj.GetA().GetInt() << endl;
	return 0;
} //function main