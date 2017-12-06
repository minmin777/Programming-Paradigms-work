/* check_mat.c

   Name:Yasmine Ayad

   Unit tests for the matrix functions.

   These tests use the `check` library, available here:
   https://libcheck.github.io/check/

   Documentation for the functions is here:
   https://libcheck.github.io/check/doc/doxygen/html/check_8h.html

   When linking this file into an executable (with `gcc -o`), make sure
   to pass in `-lcheck` to link to the "check" library. For example,
   to compile this with the matrix.c file you would do

     gcc -c matrix.c
     gcc -c check_mat.c
     gcc -o check_mat matrix.o check_mat.o -lcheck

   or, if you wanted to compile and link at the same time,

     gcc -o check_mat matrix.c check_mat.c -lcheck
*/

#include <stdbool.h>
#include <check.h>

#include "matrix.h"

START_TEST(test_eq_matrix)
{
  int mat1[2][3] = { {1, 2, 3}, {4, 5, 6} };
  int mat2[2][3] = { {7, 8, 9}, {10, 11, 12} };
  ck_assert(eq_matrix(2, 3, mat1, mat1));
  ck_assert(eq_matrix(2, 3, mat2, mat2));
  ck_assert(!eq_matrix(2, 3, mat1, mat2));
}
END_TEST

// You can have multiple tests in a file.
START_TEST(test_identity_mat)
{
  int ident[2][2] = { {1, 0}, {0, 1} };
  int result[2][2];
  identity_mat(2, result);
  ck_assert(eq_matrix(2, 2, ident, result));

}
END_TEST

START_TEST(test_scalar_mult)
{
  int ident[3][2] = { {18, 24}, {12, 48}, {54, 42} };
  int numbers[3][2] = { { 3, 4 }, { 2, 8 }, { 9, 7 } };
  int result[3][2];
  scalar_mult(6, 3, 2, numbers, result);
  //print_matrix(3, 2, result);
  ck_assert(eq_matrix(3, 2, ident, result));

}
END_TEST

START_TEST(test_matrix_mult)
{
  int ident[2][2] = { {7, 10}, {15, 22} };
  int mat1[2][2] = { {1, 2}, {3, 4} };
  int mat2[2][2] = { {1, 2}, {3, 4} };
  int result[2][2];
  matrix_mult(2, 2, mat1, 2, mat2, result);
  ck_assert(eq_matrix(2, 2, ident, result));

}
END_TEST


START_TEST(test_matrix_pow)
{
  int ident[2][2] = { {7, 10}, {15, 22} };
  int mat1[2][2] = { {1, 2}, {3, 4} };
  int result[2][2];
  matrix_pow(2, mat1, 2, result);
  ck_assert(eq_matrix(2, 2, ident, result));

}
END_TEST

START_TEST(test_matrix_pow_rec)
{
  int ident[2][2] = { {7, 10}, {15, 22} };
  int mat1[2][2] = { {1, 2}, {3, 4} };
  int result[2][2];
  matrix_pow_rec(2, mat1, 2, result);
  ck_assert(eq_matrix(2, 2, ident, result));

}
END_TEST

START_TEST(test_matrix_pow_two)
{
  int ident[2][2] = { {37, 54}, {81, 118} };
  int mat1[2][2] = { {1, 2}, {3, 4} };
  int result[2][2];
  matrix_pow(2, mat1, 3, result);
  ck_assert(eq_matrix(2, 2, ident, result));

}
END_TEST


START_TEST(test_matrix_pow_rec_two)
{
  int ident[2][2] = { {37, 54}, {81, 118} };
  int mat1[2][2] = { {1, 2}, {3, 4} };
  int result[2][2];
  matrix_pow_rec(2, mat1, 3, result);
  ck_assert(eq_matrix(2, 2, ident, result));

}
END_TEST



// the main() function for unit testing is fairly prescribed.
// Just copy & paste, but make sure to update the test names!
int main()
{
  // `check` allows for multiple test suites, but we'll always
  // just have one, called "main"
  Suite* s = suite_create("main");

  // Inside a suite are potentially many `TCase`s.
  TCase* tc = tcase_create("matrix");

  // Each TCase can have many individual testing functions.
  tcase_add_test(tc, test_eq_matrix);
  tcase_add_test(tc, test_identity_mat);
  tcase_add_test(tc, test_scalar_mult);
  tcase_add_test(tc, test_matrix_mult);
  tcase_add_test(tc, test_matrix_pow);
  tcase_add_test(tc, test_matrix_pow_rec);
  tcase_add_test(tc, test_matrix_pow_two);
  tcase_add_test(tc, test_matrix_pow_rec_two);

  // Having set up the TCase, add it to the suite:
  suite_add_tcase(s, tc);

  // To run the tests, we need a runner:
  SRunner* sr = srunner_create(s);

  // You can see options for running only some of the tests at
  // the documentation link above. The CK_NORMAL indicates to
  // print only failing tests.
  srunner_run_all(sr, CK_NORMAL);

  // after running, we can retrieve the number of failures
  int number_failed = srunner_ntests_failed(sr);

  // We're done now with the testsuite, so dispose of it properly
  srunner_free(sr);

  // conveniently, number_failed makes a nice exit code.
  // a non-zero answer means a failed test!
  return number_failed;
}
				    
