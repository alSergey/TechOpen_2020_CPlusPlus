#include <iostream>
class C;

class A {
public:
    A(int i = 0, C* parent = nullptr) : m_i(i){
        c = parent;
        std::cout << this << "  A(" << m_i << ")" << std::endl;
    }

    A(const A &rhs) {
        std::cout << this << "  A(const A&) m_i=" << m_i << " rhs=" << &rhs << std::endl;
    }

    ~A() {
        std::cout << this << " ~A(" << m_i << ")" << std::endl;
    }

    void attach_parent(C *parent){
        c = parent;
    }
private:
    int m_i;
    C* c;
};

class B {
public:
    B(int i) : m_i(i) {
        std::cout << this << "  B(" << m_i << ")" << std::endl;
    }

    B(const B &rhs) {
        std::cout << this << "  B(const B&) m_i=" << m_i << " rhs=" << &rhs << std::endl;
    }

    ~B() {
        std::cout << this << " ~B(" << m_i << ")" << std::endl;
    }

private:
    int m_i;
};

class C {
public:
    C(int i = 0) : m_i(i), a(m_i + 1), b(1234) {
        std::cout << this << "  C(" << m_i << ")" << std::endl;
    }

    C(const C &rhs) : b(rhs.b) {
        std::cout << this << "  C(const C&) m_i=" << m_i << " rhs=" << &rhs << std::endl;
    }

    ~C() {
        std::cout << this << " ~C(" << m_i << ")" << std::endl;
    }

private:
    int m_i;
    B b;
    A a;
};

int main() {
    C c(159);
    C c1(c);
    return 0;
}