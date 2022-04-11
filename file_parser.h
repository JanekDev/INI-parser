#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 256

struct Key {
  char *key;
  char *value;
  struct Key *nextkey;
};

struct Section {
  char *name;
  struct Key *keys;
  struct Section *nextsection;
};

void free_mem(struct Section *first_section);

bool is_identifier_valid(char *identifier);

struct Section *parse_file(FILE *file);

char *read_value_from_section(struct Section *first_section, char *section, char *key);

#endif