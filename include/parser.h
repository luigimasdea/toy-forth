#ifndef PARSER_H
#define PARSER_H

#include "tfobj.h"

#define MAX_SYM_LEN 10
#define MAX_INT_LEN 128

typedef struct tfparser {
  char *prg;  /* The program to compile into a list */
  char *p;  /* Next token to parse */
} tfparser;

void skip_spaces(tfparser *parser);
tfobj *parse_int(tfparser *parser);
tfobj *parse_symbol(tfparser *parser);

#endif // !PARSER_H
