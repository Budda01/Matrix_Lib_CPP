FLAGS  = g++ -std=c++17 -Wall -Wextra -Werror
LIBS = -lgtest -pthread -lstdc++ -lm
GCOV = --coverage

all:

s21_matrix_oop.a:
	@$(FLAGS) -c s21_overload_op.cc  -o s21_overload_op.o
	@$(FLAGS) -c s21_private_func.cc -o s21_private_func.o
	@$(FLAGS) -c s21_public_func.cc -o s21_public_func.o
	@ar rcs s21_matrix_oop.a s21_overload_op.o s21_private_func.o s21_public_func.o

tests: clean
	$(CC) s21_overload_op.cc s21_private_func.cc s21_public_func.cc tests.cc -o matrix_test $(LIBS)
	./matrix_test
gcov_report:
	@$(CC) $(GCOV) -c s21_overload_op.cc
	@$(CC) $(GCOV) -c s21_private_func.cc
	@$(CC) $(GCOV) -c s21_public_func.cc
	$(CC) -c tests.cc $(LIBS)
	$(CC) --coverage -o matrix_test tests.o s21_overload_op.o s21_private_func.o s21_public_func.o $(LIBS)
	./matrix_test
	lcov -t "tests" -o s21_matrix_oop.info -c -d .
	genhtml -o report s21_matrix_oop.info
	open ./report/index.html
	make clean_test
style:
	clang-format -style=Google -n *.cc *.h
clean:
	@rm -rf report ./*.o ./*.a *.info *.gcda *.gcno matrix_test
clean_test:
	@rm -rf *.info *.gcda *.gcno 