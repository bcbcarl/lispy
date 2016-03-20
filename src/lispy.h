#ifndef LISPY_H_
#define LISPY_H_

#include "mpc.h"

typedef struct {
  int type;
  double num;
  int err;
} lval;

enum { LVAL_NUM, LVAL_ERR };
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };


lval lval_num(double);
lval lval_err(int);
void lval_print(lval);
void lval_println(lval);
lval add(lval, lval);
lval sub(lval, lval);
lval mul(lval, lval);
lval division(lval, lval);
lval mod(lval, lval);
lval expt(lval, lval);
lval min(lval, lval);
lval max(lval, lval);
lval eval_op(char*, lval, lval);
lval eval(mpc_ast_t*);

#endif
