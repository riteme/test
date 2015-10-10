#include <iostream>
using namespace std;

template <typename T>
void PrintArray(const T &a){
	for (auto &e : a) {
	    cout<<e<<' ';
	}  // foreach in a
	cout<<endl;
}

template <typename T,unsigned N>
void PrintArray(const T (&a)[N]){
	for (int i=0;
	     i<N;
	     i++) {
	    cout<<a[i]<<' ';
	}  // for
	cout<<endl;
}

template <typename T>
class PtrDeleter {
  public:
    PtrDeleter()=default;
    PtrDeleter(T *target):m_pTarget(target) {}
    ~PtrDeleter(){
    	if (m_pTarget!=nullptr) {
    	    delete m_pTarget;
    	}
    }

    void Reset(T *target){
    	m_pTarget=target;
    }

  private:
    T *m_pTarget=nullptr;
};  // class PtrDeleter

template <typename T>
class ArrayPtrDeleter {
  public:
    ArrayPtrDeleter()=default;
    ArrayPtrDeleter(T *target):m_pTarget(target) {}
    ~ArrayPtrDeleter(){
    	if (m_pTarget!=nullptr) {
    	    delete [] m_pTarget;
    	}
    }

    void Reset(T *target){
    	m_pTarget=target;
    }

  private:
    T *m_pTarget=nullptr;
};  // class ArrayPtrDeleter