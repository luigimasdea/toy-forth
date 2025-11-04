#ifndef PARSER_H
#define PARSER_H

/*
* - Tokenize input by whitespaces
* - Parse
*   Int -> atoi()
*   Bool -> atoi() + check_bool
*   Strings -> later
*   Lists -> later
*   Symbols -> check if in dictionary
*/

#include "tfobj.h"

typedef struct tfparser {
  char *prg;  /* The program to compile into a list */
  char *p;  /* Next token to parse */
} tfparser;

char *normalize(char *str);
tfobj *parse(const char *tok);
tfobj *tokenize(char *buf);

#endif // !PARSER_H
