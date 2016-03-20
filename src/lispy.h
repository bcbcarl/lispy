#ifndef LISPY_H_
#define LISPY_H_

#include "mpc.h"

long add(long, long);
long sub(long, long);
long mul(long, long);
long mod(long, long);
long min(long, long);
long max(long, long);
long eval_op(char*, long, long);
long eval(mpc_ast_t*);

#endif
