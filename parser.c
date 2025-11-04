#include "parser.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "list.h"

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

  /* Check if it is a negative number or an error, then skip the '-' */
  if (parser->p[0] == '-') {
    if (!isdigit(parser->p[1])) {
      return NULL;
    }
    parser->p[0]++;
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

tfobj *compile(char *prg) {
  tfparser parser;
  parser.prg = prg;
  parser.p = prg;

  tfobj *obj;
  tfobj *parsed_list = create_list_object();

  while (parser.p) {
    char *token_start = parser.p;
    skip_spaces(&parser);

    if (parser.p[0] == '\0') {
      break;  /* EOF */
    }

    /* Parsing different types */
    if (isdigit(parser.p[0]) || parser.p[0] == '-') {
      obj = parse_int(&parser);
    }
    else {
      obj = NULL;
    }

    if (obj == NULL) {
      fprintf(stderr, "Syntax error at: %s\n", token_start);
      return NULL;
    }

    list_push_back(parsed_list, obj);
  }

  return parsed_list;
}
