#include <cmath>
#include <iostream>

class S21Matrix {
 public:
  const double EPS = 0.0000001;
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();
  double recurs_determ(const S21Matrix &inp_matr);
  S21Matrix create_minor(int i, int j, int row, int col) const;

  int GetCols();
  int GetRows();
  void SetCols(int inp_cols);
  void SetRows(int inp_cols);

  double &operator()(int i, int j);
  S21Matrix operator+(const S21Matrix &other) const;
  void operator+=(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix operator*(double num) const;
  friend S21Matrix operator*(const double num, const S21Matrix &matrix);
  void operator*=(const S21Matrix &other);
  void operator*=(const double num);
  S21Matrix operator-(const S21Matrix &other) const;
  void operator-=(const S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other);
  bool operator==(const S21Matrix &other) const;

 private:
  int rows_, cols_;
  double **matrix_;
  void create_matrix(int rows, int cols);
  void del_matrix();
  void reset_matrix();
  bool is_correct_matrix(int rows, int cols);
  bool is_eq_size(const S21Matrix &other) const;
  void copy_matrix(const S21Matrix &other);
};