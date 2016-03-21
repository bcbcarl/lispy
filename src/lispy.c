#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mpc.h"
#include "lispy.h"

lval* lval_num(double x) {
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_NUM;
  v->num = x;
  return v;
}

lval* lval_err(char* m) {
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_ERR;
  v->err = malloc(strlen(m) + 1);
  strcpy(v->err, m);
  return v;
}

lval* lval_sym(char* s) {
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_SYM;
  v->sym = malloc(strlen(s) + 1);
  strcpy(v->sym, s);
  return v;
}

lval* lval_sexpr(void) {
  lval* v = malloc(sizeof(lval));
  v->type = LVAL_SEXPR;
  v->count = 0;
  v->cell = NULL;
  return v;
}

void lval_del(lval* v) {
  switch (v->type) {
  case LVAL_NUM:
    break;
  case LVAL_ERR:
    free(v->err);
    break;
  case LVAL_SYM:
    free(v->sym);
    break;
  case LVAL_SEXPR:
    for (int i = 0; i < v->count; ++i) {
      free(v->cell[i]);
    }
    free(v->cell);
    break;
  }
  free(v);
}

lval* lval_read_num(mpc_ast_t* t) {
    errno = 0;
    double x = strtod(t->contents, NULL);
    return errno != ERANGE ?
      lval_num(x) :
      lval_err("invalid number.");
}

lval* lval_read(mpc_ast_t* t) {

  if (strstr(t->tag, "number")) {
    return lval_read_num(t);
  }

  if (strstr(t->tag, "symbol")) {
    return lval_sym(t->contents);
  }

  lval* x = NULL;
  if (strcmp(t->tag, ">") == 0) { x = lval_sexpr(); }
  if (strcmp(t->tag, "sexpr") == 0) { x = lval_sexpr(); }

  for (int i = 0; i < t->children_num; ++i) {
    if (strcmp(t->children[i]->contents, "(") == 0) { continue; }
    if (strcmp(t->children[i]->contents, ")") == 0) { continue; }
    if (strcmp(t->children[i]->tag, "regex") == 0) { continue; }
    x = lval_add(x, lval_read(t->children[i]));
  }

  return x;
}

lval* lval_add(lval* v, lval* x) {
  v->count++;
  v->cell = realloc(v->cell, sizeof(lval*) * v->count);
  v->cell[v->count-1] = x;
  return v;
}

void lval_expr_print(lval* v, char open, char close) {

  putchar(open);

  for (int i = 0; i < v->count; ++i) {
    lval_print(v->cell[i]);

    if (i != (v->count-1)) {
      putchar(' ');
    }
  }

  putchar(close);
}

void lval_print(lval* v) {
  switch (v->type) {
  case LVAL_NUM:
    printf("%.2f", v->num);
    break;
  case LVAL_ERR:
    printf("Error: %s", v->err);
    break;
  case LVAL_SYM:
    printf("%s", v->sym);
    break;
  case LVAL_SEXPR:
    lval_expr_print(v, '(', ')');
    break;
  default:
    printf("Error: Unknown type.");
    break;
  }
}

void lval_println(lval* v) {
  lval_print(v);
  putchar('\n');
}

lval* add(lval* x, lval* y) {
  return lval_num(x->num + y->num);
}

lval* sub(lval* x, lval* y) {
  return lval_num(x->num - y->num);
}

lval* mul(lval* x, lval* y) {
  return lval_num(x->num * y->num);
}

lval* division(lval* x, lval* y) {
  if (y->num == 0) {
    return lval_err("Division by zero.");
  }

  div_t d = div(x->num, y->num);
  return lval_num(d.quot);
}

lval* mod(lval* x, lval* y) {
  return lval_num(fmod(x->num, y->num));
}

lval* expt(lval* x, lval* y) {
  return lval_num(pow(x->num, y->num));
}

lval* min(lval* x, lval* y) {
  return lval_num(fmin(x->num, y->num));
}

lval* max(lval* x, lval* y) {
  return lval_num(fmax(x->num, y->num));
}

/*
lval* eval_op(char* op, lval x, lval y) {

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

  return lval_err("Invalid operator.");
}
*/
