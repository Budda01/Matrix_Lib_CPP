#include "s21_matrix_oop.h"

void S21Matrix::create_matrix(int rows, int cols) {
  if (is_correct_matrix(rows, cols)) {
    rows_ = rows;
    cols_ = cols;
    matrix_ = new double* [rows_] {};
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_]{};
    }
  } else
    throw std::invalid_argument("Число строк и столбцов должно превышать 0");
}
void S21Matrix::del_matrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  reset_matrix();
}
void S21Matrix::reset_matrix() {
  cols_ = 0;
  rows_ = 0;
  matrix_ = nullptr;
}
void S21Matrix::copy_matrix(const S21Matrix& other) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) matrix_[i][j] = other.matrix_[i][j];
  }
}
bool S21Matrix::is_correct_matrix(int rows, int cols) {
  return (rows > 0 && cols > 0) ? true : false;
}
bool S21Matrix::is_eq_size(const S21Matrix& other) const {
  return (rows_ == other.rows_ && cols_ == other.cols_) ? true : false;
}