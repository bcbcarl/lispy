#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/lispy.h"
#include "assert_float.h"

void test_add(void **state) {
  lval* x = NULL;
  lval* y = NULL;

  x = lval_num(3.);
  y = lval_num(3.);

  assert_float_equal(add(x, y)->num, 6.);
  lval_del(x);
  lval_del(y);

  x = lval_num(3.);
  y = lval_num(-3.);
  assert_float_equal(add(x, y)->num, 0.);
  lval_del(x);
  lval_del(y);
}

void test_sub(void **state) {
  lval* x = NULL;
  lval* y = NULL;

  x = lval_num(3.);
  y = lval_num(3.);
  assert_float_equal(sub(x, y)->num, 0.);
  lval_del(x);
  lval_del(y);

  x = lval_num(3.);
  y = lval_num(-3.);
  assert_float_equal(sub(x, y)->num, 6.);
  lval_del(x);
  lval_del(y);
}

void test_mul(void **state) {
  lval* x = NULL;
  lval* y = NULL;

  x = lval_num(3.);
  y = lval_num(3.);
  assert_float_equal(mul(x, y)->num, 9.);
  lval_del(x);
  lval_del(y);

  x = lval_num(3.);
  y = lval_num(-3.);
  assert_float_equal(mul(x, y)->num, -9.);
  lval_del(x);
  lval_del(y);
}

void test_division(void **state) {
  lval* x = NULL;
  lval* y = NULL;

  x = lval_num(10.);
  y = lval_num(0.);
  assert_string_equal(division(x, y)->err, "Division by zero.");
  lval_del(x);
  lval_del(y);

  x = lval_num(10.);
  y = lval_num(2.);
  assert_float_equal(division(x, y)->num, 5.);
  lval_del(x);
  lval_del(y);
}

void test_mod(void **state) {
  lval* x = NULL;
  lval* y = NULL;

  x = lval_num(7.);
  y = lval_num(4.);
  assert_float_equal(mod(x, y)->num, 3.);
  lval_del(x);
  lval_del(y);

  x = lval_num(8.);
  y = lval_num(2.);
  assert_float_equal(mod(x, y)->num, 0.);
  lval_del(x);
  lval_del(y);
}

void test_expt(void **state) {
  lval* x = NULL;
  lval* y = NULL;

  x = lval_num(4.);
  y = lval_num(2.);
  assert_float_equal(expt(x, y)->num, 16.);
  lval_del(x);
  lval_del(y);
}

void test_min(void **state) {
  lval* x = NULL;
  lval* y = NULL;

  x = lval_num(3.);
  y = lval_num(3.);
  assert_float_equal(min(x, y)->num, 3.);
  lval_del(x);
  lval_del(y);

  x = lval_num(3.);
  y = lval_num(-3.);
  assert_float_equal(min(x, y)->num, -3.);
  lval_del(x);
  lval_del(y);
}

void test_max(void **state) {
  lval* x = NULL;
  lval* y = NULL;

  x = lval_num(3.);
  y = lval_num(3.);
  assert_float_equal(max(x, y)->num, 3.);
  lval_del(x);
  lval_del(y);

  x = lval_num(3.);
  y = lval_num(-3.);
  assert_float_equal(max(x, y)->num, 3.);
  lval_del(x);
  lval_del(y);
}

int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_add),
    cmocka_unit_test(test_sub),
    cmocka_unit_test(test_mul),
    cmocka_unit_test(test_division),
    cmocka_unit_test(test_mod),
    cmocka_unit_test(test_expt),
    cmocka_unit_test(test_min),
    cmocka_unit_test(test_max),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
