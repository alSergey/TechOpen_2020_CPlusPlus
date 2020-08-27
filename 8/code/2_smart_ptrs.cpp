#include <iostream>
#include <memory>
#include <vector>

class A {
 public:
  A(int i = 1337)
      : m_i(i) {
    std::cout << this << "  A(" << m_i << ")" << std::endl;
  }

  A(const A& rhs) {
    std::cout << this << "  A(const A&) m_i=" << m_i << " rhs=" << &rhs << std::endl;
  }

  ~A() {
    std::cout << this << " ~A(" << m_i << ")" << std::endl;
  }


  virtual
  void foo() {
    std::cout << "foo A" << std::endl;
  }

  int m_i;
};

class B : public A {
 public:
  B(int i = 789)
      : A(i + 1)
      , m_i(i) {
    std::cout << this << "  B(" << m_i << ")" << std::endl;
  }

  B(const B& rhs) {
    std::cout << this << "  B(const B&) m_i=" << m_i << " rhs=" << &rhs << std::endl;
  }

  ~B() {
    std::cout << this << " ~B(" << m_i << ")" << std::endl;
  }

  virtual
  void foo() {
    std::cout << "foo B" << std::endl;
  }

  void foo_b() {
    std::cout << "foo_b B" << std::endl;
  }
 private:
  int m_i;
};

class UniquePtrA {
 public:
  UniquePtrA(int i)
      : m_ptr(new A(i)) {
  }

  UniquePtrA(const UniquePtrA&) = delete;

  ~UniquePtrA() {
    delete m_ptr;
  }

  A* operator->() {
    return m_ptr;
  }

 private:
  A* m_ptr;
};

void foo(UniquePtrA a) {
  a->m_i = 14;
}

void foo(std::unique_ptr<A> ptr) {
  ptr->m_i = 14;
}

void foo(std::shared_ptr<A> ptr) {
  ptr->m_i = 14;
}

//class Wolf {
//  Wolf(std::shared_ptr<Texture> texture)
//      : texture(texture) {
//  }
//
// private:
//  std::shared_ptr<Texture> texture;
//};

int main() {
//  UniquePtrA ptr(2007);
//  foo(ptr);
//
//  std::cout << ptr->m_i;

//  std::unique_ptr<A> ptr_up = std::make_unique<A>(123);
//  foo(std::move(ptr_up));

//  std::cout << ptr_up->m_i << std::endl; // <- BAD!!!

//  std::shared_ptr<Texture> texture = std::make_shared<Texture>();
//
//  std::shared_ptr<Wolf> wolf1 = std::make_shared<Wolf>(texture);
//  std::shared_ptr<Wolf> wolf2 = std::make_shared<Wolf>(texture);
//  std::shared_ptr<Wolf> wolf3 = std::make_shared<Wolf>(texture);
//  std::shared_ptr<Wolf> wolf4 = std::make_shared<Wolf>(texture);

//  std::shared_ptr<A> ptr_sh = std::make_shared<A>();
//  auto ptr_sh_2 = ptr_sh;
//  auto ptr_sh_3 = ptr_sh;
//  foo(ptr_sh_3);
//  auto ptr_sh_4 = ptr_sh;
//  auto ptr_sh_5 = ptr_sh;
//
//  std::weak_ptr<A> ptr_w = ptr_sh;
//
//  std::cout << ptr_sh_4.use_count() << std::endl;
//  std::cout << ptr_sh.use_count() << std::endl;
//  std::cout << ptr_sh_4.use_count() << std::endl;
//  std::cout << ptr_sh_5->m_i << std::endl;
//  std::cout << ptr_sh->m_i << std::endl;
//
//  if (!ptr_w.expired()) {
//    std::shared_ptr<A> sh_ptr = ptr_w.lock();
//
//    std::cout << sh_ptr.use_count() << std::endl;
//    std::cout << sh_ptr->m_i << std::endl;
//  }

  std::vector<std::shared_ptr<B>> arr_b = {
      std::make_shared<B>(2),
      std::make_shared<B>(4),
      std::make_shared<B>(5),
  };
  std::vector<std::shared_ptr<A>> arr_a = {
      std::make_shared<A>(1),
      std::make_shared<A>(3),
  };

  for (auto ptr: arr_b) {
    arr_a.push_back(ptr);
  }

  arr_a[1] = std::make_shared<A>(10);

  for (auto ptr: arr_b) {
    ptr->foo_b();
  }
  for (auto ptr: arr_a) {
    ptr->foo();
  }

  foo(arr_b[1]);

  return 0;
}