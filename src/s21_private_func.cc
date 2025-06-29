#include "s21_matrix_oop.h"

void S21Matrix::CreateMatrix(int rows, int cols) {
  if (!IsCorrectMatrix(rows, cols)) {
    throw std::invalid_argument("Число строк и столбцов должно превышать 0");
  }
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double* [rows_] {};
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]{};
  }
}
void S21Matrix::DelMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  ResetMatrix();
}
void S21Matrix::ResetMatrix() {
  cols_ = 0;
  rows_ = 0;
  matrix_ = nullptr;
}
void S21Matrix::CopyMatrix(const S21Matrix& other) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) matrix_[i][j] = other.matrix_[i][j];
  }
}
bool S21Matrix::IsCorrectMatrix(int rows, int cols) {
  return (rows > 0 && cols > 0) ? true : false;
}
bool S21Matrix::isEqSize(const S21Matrix& other) const {
  return (rows_ == other.rows_ && cols_ == other.cols_) ? true : false;
}