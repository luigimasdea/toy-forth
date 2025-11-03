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

tfobj *tokenize(char *buf);

#endif // !PARSER_H
