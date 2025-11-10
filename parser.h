#ifndef PARSER_H
#define PARSER_H

#include "tfobj.h"

#define MAX_PRIM_LEN 10
#define MAX_INT_LEN 128

typedef struct tfparser {
  char *prg;  /* The program to compile into a list */
  char *p;  /* Next token to parse */
} tfparser;

void skip_spaces(tfparser *parser);
tfobj *parse_string(tfparser *parser);
tfobj *parse_int(tfparser *parser);
tfobj *compile(char *prg);

#endif // !PARSER_H
