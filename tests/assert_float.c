#include <stdlib.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>
#include <math.h>
#include <float.h>

int float_equal_display_error(float left, float right) {

  int left_int = *(int*)&left;
  if (left_int < 0) {
    left_int = 0x80000000 - left_int;
  }

  int right_int = *(int*)&right;
  if (right_int < 0) {
    right_int = 0x80000000 - right_int;
  }

  if (abs(left_int - right_int) <= 4) {
    return 1;
  }

  return 0;
}

void _assert_float_equal(
    const float a, const float b,
    const char* const file, const int line) {
  if (!float_equal_display_error(a, b)) {
    _fail(file, line);
  }
}
