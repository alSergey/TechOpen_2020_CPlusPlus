#include <iostream>

class A {
public:
    A(int i = 0) : m_i(i) {
        std::cout << this << "  A(" << m_i << ")" << std::endl;
    }

    A(const A &rhs): m_i(rhs.m_i) {
        std::cout << this << "  A(const A&) m_i=" << m_i << " rhs=" << &rhs << std::endl;
    }

    ~A() {
        std::cout << this << " ~A(" << m_i << ")" << std::endl;
    }

private:
    int m_i;
};

void pass_by_value(A a) {
    std::cout << "pass_by_value " << &a << std::endl;
    (void) a;
}

A ret_by_value() {
    A a(17);
    std::cout << "ret_by_value " << &a << std::endl;
    return a;
}

void throw_exception() {
    A a(1337);
    std::cout << "throw " << &a << std::endl;
    throw a;
}

int main() {
    A a_orig(2007);
    A explicit_call(a_orig);
//    a_orig == explicit_call; //true
    A implicit_call = a_orig;

    pass_by_value(a_orig);
    A ret = ret_by_value();

    try {
        throw_exception();
    }
    catch (A exc) {
        std::cout << "catch_exception_by_value " << &exc << std::endl;
    }

    try {
        throw_exception();
    }
    catch (const A &exc) {
        std::cout << "catch_exception_by_ref " << &exc << std::endl;
    }

    return 0;
}