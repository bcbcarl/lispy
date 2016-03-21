#include "mpc.h"
#include "lispy.h"

static const char* lispy_version = "0.0.0.0.5";

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

int main(void) {

  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Symbol = mpc_new("symbol");
  mpc_parser_t* Sexpr = mpc_new("sexpr");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Lispy = mpc_new("lispy");

  mpca_lang(MPCA_LANG_DEFAULT,
    "                                                             "
    " number : /-?[0-9]+(\\.[0-9]*)?/;                            "
    " symbol : '+' | '-' | '*' | '/' | '%' | '^'                  "
    "          | \"add\" | \"sub\" | \"mul\" | \"div\"            "
    "          | \"mod\" | \"pow\" | \"min\" | \"max\";           "
    " sexpr  : '(' <expr>* ')';                                   "
    " expr   : <number> | <symbol> | <sexpr>;                     "
    " lispy  : /^/ <expr>* /$/;                                   ",
    Number, Symbol, Sexpr, Expr, Lispy, NULL);

  printf("Lispy Version %s\n", lispy_version);
  puts("Press Ctrl+c to Exit\n");

  while (1) {

    char* input = readline("lispy> ");
    add_history(input);

    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      lval result = eval(r.output);
      lval_println(result);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    free(input);
  };

  mpc_cleanup(5, Number, Symbol, Sexpr, Expr, Lispy);

  return 0;
}
