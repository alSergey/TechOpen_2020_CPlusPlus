#include <istream>
#include <iomanip>
#include <cmath>
#include "matrix.h"
#include "exceptions.h"

namespace prep {
    Matrix::Matrix(size_t rows, size_t cols)
        : rowsSize(rows),
        colsSize(cols),
        data(rows, std::vector<double> (cols, 0))  {
    }

    Matrix::Matrix(std::istream& is) {
        is >> rowsSize >> colsSize;
        if (!is) {
            throw InvalidMatrixStream();
        }

        data.resize(rowsSize, std::vector<double>(colsSize, 0));
        for (size_t i = 0; i < rowsSize; i++) {
            for (size_t j = 0; j < colsSize; j++) {
                is >> data[i][j];
                if (!is) {
                    throw InvalidMatrixStream();
                }
            }
        }
    }

    // Получение количества строк и столбцов
    size_t Matrix::getRows() const {
        return rowsSize;
    }

    size_t Matrix::getCols() const {
        return colsSize;
    }

    // Получение и присвоение элемента
    double Matrix::operator()(size_t i, size_t j) const {
        if (i >= rowsSize || j >= colsSize) {
            throw OutOfRange(i, j, *this);
        }

        return this->data[i][j];
    }

    double& Matrix::operator()(size_t i, size_t j) {
        if (i >= rowsSize || j >= colsSize) {
            throw OutOfRange(i, j, *this);
        }

        return this->data[i][j];
    }

    // Операторы сравнения
    bool Matrix::operator==(const Matrix &rhs) const {
        if (this->rowsSize != rhs.rowsSize || this->colsSize != rhs.colsSize) {
            return false;
        }

        for (size_t i = 0; i < this->rowsSize; i++) {
            for (size_t j = 0; j < this->colsSize; j++) {
                if (std::abs(this->data[i][j] - rhs.data[i][j]) >= 1e-7) {
                    return false;
                }
            }
        }

        return true;
    }

    bool Matrix::operator!=(const Matrix &rhs) const {
        return !(*this == rhs);
    }

    // Базовые математические операции
    Matrix Matrix::operator+(const Matrix &rhs) const {
        if (this->rowsSize != rhs.rowsSize || this->colsSize != rhs.colsSize) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix result(this->rowsSize, this->colsSize);

        for (size_t i = 0; i < this->rowsSize; i++) {
            for (size_t j = 0; j < this->colsSize; j++) {
                result.data[i][j] = this->data[i][j] + rhs.data[i][j];
            }
        }

        return result;
    }

    Matrix Matrix::operator-(const Matrix &rhs) const {
        if (this->rowsSize != rhs.rowsSize || this->colsSize != rhs.colsSize) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix result(this->rowsSize, this->colsSize);

        for (size_t i = 0; i < this->rowsSize; i++) {
            for (size_t j = 0; j < this->colsSize; j++) {
                result.data[i][j] = this->data[i][j] - rhs.data[i][j];
            }
        }

        return result;
    }

    Matrix Matrix::operator*(const Matrix &rhs) const {
        if (this->colsSize != rhs.rowsSize) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix result(this->rowsSize, rhs.colsSize);

        for (size_t i = 0; i < this->rowsSize; i++) {
            for (size_t j = 0; j < rhs.colsSize; j++) {
                for (size_t k = 0; k < this->colsSize; k++) {
                    result.data[i][j] += this->data[i][k] * rhs.data[k][j];
                }
            }
        }

        return result;
    }

    // Правостороннее умножение
    Matrix Matrix::operator*(double val) const {
        Matrix result(this->rowsSize, this->colsSize);

        for (size_t i = 0; i < this->rowsSize; i++) {
            for (size_t j = 0; j < this->colsSize; j++) {
                result.data[i][j] = this->data[i][j] * val;
            }
        }

        return result;
    }

    // Экстра функции
    Matrix Matrix::transp() const {
        Matrix result(this->colsSize, this->rowsSize);

        for (size_t i = 0; i < this->rowsSize; i++) {
            for (size_t j = 0; j < this->colsSize; j++) {
                result.data[j][i] = this->data[i][j];
            }
        }

        return result;
    }

    double Matrix::det() const {
        if (this->rowsSize != this->colsSize) {
            throw DimensionMismatch(*this);
        }

        size_t size = this->rowsSize;

        if (size == 1) {
            return this->data[0][0];
        }

        if (size == 2) {
            return this->data[0][0] * this->data[1][1] - this->data[0][1] * this->data[1][0];
        }

        double deter = 0;
        int degree = 1;

        for (size_t i = 0; i < size; i++) {
            double new_val = this->minor(size, 0, i).det();

            deter += degree * this->data[0][i] * new_val;
            degree = -degree;
        }

        return deter;
    }

    Matrix Matrix::adj() const {
        if (this->rowsSize != this->colsSize) {
            throw DimensionMismatch(*this);
        }

        size_t size = this->rowsSize;

        Matrix result(size, size);

        if (size == 1) {
            result.data[0][0] = 1;
            return result;
        }

        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                double val = this->transp().minor(size, i, j).det();

                result.data[i][j] = (i + j) % 2 == 0 ? val : -1 * val;
            }
        }

        return result;
    }

    Matrix Matrix::inv() const {
        if (this->rowsSize != this->colsSize) {
            throw DimensionMismatch(*this);
        }

        double val = this->det();
        if (val == 0) {
            throw SingularMatrix();
        }

        val = 1/val;

        return this->adj() * val;
    }

    Matrix Matrix::minor(size_t size, size_t row, size_t col) const {
        Matrix result(size - 1, size - 1);

        int offsetRow = 0;

        for (size_t i = 0; i < size - 1; i++) {
            if (i == row) {
                offsetRow = 1;
            }

            int offsetCol = 0;

            for (size_t j = 0; j < size - 1; j++) {
                if (j == col) {
                    offsetCol = 1;
                }

                result.data[i][j] = this->data[i + offsetRow][j + offsetCol];
            }
        }

        return result;
    }

    // Дружественные функции
    Matrix operator*(double val, const Matrix& matrix) {
        return matrix * val;
    }

    std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        os << matrix.rowsSize << ' ' << matrix.colsSize << '\n';

        for (size_t i = 0; i < matrix.rowsSize; i++) {
            for (size_t j = 0; j < matrix.colsSize; j++) {
                os << std::setprecision(std::numeric_limits<double>::max_digits10) << matrix.data[i][j] << ' ';
            }
            os << '\n';
        }

        return os;
    }
}  // namespace prep
