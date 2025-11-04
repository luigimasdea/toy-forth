#include "parser.h"

#include <string.h>
#include <stdlib.h>

#include "list.h"
#include "tfobj.h"

#define WHITESPACE_DELIMITERS " \t\n"

char *normalize(char *str) {

}

tfobj *parse(const char *tok) {
  if (strcmp(tok, "0") == 0) {
    return create_int_object(0);
  } 

  int i = atoi(tok);
  if (i != 0) {
    return create_int_object(i);
  }

  if (strcmp(tok, "true") == 0) {
    return create_bool_object(1);
  }
  else if (strcmp(tok, "false") == 0) {
    return create_bool_object(0);
  }

  return NULL;
}

tfobj *tokenize(char *buf) {
  tfobj *tokens = create_list_object();

  const char *delimiters = " ";

  char *tok = strtok(buf, delimiters);

  while (tok != NULL) {
    list_push_back(tokens, parse(tok));
    tok = strtok(NULL, delimiters);
  }

  return tokens;
}
