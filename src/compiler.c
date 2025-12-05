#include "../include/compiler.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "../include/list.h"
#include "../include/memory.h"

char *read_file(char *path) {
  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    perror("Opening ToyForth program");
    return NULL;
  }

  fseek(fp, 0, SEEK_END);
  long file_size = ftell(fp);
  char *prg_text = (char *) xmalloc(file_size + 1);
  fseek(fp, 0, SEEK_SET);
  fread(prg_text, file_size, 1, fp);
  prg_text[file_size] = '\0';
  fclose(fp);

  return prg_text;
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
    if (isdigit(parser.p[0]) || 
      (parser.p[0] == '-' && isdigit(parser.p[1]))) {
      obj = parse_int(&parser);
    }
    else if (strncmp(parser.p, "S\" ", 3) == 0) {
      obj = parse_string(&parser);
    }
    else {
      obj = parse_symbol(&parser);
    }

    if (obj == NULL) {
      fprintf(stderr, "Syntax error at: %s\n", token_start);
      return NULL;
    }

    list_push_back(parsed_list, obj);
  }

  return parsed_list;
}
