#include <stdio.h>
#include <stdlib.h>

#include "mpc.h"

/* If we are compiling on Windows compile these functions */
#ifdef _WIN32

#include <string.h>

static char buffer[2048];

/* Fake readline function */
char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
}

/* Fake add_history function */
char* add_history(char* unused) {}

/* Otherwise include the editline headers */
#else

#include <readline/readline.h>
#include <readline/history.h>

#endif

int main() {

  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Lispy = mpc_new("lispy");

  mpca_lang(MPCA_LANG_DEFAULT,
    "                                                               "
    " number  : /-?[0-9]+(\\.[0-9]*)?/;                             "
    " operator : '+' | '-' | '*' | '/' | '%'                        "
    "            | \"add\" | \"sub\" | \"mul\" | \"div\";           "
    " expr     : <number> | <decimal> | '(' <operator> <expr>+ ')'; "
    " lispy    : /^/ <operator> <expr>+ /$/;                        ",
    Number, Operator, Expr, Lispy, NULL);

  puts("Lispy Version 0.0.0.0.2");
  puts("Press Ctrl+c to Exit\n");

  while (1) {

    char* input = readline("lispy> ");
    add_history(input);

    /* Attempt to Parse the user Input */
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      /* On Success Print the AST */
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      /* Otherwise Print the Error */
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    free(input);
  };

  /* Undefine and delete our parsers */
  mpc_cleanup(4, Number, Operator, Expr, Lispy);

  return 0;
}
