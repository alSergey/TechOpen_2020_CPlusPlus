#pragma once

#include <vector>
#include <iosfwd>

namespace prep {
class Matrix {
 public:
  explicit Matrix(size_t rows = 0, size_t cols = 0);
  explicit Matrix(std::istream& is);
  Matrix(const Matrix& rhs) = default;
  Matrix& operator=(const Matrix& rhs) = default;
  ~Matrix() = default;

  // Получение количества строк и столбцов
  size_t getRows() const;
  size_t getCols() const;

  // Получение и присвоение элемента
  double operator()(size_t i, size_t j) const;
  double& operator()(size_t i, size_t j);

  // Операторы сравнения
  bool operator==(const Matrix& rhs) const;
  bool operator!=(const Matrix& rhs) const;

  // Базовые математические операции
  Matrix operator+(const Matrix& rhs) const;
  Matrix operator-(const Matrix& rhs) const;
  Matrix operator*(const Matrix& rhs) const;

  // Правостороннее умножение
  Matrix operator*(double val) const;

  friend
  Matrix operator*(double val, const Matrix& matrix);
  friend
  std::ostream& operator<<(std::ostream& os, const Matrix& matrix);


  // Экстра функции
  Matrix transp() const;
  double det() const;
  Matrix adj() const;
  Matrix inv() const;
  Matrix minor(size_t size, size_t row, size_t col) const;

 private:
    size_t rowsSize{};
    size_t colsSize{};
    std::vector<std::vector<double>> data;
};

Matrix operator*(double val, const Matrix& matrix);
std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
}  // namespace prep
