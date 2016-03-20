#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/lispy.h"

void test_add(void **state) {
  lval x, y;

  x = lval_num(3);
  y = lval_num(3);
  assert_int_equal(add(x, y).num, 6);

  x = lval_num(3);
  y = lval_num(-3);
  assert_int_equal(add(x, y).num, 0);
}

void test_sub(void **state) {
  lval x, y;

  x = lval_num(3);
  y = lval_num(3);
  assert_int_equal(sub(x, y).num, 0);

  x = lval_num(3);
  y = lval_num(-3);
  assert_int_equal(sub(x, y).num, 6);
}

void test_mul(void **state) {
  lval x, y;

  x = lval_num(3);
  y = lval_num(3);
  assert_int_equal(mul(x, y).num, 9);

  x = lval_num(3);
  y = lval_num(-3);
  assert_int_equal(mul(x, y).num, -9);
}

void test_division(void **state) {
  lval x, y;

  x = lval_num(10);
  y = lval_num(0);
  assert_int_equal(division(x, y).err, LERR_DIV_ZERO);

  x = lval_num(10);
  y = lval_num(2);
  assert_int_equal(division(x, y).num, 5);
}

void test_mod(void **state) {
  lval x, y;

  x = lval_num(7);
  y = lval_num(4);
  assert_int_equal(mod(x, y).num, 3);

  x = lval_num(8);
  y = lval_num(2);
  assert_int_equal(mod(x, y).num, 0);
}

void test_expt(void **state) {
  lval x, y;

  x = lval_num(4);
  y = lval_num(2);
  assert_int_equal(expt(x, y).num, 16);
}

void test_min(void **state) {
  lval x, y;

  x = lval_num(3);
  y = lval_num(3);
  assert_int_equal(min(x, y).num, 3);

  x = lval_num(3);
  y = lval_num(-3);
  assert_int_equal(min(x, y).num, -3);
}

void test_max(void **state) {
  lval x, y;

  x = lval_num(3);
  y = lval_num(3);
  assert_int_equal(max(x, y).num, 3);

  x = lval_num(3);
  y = lval_num(-3);
  assert_int_equal(max(x, y).num, 3);
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
