#include "s21_matrix_oop.h"

//конструкторы и деструкторы
S21Matrix::S21Matrix() : rows_(2), cols_(2) { create_matrix(rows_, cols_); }
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  create_matrix(rows_, cols_);
}
S21Matrix::S21Matrix(const S21Matrix &other) {
  create_matrix(other.rows_, other.cols_);
  copy_matrix(other);
}
S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.reset_matrix();
}
S21Matrix::~S21Matrix() { del_matrix(); }
// аксессоры и мутаторы
int S21Matrix::GetCols() { return cols_; }
int S21Matrix::GetRows() { return rows_; }
void S21Matrix::SetCols(int inp_cols) {
  if (inp_cols <= 0) {
    throw std::invalid_argument("Неверный аргумент");
  }
  S21Matrix res(rows_, inp_cols);
  int cols_value = 0;
  int check = 0;
  if (inp_cols > cols_) {
    cols_value = cols_;
    check = 1;
  } else
    cols_value = inp_cols;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_value; j++) {
      res.matrix_[i][j] = matrix_[i][j];
    }
  }
  if (check) {
    for (int i = 0; i < rows_; i++) {
      for (int j = cols_; j < inp_cols; j++) {
        res.matrix_[i][j] = 0;
      }
    }
  }
  *this = res;
}
void S21Matrix::SetRows(int inp_rows) {
  if (inp_rows <= 0) {
    throw std::invalid_argument("Неверный аргумент");
  }
  S21Matrix res(inp_rows, cols_);
  int rows_value = 0;
  int check = 0;
  if (inp_rows > rows_) {
    rows_value = rows_;
    check = 1;
  } else
    rows_value = inp_rows;
  for (int i = 0; i < rows_value; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[i][j] = matrix_[i][j];
    }
  }
  if (check) {
    for (int i = rows_; i < inp_rows; i++) {
      for (int j = 0; j < cols_; j++) {
        res.matrix_[i][j] = 0;
      }
    }
  }
  *this = res;
}
//перегрузка операторов
double &S21Matrix::operator()(int i, int j) {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::out_of_range("Вне матрицы");
  }
  return matrix_[i][j];
}
S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}
void S21Matrix::operator+=(const S21Matrix &other) { SumMatrix(other); }
S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}
void S21Matrix::operator-=(const S21Matrix &other) { SubMatrix(other); }
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  del_matrix();
  create_matrix(other.rows_, other.cols_);
  copy_matrix(other);
  return *this;
}
bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}
S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}
S21Matrix operator*(const double num, const S21Matrix &matrix) {
  S21Matrix res(matrix.rows_, matrix.cols_);
  res.copy_matrix(matrix);
  res.MulNumber(num);
  return res;
}
S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}
void S21Matrix::operator*=(const S21Matrix &other) { MulMatrix(other); }
void S21Matrix::operator*=(const double num) { MulNumber(num); }