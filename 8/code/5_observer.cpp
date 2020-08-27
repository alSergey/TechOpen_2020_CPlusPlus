//
// Created by tsv on 24.02.17.
//
#include <iostream>

#ifndef CUDASOLVER_OBSERVABLEVALUE_HPP
#define CUDASOLVER_OBSERVABLEVALUE_HPP

#include <boost/signals2.hpp>


template<class T>
class ObservableValue {
 public:
  using signal_t = boost::signals2::signal<void()>;

  explicit ObservableValue(const T& value = T())
      : m_value(value) {
  }

  ObservableValue(const ObservableValue& rhs)
      : ObservableValue(rhs.m_value) {
  }

  virtual
  ~ObservableValue() {
    signal.disconnect_all_slots();
  }

  const T&
  get() const {
    return m_value;
  }

  void
  set(const T& value) {
    if (m_value != value) {
      m_value = value;
      signal();
    }
  }

  void
  connect(const signal_t::slot_type& slot) const {
    signal.connect(slot);
  }

  operator T() const {
    return m_value;
  }

  ObservableValue&
  operator=(const T& value) {
    set(value);
    return *this;
  }

  const ObservableValue&
  operator+=(const T& value) {
    set(m_value + value);
    return *this;
  }

 private:
  T m_value;
  mutable signal_t signal;
};

#endif //CUDASOLVER_OBSERVABLEVALUE_HPP

class Compute {
 public:
  ObservableValue<double> x;
  ObservableValue<double> y;
  ObservableValue<double> h;

  Compute() {
    x.connect(std::bind(&Compute::change_h, this));
    y.connect(std::bind(&Compute::change_h, this));

    h.connect([this] {
      change_y();
    });
  }

  const int n = 100;

  void change_x() {
    x = y - h * n;
  }

  void change_y() {
    y = x + h * n;
  }

  void change_h() {
    h = (y - x) / n;
  }

  double get_result() {
    return x + y + h;
  }

  friend
  std::ostream& operator<<(std::ostream& os, const Compute& c) {
    os << c.x << ' ' << c.y << ' ' << c.h << std::endl;
    return os;
  }
};

struct Point{
  double x, y;
};

int main() {
  Compute c;
  std::cout << c;
  c.y = 5;
  std::cout << c;

  c.h = 0.001;
  std::cout << c;

  return 0;
}