#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/lispy.h"

void test_add(void **state) {
  assert_int_equal(add(3, 3), 6);
  assert_int_equal(add(3, -3), 0);
}

void test_sub(void **state) {
    assert_int_equal(sub(3, 3), 0);
    assert_int_equal(sub(3, -3), 6);
}

void test_mul(void **state) {
    assert_int_equal(mul(3, 3), 9);
    assert_int_equal(mul(3, -3), -9);
}

void test_mod(void **state) {
    assert_int_equal(mod(7, 4), 3);
    assert_int_equal(mod(8, 2), 0);
}

void test_min(void **state) {
    assert_int_equal(min(3, 3), 3);
    assert_int_equal(min(3, -3), -3);
}

void test_max(void **state) {
    assert_int_equal(max(3, 3), 3);
    assert_int_equal(max(3, -3), 3);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_add),
        cmocka_unit_test(test_sub),
        cmocka_unit_test(test_mul),
        cmocka_unit_test(test_mod),
        cmocka_unit_test(test_min),
        cmocka_unit_test(test_max),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
