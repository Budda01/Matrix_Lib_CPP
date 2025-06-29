#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool res = true;
  if (isEqSize(other)) {
    int check = 0;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) check++;
      }
    }
    if (check != 0) res = false;
  } else {
    res = false;
  }
  return res;
}
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (!isEqSize(other)) {
    throw std::invalid_argument("Различная размерность матриц");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (!isEqSize(other)) {
    throw std::invalid_argument("Различная размерность матриц");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}
void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Число столбцов первой матрицы не равно числу строк второй матрицы");
  }
  S21Matrix result_matr(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < rows_; j++) {
      double sum = 0;
      for (int r = 0; r < cols_; r++) {
        sum += (matrix_[i][r] * other.matrix_[r][j]);
      }
      result_matr.matrix_[i][j] = sum;
    }
  }
  *this = result_matr;
}
S21Matrix S21Matrix::Transpose() {
  S21Matrix result_matr(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result_matr.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result_matr;
}
double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Матрица не является квадратной");
  }
  double determ = 0;
  if (rows_ == 1)
    determ = matrix_[0][0];
  else
    determ = this->RecursDeterm(*this);
  return determ;
}
double S21Matrix::RecursDeterm(const S21Matrix& inp_matr) {
  double determ = 0;
  if (inp_matr.rows_ == 2) {
    determ = (inp_matr.matrix_[0][0] * inp_matr.matrix_[1][1]) -
             (inp_matr.matrix_[0][1] * inp_matr.matrix_[1][0]);
  } else {
    for (int j = 0; j < inp_matr.cols_; j++) {
      S21Matrix minor =
          inp_matr.CreateMinor(0, j, inp_matr.rows_, inp_matr.cols_);
      double sub_determ = RecursDeterm(minor);
      determ += pow(-1, j) * inp_matr.matrix_[0][j] * sub_determ;
    }
  }
  return determ;
}
S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Матрица не является квадратной");
  }
  S21Matrix res(rows_, cols_);
  if (rows_ == 1)
    res.matrix_[0][0] = matrix_[0][0];
  else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        S21Matrix minor = CreateMinor(i, j, rows_, cols_);
        double determ = minor.Determinant();
        res.matrix_[i][j] = (pow(-1, i + j) * determ);
      }
    }
  }
  return res;
}
S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::runtime_error("Матрица не является квадратной");
  }
  double det = Determinant();
  if (det == 0) {
    throw std::runtime_error("Определитель матрицы равен 0");
  }
  S21Matrix res(rows_, cols_);
  if (rows_ == 1)
    res.matrix_[0][0] = 1 / (matrix_[0][0]);
  else {
    S21Matrix complement = CalcComplements();
    S21Matrix transp_compl = complement.Transpose();
    transp_compl *= (1 / det);
    res = transp_compl;
  }
  return res;
}
S21Matrix S21Matrix::CreateMinor(int i, int j, int row, int col) const {
  S21Matrix minor(row - 1, col - 1);
  for (int r = 0; r < i; r++) {
    for (int c = 0; c < j; c++) {
      minor.matrix_[r][c] = matrix_[r][c];
    }
  }
  for (int r = i + 1; r < rows_; r++) {
    for (int c = j + 1; c < cols_; c++) {
      minor.matrix_[r - 1][c - 1] = matrix_[r][c];
    }
  }
  for (int r = i + 1; r < rows_; r++) {
    for (int c = 0; c < j; c++) {
      minor.matrix_[r - 1][c] = matrix_[r][c];
    }
  }
  for (int r = 0; r < i; r++) {
    for (int c = j + 1; c < cols_; c++) {
      minor.matrix_[r][c - 1] = matrix_[r][c];
    }
  }
  return minor;
}
