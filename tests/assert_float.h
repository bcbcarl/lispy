#ifndef ASSERT_FLOAT_H_
#define ASSERT_FLOAT_H_

void _assert_float_equal(const float, const float, const char* const, const int);

#define assert_float_equal(a, b) \
  _assert_int_equal(cast_to_largest_integral_type(a), \
                    cast_to_largest_integral_type(b), \
__FILE__, __LINE__)

#endif
