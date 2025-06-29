#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

TEST(S21MatrixTestConstructor, basic_constr) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_EQ(matrix.GetCols(), 2);
}
TEST(S21MatrixTestConstructor, param_constr_1) {
  S21Matrix matrix(2, 3);
  ASSERT_EQ(matrix.GetRows(), 2);
  ASSERT_EQ(matrix.GetCols(), 3);
}
TEST(S21MatrixTestConstructor, param_constr_2) {
  S21Matrix matrix(5, 5);
  ASSERT_EQ(matrix.GetRows(), 5);
  ASSERT_EQ(matrix.GetCols(), 5);
}
TEST(S21MatrixTestConstructor, param_constr_3) {
  S21Matrix matrix(30, 4);
  ASSERT_EQ(matrix.GetRows(), 30);
  ASSERT_EQ(matrix.GetCols(), 4);
}
TEST(S21MatrixTestConstructor, param_constr_4) {
  S21Matrix matrix(1, 1);
  ASSERT_EQ(matrix.GetRows(), 1);
  ASSERT_EQ(matrix.GetCols(), 1);
}
TEST(S21MatrixTestConstructor, param_constr_5) {
  ASSERT_THROW(S21Matrix matrix(1, -1), std::invalid_argument);
}
TEST(S21MatrixTestCopyConstructor, param_constr_6) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;
  S21Matrix matrix2(matrix1);
  ASSERT_EQ(matrix1(0, 0), matrix2(0, 0));
  ASSERT_EQ(matrix1(1, 2), matrix2(1, 2));
}
TEST(S21MatrixTestMoveConstructor, param_constr_7) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;
  S21Matrix matrix2(std::move(matrix1));
  ASSERT_EQ(matrix2(0, 0), 1);
  ASSERT_EQ(matrix2(1, 2), 6);
  ASSERT_EQ(matrix1.GetRows(), 0);
}
TEST(S21MatrixTestMoveConstructor, param_constr_8) {
  S21Matrix matrix1(2, 3);
  ASSERT_THROW(matrix1.SetCols(-5), std::invalid_argument);
  matrix1.SetCols(10);
  ASSERT_EQ(matrix1.GetCols(), 10);
}
TEST(S21MatrixTestMoveConstructor, param_constr_9) {
  S21Matrix matrix1(2, 3);
  ASSERT_THROW(matrix1.SetRows(-5), std::invalid_argument);
  matrix1.SetRows(10);
  ASSERT_EQ(matrix1.GetRows(), 10);
}
TEST(S21MatrixTestMoveConstructor, param_constr_10) {
  S21Matrix matrix1(2, 3);
  ASSERT_THROW(matrix1(3, 2), std::out_of_range);
}
TEST(S21MatrixTestOperations, EqMatrix_1) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1(0, 0) = 34;
  matrix1(0, 1) = 123;
  matrix1(1, 0) = 2;
  matrix1(1, 1) = 4;

  matrix2(0, 0) = 34;
  matrix2(0, 1) = 123;
  matrix2(1, 0) = 2;
  matrix2(1, 1) = 4;
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));

  matrix2(1, 1) = 4.00123;
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));

  matrix2(1, 1) = 4.000000001;
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));

  matrix1.SetRows(4);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}
