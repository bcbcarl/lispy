#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mpc.h"

long add(long x, long y) {
  return x + y;
}

long sub(long x, long y) {
  return x - y;
}

long mul(long x, long y) {
  return x * y;
}

long mod(long x, long y) {
  return x % y;
}

long min(long x, long y) {
  return (x < y) ? x : y;
}

long max(long x, long y) {
  return (x > y) ? x : y;
}

long eval_op(char* op, long x, long y) {
  if (strcmp(op, "+") == 0) { return add(x, y); }
  if (strcmp(op, "-") == 0) { return sub(x, y); }
  if (strcmp(op, "*") == 0) { return mul(x, y); }
  if (strcmp(op, "/") == 0) { return x / y; }
  if (strcmp(op, "%") == 0) { return mod(x, y); }
  if (strcmp(op, "^") == 0) { return pow(x, y); }
  if (strcmp(op, "add") == 0) { return add(x, y); }
  if (strcmp(op, "sub") == 0) { return sub(x, y); }
  if (strcmp(op, "mul") == 0) { return mul(x, y); }
  if (strcmp(op, "div") == 0) { return x / y; }
  if (strcmp(op, "mod") == 0) { return mod(x, y); }
  if (strcmp(op, "pow") == 0) { return pow(x, y); }
  if (strcmp(op, "min") == 0) { return min(x, y); }
  if (strcmp(op, "max") == 0) { return max(x, y); }
  return 0;
}

long eval(mpc_ast_t* t) {

  if (strstr(t->tag, "number")) {
    return atoi(t->contents);
  }

  char* op = t->children[1]->contents;
  long x = eval(t->children[2]);

  if ((strcmp(op, "-") == 0) && !strstr(t->children[3]->tag, "expr")) {
      return -x;
  };

  for (int i = 3; strstr(t->children[i]->tag, "expr"); ++i) {
    x = eval_op(op, x, eval(t->children[i]));
  }

  return x;
}
