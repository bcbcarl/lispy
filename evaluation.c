#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mpc.h"

static const char* lispy_version = "0.0.0.0.3";

#ifdef _WIN32

#include <string.h>

static char buffer[2048];

char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
}

char* add_history(char* unused) {}

#else

#include <readline/readline.h>
#include <readline/history.h>

#endif

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

int main() {

  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Lispy = mpc_new("lispy");

  mpca_lang(MPCA_LANG_DEFAULT,
    "                                                               "
    " number  : /-?[0-9]+(\\.[0-9]*)?/;                             "
    " operator : '+' | '-' | '*' | '/' | '%' | '^'                  "
    "            | \"add\" | \"sub\" | \"mul\" | \"div\"            "
    "            | \"mod\" | \"pow\" | \"min\" | \"max\";           "
    " expr     : <number> | <decimal> | '(' <operator> <expr>+ ')'; "
    " lispy    : /^/ <operator> <expr>+ /$/;                        ",
    Number, Operator, Expr, Lispy, NULL);

  printf("Lispy Version %s\n", lispy_version);
  puts("Press Ctrl+c to Exit\n");

  while (1) {

    char* input = readline("lispy> ");
    add_history(input);

    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      long result = eval(r.output);
      printf("%li\n", result);

      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    free(input);
  };

  mpc_cleanup(4, Number, Operator, Expr, Lispy);

  return 0;
}
