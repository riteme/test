/**
 * 4.30.2015
 * Just for fun.
 * class ptr;
 * template class ptrT
 * ~
 */
#include <iostream>
using namespace std;

struct A {
	int a = 0;
}; // struct A

class ptr {
	A *m_p = nullptr;
  public:
	ptr() = default;
	~ptr() = default;
	ptr(A *p): m_p(p) {

	}
	ptr &operator=(A *value) {
		this->m_p = value;
		return *this;
	}

	operator A*() {
		return this->m_p;
	}
	A **operator&() {
		return &m_p;
	}
	A &operator*() {
		return *this->m_p;
	}
	A *operator->() {
		return this->m_p;
	}
}; // class ptr

template<typename T>
class ptrT {
	T *m_p = nullptr;
  public:
	ptrT() = default;
	~ptrT() = default;
	ptrT(T *p): m_p(p) {

	}
	ptrT &operator=(T *value) {
		this->m_p = value;
		return *this;
	}

	operator T*() {
		return this->m_p;
	}
	T **operator&() {
		return &m_p;
	}
	T &operator*() {
		return *this->m_p;
	}
	T *operator->() {
		return this->m_p;
	}
}; // class ptrT

int main(int argc, char **argv) {
	ptrT<A> p;
	p = new A;
	p->a = 1;
	cout << p->a << endl;
	delete p;
	return 0;
} //function main