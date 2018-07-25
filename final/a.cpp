#include <iostream>
using std::cout;
using std::cin;
using std::endl;

class Base {
  public:
    Base() = default;
    virtual ~Base() = default;
    virtual void Print(int a) { cout << a << endl; }
    int a = 0;

  protected:
    int num = 1;
};

class D1 : public Base {
  public:
    D1() = default;
    virtual ~D1() = default;
    virtual void Print(int a) override { cout << "number is " << a << endl; }
    virtual void Print(std::string &s) { cout << s << endl; }

  private:
    using Base::a;
};

class D2 : public Base {
  public:
    D2() = default;
    virtual ~D2() = default;
    virtual void Print(int a) override { cout << "the number is" << a << endl; }
    virtual void Print(double num) { cout << "double is " << num << endl; }
    using Base::num;
};

int main(int argc, char **argv) {
    D1 ins1;
    Base *p1 = &ins1;
    cout << p1->a << endl;
    /* D1* p2=p1; */
    /* D1 *p3 = dynamic_cast<D1 *>(p1); */
    /* D1 *p3 = static_cast<D1 *>(p1); */
    D2 *p4 = dynamic_cast<D2 *>(p1);
    p4->Print(3.0);
    D2 ins2;
    ins2.Print(1);
    cout << ins2.num << endl;
}
