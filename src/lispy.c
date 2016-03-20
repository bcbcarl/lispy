#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mpc.h"
#include "lispy.h"

lval lval_num(double x) {
  lval v;
  v.type = LVAL_NUM;
  v.num = x;
  return v;
}

lval lval_err(int x) {
  lval v;
  v.type = LVAL_ERR;
  v.err = x;
  return v;
}

void lval_print(lval v) {
  switch (v.type) {
  case LVAL_NUM:
    printf("%.2f", v.num);
    break;
  case LVAL_ERR:
    if (v.err == LERR_DIV_ZERO) {
      printf("Error: Division by zero.");
    }
    if (v.err == LERR_BAD_OP) {
      printf("Error: Invalid operator.");
    }
    if (v.err == LERR_BAD_NUM) {
      printf("Error: Invalid number.");
    }
    break;
  default:
    printf("Error: Unknown type.");
    break;
  }
}

void lval_println(lval v) {
  lval_print(v);
  putchar('\n');
}

lval add(lval x, lval y) {
  return lval_num(x.num + y.num);
}

lval sub(lval x, lval y) {
  return lval_num(x.num - y.num);
}

lval mul(lval x, lval y) {
  return lval_num(x.num * y.num);
}

lval division(lval x, lval y) {
  if (y.num == 0) {
    return lval_err(LERR_DIV_ZERO);
  }

  div_t d = div(x.num, y.num);
  return lval_num(d.quot);
}

lval mod(lval x, lval y) {
  return lval_num(fmod(x.num, y.num));
}

lval expt(lval x, lval y) {
  return lval_num(pow(x.num, y.num));
}

lval min(lval x, lval y) {
  return (x.num < y.num) ?
    lval_num(x.num) :
    lval_num(y.num);
}

lval max(lval x, lval y) {
  return (x.num > y.num) ?
    lval_num(x.num) :
    lval_num(y.num);
}

lval eval_op(char* op, lval x, lval y) {

  if (x.type == LVAL_ERR) { return x; }
  if (y.type == LVAL_ERR) { return y; }

  if (strcmp(op, "+") == 0) { return add(x, y); }
  if (strcmp(op, "-") == 0) { return sub(x, y); }
  if (strcmp(op, "*") == 0) { return mul(x, y); }
  if (strcmp(op, "/") == 0) { return division(x, y); }
  if (strcmp(op, "%") == 0) { return mod(x, y); }
  if (strcmp(op, "^") == 0) { return expt(x, y); }
  if (strcmp(op, "add") == 0) { return add(x, y); }
  if (strcmp(op, "sub") == 0) { return sub(x, y); }
  if (strcmp(op, "mul") == 0) { return mul(x, y); }
  if (strcmp(op, "div") == 0) { return division(x, y); }
  if (strcmp(op, "mod") == 0) { return mod(x, y); }
  if (strcmp(op, "pow") == 0) { return expt(x, y); }
  if (strcmp(op, "min") == 0) { return min(x, y); }
  if (strcmp(op, "max") == 0) { return max(x, y); }

  return lval_err(LERR_BAD_OP);
}

lval eval(mpc_ast_t* t) {

  if (strstr(t->tag, "number")) {
    errno = 0;
    double x = strtod(t->contents, NULL);
    return errno != ERANGE ? lval_num(x) : lval_err(LERR_BAD_NUM);
  }

  char* op = t->children[1]->contents;
  lval x = eval(t->children[2]);

  if ((strcmp(op, "-") == 0) && !strstr(t->children[3]->tag, "expr")) {
    return lval_num(-x.num);
  };

  for (int i = 3; strstr(t->children[i]->tag, "expr"); ++i) {
    x = eval_op(op, x, eval(t->children[i]));
  }

  return x;
}
