#include "../include/parser.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "../include/symbol.h"

void skip_spaces(tfparser *parser) {
  while (isspace(parser->p[0])) {
    parser->p++;
  }
}

tfobj *parse_int(tfparser *parser) {
  int num;
  char token[MAX_INT_LEN];

  /* Saving the start of the number */
  char *start = parser->p;

  /* If negative int, skip the '-' sign */
  if (parser->p[0] == '-') {
    parser->p++;
  }

  /* Now skip to the end of the token */
  while (!isspace(parser->p[0]) && parser->p[0] != '\0') {
    if (!isdigit(parser->p[0])) {
      return NULL;
    }
    parser->p++;
  }

  short numlen = parser->p - start;
  if (numlen >= MAX_INT_LEN) {
    fprintf(stderr, "Number too big\n");
    return NULL;
  }

  memcpy(token, start, numlen);
  token[numlen] = '\0';
  num = atoi(token);

  return create_int_object(num);
}

tfobj *parse_symbol(tfparser *parser) {
  char token[MAX_SYM_LEN + 1];  /* +1 because of '\0' */

  /* Saving the start of the string */
  char *start = parser->p;

  /* Now skip to the end of the token */
  while (!isspace(parser->p[0]) && parser->p[0] != '\0') {
    parser->p++;
  }

  short len = parser->p - start;
  if (len >= MAX_SYM_LEN) {
    fprintf(stderr, "Symbol too big\n");
    return NULL;
  }

  memcpy(token, start, len);
  token[len] = '\0';

  tfprim prim = getprim(token);
  if (prim == NULL) {
    return NULL;
  }

  return create_symbol_object(prim);
}