TEST(S21MatrixTestOperations, SumMatrix_1) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix exp_res3(2, 2);
  matrix1(0, 0) = 34;
  matrix1(0, 1) = 123;
  matrix1(1, 0) = 2;
  matrix1(1, 1) = 4;

  matrix2(0, 0) = 3;
  matrix2(0, 1) = 314;
  matrix2(1, 0) = 545.3123;
  matrix2(1, 1) = 1;

  exp_res3(0, 0) = 37;
  exp_res3(0, 1) = 437;
  exp_res3(1, 0) = 547.3123;
  exp_res3(1, 1) = 5;
  matrix1.SumMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(exp_res3));
}
TEST(S21MatrixTestOperations, SumMatrix_2) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  S21Matrix exp_res(3, 3);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 8;
  matrix1(2, 2) = 9;

  matrix2(0, 0) = 9;
  matrix2(0, 1) = 8;
  matrix2(0, 2) = 7;
  matrix2(1, 0) = 6;
  matrix2(1, 1) = 5;
  matrix2(1, 2) = 4;
  matrix2(2, 0) = 3;
  matrix2(2, 1) = 2;
  matrix2(2, 2) = 1;

  exp_res(0, 0) = 10;
  exp_res(0, 1) = 10;
  exp_res(0, 2) = 10;
  exp_res(1, 0) = 10;
  exp_res(1, 1) = 10;
  exp_res(1, 2) = 10;
  exp_res(2, 0) = 10;
  exp_res(2, 1) = 10;
  exp_res(2, 2) = 10;

  matrix1.SumMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(exp_res));
}
TEST(S21MatrixTestOperations, ErrSumMatrix) {
  S21Matrix matrix1(1, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix exp_res3(2, 2);
  matrix1(0, 0) = 34;
  matrix1(0, 1) = 123;

  matrix2(0, 0) = 3;
  matrix2(0, 1) = 314;
  matrix2(1, 0) = 545.3123;
  matrix2(1, 1) = 1;

  ASSERT_THROW(matrix1.SumMatrix(matrix2), std::invalid_argument);
}
TEST(S21MatrixTestOperations, SubMatrix_1) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  S21Matrix exp_res(3, 3);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 8;
  matrix1(2, 2) = 9;

  matrix2(0, 0) = 9;
  matrix2(0, 1) = 8;
  matrix2(0, 2) = 7;
  matrix2(1, 0) = 6;
  matrix2(1, 1) = 5;
  matrix2(1, 2) = 4;
  matrix2(2, 0) = 3;
  matrix2(2, 1) = 2;
  matrix2(2, 2) = 1;

  exp_res(0, 0) = -8;
  exp_res(0, 1) = -6;
  exp_res(0, 2) = -4;
  exp_res(1, 0) = -2;
  exp_res(1, 1) = 0;
  exp_res(1, 2) = 2;
  exp_res(2, 0) = 4;
  exp_res(2, 1) = 6;
  exp_res(2, 2) = 8;

  matrix1.SubMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(exp_res));
}
TEST(S21MatrixTestOperations, ErrSubMatrix) {
  S21Matrix matrix1(1, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix exp_res3(2, 2);
  matrix1(0, 0) = 34;
  matrix1(0, 1) = 123;

  matrix2(0, 0) = 3;
  matrix2(0, 1) = 314;
  matrix2(1, 0) = 545.3123;
  matrix2(1, 1) = 1;

  ASSERT_THROW(matrix1.SubMatrix(matrix2), std::invalid_argument);
}
TEST(S21MatrixTestOperations, MulNumber) {
  S21Matrix matrix(2, 3);
  S21Matrix exp_res(2, 3);
  matrix(0, 0) = 13;
  matrix(0, 1) = 2;
  matrix(0, 2) = 4.5;
  matrix(1, 0) = 12.12;
  matrix(1, 1) = 7.02;
  matrix(1, 2) = 1;

  exp_res(0, 0) = 130;
  exp_res(0, 1) = 20;
  exp_res(0, 2) = 45;
  exp_res(1, 0) = 121.2;
  exp_res(1, 1) = 70.2;
  exp_res(1, 2) = 10;
  double num = 10;
  matrix.MulNumber(num);
  EXPECT_TRUE(matrix.EqMatrix(exp_res));
}
TEST(S21MatrixTestOperations, MulNumber_2) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 21.00003;
  matrix(0, 1) = 2.1234567;
  matrix(0, 2) = 3.99;
  matrix(1, 0) = 4.12;
  matrix(1, 1) = 5.02;
  matrix(1, 2) = 6.011;
  double num = 2.1;
  S21Matrix res = num * matrix;

  ASSERT_DOUBLE_EQ(res(0, 0), 44.100063);
  ASSERT_DOUBLE_EQ(res(0, 1), 4.45925907);
  ASSERT_DOUBLE_EQ(res(0, 2), 8.379);
  ASSERT_DOUBLE_EQ(res(1, 0), 8.652);
  ASSERT_DOUBLE_EQ(res(1, 1), 10.542);
  ASSERT_DOUBLE_EQ(res(1, 2), 12.6231);

  ASSERT_DOUBLE_EQ(matrix(0, 0), 21.00003);
  ASSERT_DOUBLE_EQ(matrix(0, 1), 2.1234567);
  ASSERT_DOUBLE_EQ(matrix(0, 2), 3.99);
  ASSERT_DOUBLE_EQ(matrix(1, 0), 4.12);
  ASSERT_DOUBLE_EQ(matrix(1, 1), 5.02);
  ASSERT_DOUBLE_EQ(matrix(1, 2), 6.011);
}
TEST(S21MatrixTestOperations, MulNumber_3) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 11.00003;
  matrix(0, 1) = 2.1234567;
  matrix(0, 2) = 3.99;
  matrix(1, 0) = 4.12;
  matrix(1, 1) = 5.02;
  matrix(1, 2) = 6.011;
  double num = 2.1;
  matrix *= num;

  ASSERT_DOUBLE_EQ(matrix(0, 0), 23.100063);
  ASSERT_DOUBLE_EQ(matrix(0, 1), 4.45925907);
  ASSERT_DOUBLE_EQ(matrix(0, 2), 8.379);
  ASSERT_DOUBLE_EQ(matrix(1, 0), 8.652);
  ASSERT_DOUBLE_EQ(matrix(1, 1), 10.542);
  ASSERT_DOUBLE_EQ(matrix(1, 2), 12.6231);
}
TEST(S21MatrixTestOperations, MulMatrix_1) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 7.0;
  matrix2(0, 1) = 8.0;
  matrix2(1, 0) = 9.0;
  matrix2(1, 1) = 10.0;
  matrix2(2, 0) = 11.0;
  matrix2(2, 1) = 12.0;

  S21Matrix result(2, 2);
  result(0, 0) = 58.0;
  result(0, 1) = 64.0;
  result(1, 0) = 139.0;
  result(1, 1) = 154.0;

  matrix1.MulMatrix(matrix2);

  ASSERT_TRUE(matrix1.EqMatrix(result));
}
TEST(S21MatrixTestOperations, ErrMulMatrix) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;
  S21Matrix matrix2(2, 2);
  ASSERT_THROW(matrix1.MulMatrix(matrix2), std::invalid_argument);
}
TEST(S21MatrixTestOperations, Transpose_1) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 32.0;
  matrix(0, 2) = 3.04;
  matrix(1, 0) = 4.03331;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 16.01;

  S21Matrix transposedMatrix = matrix.Transpose();

  S21Matrix result(3, 2);
  result(0, 0) = 1.0;
  result(0, 1) = 4.03331;
  result(1, 0) = 32.0;
  result(1, 1) = 5.0;
  result(2, 0) = 3.04;
  result(2, 1) = 16.01;

  ASSERT_TRUE(transposedMatrix.EqMatrix(result));

  matrix.SetCols(2);
  S21Matrix transposedMatrix2 = matrix.Transpose();
  S21Matrix result2(2, 2);

  result2(0, 0) = 1.0;
  result2(0, 1) = 4.03331;
  result2(1, 0) = 32.0;
  result2(1, 1) = 5.0;

  ASSERT_TRUE(transposedMatrix2.EqMatrix(result2));
}
TEST(S21MatrixTestOperations, Determinant_1) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 12;
  matrix1(0, 1) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 11;

  ASSERT_DOUBLE_EQ(matrix1.Determinant(), 120);
}
TEST(S21MatrixTestOperations, Determinant_2) {
  S21Matrix matrix1(4, 4);
  int val = 1;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix1(i, j) = val++;
    }
  }
  matrix1(2, 2) = 1;
  matrix1(3, 3) = 1;
  ASSERT_DOUBLE_EQ(matrix1.Determinant(), -600);
}
TEST(S21MatrixTestOperations, Determinant_3) {
  S21Matrix matrix1(1, 1);
  matrix1(0, 0) = 12;

  ASSERT_DOUBLE_EQ(matrix1.Determinant(), 12);
}
TEST(S21MatrixTestOperations, ErrDeterminant) {
  S21Matrix matrix1(2, 1);
  matrix1(0, 0) = 12;
  ASSERT_THROW(matrix1.Determinant(), std::invalid_argument);
}
TEST(S21MatrixTestOperations, CalcComplements_1) {
  S21Matrix matrix1(2, 2);
  S21Matrix exp_res(2, 2);
  matrix1(0, 0) = 2.0;
  matrix1(0, 1) = 3.0;
  matrix1(1, 0) = 1.0;
  matrix1(1, 1) = 4.0;

  exp_res(0, 0) = 4.0;
  exp_res(0, 1) = -1.0;
  exp_res(1, 0) = -3.0;
  exp_res(1, 1) = 2.0;
  S21Matrix complementsMatrix = matrix1.CalcComplements();
  EXPECT_TRUE(complementsMatrix.EqMatrix(exp_res));
}
TEST(S21MatrixTestOperations, CalcComplements_2) {
  S21Matrix matrix1(3, 3);
  S21Matrix exp_res(3, 3);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 0;
  matrix1(1, 1) = 4;
  matrix1(1, 2) = 2;
  matrix1(2, 0) = 5;
  matrix1(2, 1) = 2;
  matrix1(2, 2) = 1;

  exp_res(0, 0) = 0;
  exp_res(0, 1) = 10;
  exp_res(0, 2) = -20;
  exp_res(1, 0) = 4;
  exp_res(1, 1) = -14;
  exp_res(1, 2) = 8;
  exp_res(2, 0) = -8;
  exp_res(2, 1) = -2;
  exp_res(2, 2) = 4;
  S21Matrix complementsMatrix = matrix1.CalcComplements();
  EXPECT_TRUE(complementsMatrix.EqMatrix(exp_res));
}
TEST(S21MatrixTestOperations, CalcComplements_3) {
  S21Matrix matrix1(2, 3);
  ASSERT_THROW(matrix1.CalcComplements(), std::invalid_argument);
}
TEST(S21MatrixTestOperations, CalcComplements_4) {
  S21Matrix matrix1(1, 1);
  matrix1(0, 0) = 32.4;
  S21Matrix complementsMatrix = matrix1.CalcComplements();
  ASSERT_DOUBLE_EQ(complementsMatrix(0, 0), 32.4);
}
TEST(S21MatrixTestOperations, InverseMatrix_1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 5;

  S21Matrix inverseMatrix = matrix.InverseMatrix();

  ASSERT_DOUBLE_EQ(inverseMatrix(0, 0), 0.2);
}
TEST(S21MatrixTestOperations, InverseMatrix_2) {
  S21Matrix matrix(2, 2);
  S21Matrix exp_res(2, 2);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;

  exp_res(0, 0) = -2.5;
  exp_res(0, 1) = 1.5;
  exp_res(1, 0) = 2.0;
  exp_res(1, 1) = -1.0;
  S21Matrix inverseMatrix = matrix.InverseMatrix();
  EXPECT_TRUE(inverseMatrix.EqMatrix(exp_res));
}
TEST(S21MatrixTestOperations, ErrInverseMatrix_1) {
  S21Matrix matrix(3, 2);
  ASSERT_THROW(matrix.InverseMatrix(), std::runtime_error);
}
TEST(S21MatrixTestOperations, ErrInverseMatrix_2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 6.0;
  ASSERT_THROW(matrix.InverseMatrix(), std::runtime_error);
}
TEST(S21MatrixTestOperations, Overload_1) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix exp_res(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;

  exp_res(0, 0) = 2;
  exp_res(0, 1) = 4;
  exp_res(1, 0) = 6;
  exp_res(1, 1) = 8;
  ASSERT_EQ(matrix1 + matrix2, exp_res);
  matrix1 += matrix2;
  ASSERT_EQ(matrix1, exp_res);
}
TEST(S21MatrixTestOperations, Overload_2) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 7.0;
  matrix2(0, 1) = 8.0;
  matrix2(1, 0) = 9.0;
  matrix2(1, 1) = 10.0;
  matrix2(2, 0) = 11.0;
  matrix2(2, 1) = 12.0;

  S21Matrix result(2, 2);
  result(0, 0) = 58.0;
  result(0, 1) = 64.0;
  result(1, 0) = 139.0;
  result(1, 1) = 154.0;

  ASSERT_EQ(matrix1 * matrix2, result);
  matrix1 *= matrix2;
  ASSERT_EQ(matrix1, result);
}
TEST(S21MatrixTestOperations, Overload_3) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix exp_res(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;

  exp_res(0, 0) = 0;
  exp_res(0, 1) = 0;
  exp_res(1, 0) = 0;
  exp_res(1, 1) = 0;
  ASSERT_EQ(matrix1 - matrix2, exp_res);
  matrix1 -= matrix2;
  ASSERT_EQ(matrix1, exp_res);
}
TEST(S21MatrixTestMultiplicationOperator, Overload_4) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;
  S21Matrix result = matrix * 2;
  ASSERT_EQ(result(0, 0), 2);
  ASSERT_EQ(result(0, 1), 4);
  ASSERT_EQ(result(0, 2), 6);
  ASSERT_EQ(result(1, 0), 8);
  ASSERT_EQ(result(1, 1), 10);
  ASSERT_EQ(result(1, 2), 12);
}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}