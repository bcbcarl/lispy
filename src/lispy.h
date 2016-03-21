#ifndef LISPY_H_
#define LISPY_H_

#include "mpc.h"

typedef struct lval {
  int type;
  double num;
  char* err;
  char* sym;
  int count;
  struct lval** cell;
} lval;

enum { LVAL_NUM, LVAL_ERR, LVAL_SYM, LVAL_SEXPR };
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };


lval* lval_num(double);
lval* lval_err(char*);
lval* lval_sym(char*);
lval* lval_sexpr(void);
void lval_del(lval*);
lval* lval_read_num(mpc_ast_t*);
lval* lval_read(mpc_ast_t*);
lval* lval_add(lval*, lval*);
void lval_expr_print(lval*, char, char);
void lval_print(lval*);
void lval_println(lval*);
lval* add(lval*, lval*);
lval* sub(lval*, lval*);
lval* mul(lval*, lval*);
lval* division(lval*, lval*);
lval* mod(lval*, lval*);
lval* expt(lval*, lval*);
lval* min(lval*, lval*);
lval* max(lval*, lval*);
/*
lval eval_op(char*, lval, lval);
lval eval(mpc_ast_t*);
*/

#endif
